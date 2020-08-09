#ifndef __PROBLEM_H
#define __PROBLEM_H

#include "sp_pnt.h"

struct {
     const Point ORIGIN_POINT;
     int POINT_NUMBER;
     int SPHERE_RADIUS;
     int * (*SATTELLITE_DISTANCE_PRODUCER) (int);
     void (*POINT_INPUT_CALLBACK)(int, int *, int *, int *);
     void (*LOGGER)(char *);
     void (*RESULT_CALLBACK)(int, int, int);
} PROBLEM_INIT = {{0, 0, 0}, 4, 10, NULL, NULL, NULL, NULL};

void problem_solution();

#endif