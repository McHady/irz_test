#include "stdlib.h"
#include "stdio.h"
#include "sp_pnt.h"

void build_point(Point * point, double x, double y, double z) {

    point->x = x;
    point->y = y;
    point->z = z;
}

Point * produce_points(int number, void (* producer) (int, double *, double *, double *)) {

    Point * points = calloc(number, sizeof(Point));

    for(int i = 0; i < number; i++) {

        double x, y, z;
        producer(i, &x, &y, &z);
        build_point(&points[i], x, y, z);
    }

    return points;          
}

void expose_point(Point point, void (* callback) (double, double, double)) {
    callback(point.x, point.y, point.z);
}
