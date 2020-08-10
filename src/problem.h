#pragma once
#include "sp_pnt.h"

struct {
     Point ORIGIN_POINT;
     int POINT_NUMBER;
     int SPHERE_RADIUS;
     int * (*satellite_distance_producer) (int);
     void (*point_input_callback)(int, int *, int *, int *);
     void (*logger)(char *);
     void (*result_callback)(int, int, int);
} PROBLEM_INIT;

void problem_solution();
