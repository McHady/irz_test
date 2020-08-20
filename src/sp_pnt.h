#pragma once
#include "stdlib.h"
typedef struct {
    double x; 
    double y; 
    double z;
} Point;

void build_point(Point *, double, double, double);

Point * produce_points(int, void (int, double *, double *, double *));

void expose_point(Point, void (int, double, double)); 