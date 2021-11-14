#ifndef __UTIL_H_
#define __UTIL_H_

#define dt_ms(oldtime) (clock() - (oldtime)) / (CLOCKS_PER_SEC / 1000)

#define create_min_func(datatype)               \
datatype min_##datatype(datatype a, datatype b) \
{                                               \
    return a < b ? a : b;                       \
}                                               \

typedef struct {
	double x, y;
} Vec2d;

int vec2d_compare_x(const void *, const void *);
double dist(int x1, int y1, int x2, int y2);
double randfrom(double min, double max);

#endif