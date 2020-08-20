#ifndef __PROBLEM_H
#define __PROBLEM_H
#include "sp_pnt.h"

struct {
     Point ORIGIN_POINT;
     int POINT_NUMBER;
     double SPHERE_RADIUS;
     double * (*satellite_distance_producer) (int);
     void (*point_input_callback)(int, double *, double *, double *);
     void (*logger)(char *);
     void (*format_logger) (char *, ...);
     void (*result_callback)(double, double, double);
} PROBLEM_INIT;

void problem_solution();

#endif