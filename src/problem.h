#ifndef __PROBLEM_H
#define __PROBLEM_H

#include "sp_pnt.h"

struct {
     const Point ORIGIN_POINT = Point {0, 0, 0};
     int POINT_NUMBER = 4;
     int SPHERE_RADIUS;
     int * (*SATTELLITE_DISTANCE_PRODUCER) (int);
     void (*POINT_INPUT_CALLBACK)(int *, int *, int *);
     void (*STAGE_LOGGER)(int);
     void (*RESULT_CALLBACK)(int, int, int);
} PROBLEM_INIT;

void problem_solution();

#endif