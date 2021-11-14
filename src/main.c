#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "cli.h"
#include "util.h"
#include "ball.h"
#include "debug.h"
#include "graphics.h"

int init(SDL_Window **window, SDL_Surface **surface, Screen *scr)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	*window = SDL_CreateWindow("Metaballs",
							   SDL_WINDOWPOS_CENTERED,
							   SDL_WINDOWPOS_CENTERED,
							   640, 480,
							   SDL_WINDOW_RESIZABLE);
	if (!(*window)) {
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	*surface = SDL_GetWindowSurface(*window);
	if (!(*surface)) {
		printf("Error creating surface: %s\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return 1;
	}

	scr->pixelsArr = (*surface)->pixels;
	scr->width     = (*surface)->w;
	scr->height    = (*surface)->h;
	scr->format    = (*surface)->format;

	srand(time(NULL));

	return 0;
}

int main(int argc, char *argv[])
{
	handle_args(&argc, argv);

	SDL_Window *window = NULL;
	SDL_Surface *windowSurface = NULL;
	Screen screen = {0};

	if (init(&window, &windowSurface, &screen)) {
		printf("Error! Failed to initialize.\n");
		return 1;
	}

	// Init world entities
	Ball balls[BALL_COUNT] = {0};

	for (int i = 0; i < BALL_COUNT; ++i) {
		balls[i] = ball_create(rand() % screen.width, rand() % screen.height);
	}

	clock_t oldtime = clock();
	while (!quit) {
		double delta = dt_ms(oldtime);
		oldtime = clock();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					windowSurface = SDL_GetWindowSurface(window);
					screen.pixelsArr = windowSurface->pixels;
					screen.width = windowSurface->w;
					screen.height = windowSurface->h;
					if (debugMode) printf("Window resized to w: %d, h: %d\n", screen.width, screen.height);
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_Q:
				case SDL_SCANCODE_ESCAPE:
					quit = true;
					break;
				case SDL_SCANCODE_V:
					limitFramerate = !limitFramerate;
					if (debugMode) printf("Frame limiter switched to %s\n", limitFramerate ? "ON" : "OFF");
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		screen_clear(&screen);

		// Prepare the frame to print
		for (int x = 0; x < screen.width; ++x) {
			for (int y = 0; y < screen.height; ++y) {
				//int index = x + y * screen.width;

				int sum = 0;
				for (int i = 0; i < BALL_COUNT; ++i) {
					double d = dist(x, y, balls[i].pos.x, balls[i].pos.y);
					sum += (int) (balls[i].r * BALL_GLOW / d);
				}
				
				// hsv h = {sum % 255, 255, 255};
				// rgb c = hsv2rgb(h);
				// draw_pixel(&screen, x, y, color(c.r, c.g, c.b, 255));
				draw_pixel(&screen, x, y, color(sum, sum, sum, 255));
			}
		}

		for (int i = 0; i < BALL_COUNT; ++i) {
			balls_update(&screen, balls, BALL_COUNT);
			//printf("%d - %lf %lf %lf %lf\n", (i+1), balls[i].pos.x, balls[i].pos.y, balls[i].vel.x, balls[i].vel.y); // DEBUG
		}

		SDL_UpdateWindowSurface(window);
		cap_framerate(delta);
		print_debug_info(delta);
	}

	SDL_FreeSurface(windowSurface);
	windowSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	return 0;
}
