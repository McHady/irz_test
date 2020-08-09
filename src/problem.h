#ifndef __PROBLEM_H
#define __PROBLEM_H

#include "sp_pnt.h"

struct {
     const Point ORIGIN_POINT;
     int POINT_NUMBER;
     int SPHERE_RADIUS;
     int * (*satellite_distance_producer) (int);
     void (*point_input_callback)(int, int *, int *, int *);
     void (*logger)(char *);
     void (*result_callback)(int, int, int);
} PROBLEM_INIT = {{0, 0, 0}, 4, 10, NULL, NULL, NULL, NULL};

void problem_solution();

#endif