#include <math.h>
#include "ball.h"
#include "util.h"
#include "graphics.h"

Ball ball_create(double x, double y)
{
    return (Ball) {
        (Vec2d) {x, y},
        (Vec2d) {
            randfrom(-1, 1) * randfrom(BALL_VEL_X_MIN_COEFF, BALL_VEL_X_MAX_COEFF),
            randfrom(-1, 1) * randfrom(BALL_VEL_Y_MIN_COEFF, BALL_VEL_Y_MAX_COEFF)
        },
        BALL_DEFAULT_RADIUS
    };
}

void balls_update(Screen *scr, Ball *ballsarr, const int SIZE)
{
    for (int i = 0; i < SIZE; ++i) {
        ballsarr[i].pos.x += ballsarr[i].vel.x;
        ballsarr[i].pos.y += ballsarr[i].vel.y;

        double posx = ballsarr[i].pos.x;
        double posy = ballsarr[i].pos.y;
        
        if (posx > scr->width || posx < 0)
            ballsarr[i].vel.x = -ballsarr[i].vel.x;

        if (posy > scr->height || posy < 0)
            ballsarr[i].vel.y = -ballsarr[i].vel.y;
    }
}