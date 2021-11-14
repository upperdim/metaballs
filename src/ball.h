#ifndef __BALL_H_
#define __BALL_H_

#include "util.h"
#include "graphics.h"

#define BALL_COUNT 4
#define BALL_GLOW 225
#define BALL_DEFAULT_RADIUS 40
#define BALL_VEL_X_MIN_COEFF 10
#define BALL_VEL_X_MAX_COEFF 20
#define BALL_VEL_Y_MIN_COEFF BALL_VEL_X_MIN_COEFF
#define BALL_VEL_Y_MAX_COEFF BALL_VEL_X_MAX_COEFF


typedef struct {
    Vec2d pos;
    Vec2d vel;
    double r;
} Ball;

Ball ball_create(double x, double y);
void balls_update(Screen *scr, Ball *ballsarr, const int SIZE);

#endif