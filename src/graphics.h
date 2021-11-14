#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#include <stdbool.h>

#include <SDL2/SDL.h>


#define FRAME_LIMIT_FPS 60
#define FRAME_LIMIT_MS (1000 / FRAME_LIMIT_FPS)


typedef struct {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} Color;

typedef struct {
	unsigned int *pixelsArr;
	int width;
	int height;
	SDL_PixelFormat *format;
} Screen;

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;


Color backgroundColor;
bool limitFramerate;


void draw_pixel(Screen *, int, int, Color);
void draw_rect(Screen *, int, int, int, int, Color);
void screen_fill(Screen *, Color);
void screen_clear(Screen *);
void cap_framerate(double deltaTime);
Color color(int r, int g, int b, int a);
hsv   rgb2hsv(rgb in);
rgb   hsv2rgb(hsv in);


#endif