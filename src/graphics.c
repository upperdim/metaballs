#include <stdbool.h>

#include "graphics.h"
#include "debug.h"
#include "util.h"


Color backgroundColor = {0, 0, 0, 255};
bool limitFramerate = false;

create_min_func(int)

void draw_pixel(Screen *scr, int x, int y, Color c)
{
	scr->pixelsArr[x + y * scr->width] = SDL_MapRGBA(scr->format, c.r, c.g, c.b, c.a);
}

void draw_rect(Screen *scr, int xstart, int ystart, int xend, int yend, Color c)
{
	for (int i = ystart; i < yend; ++i) {
		for (int j = xstart; j < xend; ++j) {
			draw_pixel(scr, i, j, c);
		}
	}
}

void screen_fill(Screen *scr, Color c)
{
	draw_rect(scr, 0, 0, scr->height, scr->width, c);
}

void screen_clear(Screen *scr)
{
	screen_fill(scr, backgroundColor);
}

void cap_framerate(double deltaTime)
{
	if (limitFramerate && deltaTime < FRAME_LIMIT_MS) {
		SDL_Delay(FRAME_LIMIT_MS - deltaTime);
	}
}

Color color(int r, int g, int b, int a)
{
	r = min_int(255, r);
	g = min_int(255, g);
	b = min_int(255, b);
	//a = min_int(255, a);
	
	return (Color) {r, g, b, a};
}

hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = 0.0;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}

rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}
