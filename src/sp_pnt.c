#include "stdlib.h"
#include "sp_pnt.h"

void build_point(Point * point, int x, int y, int z) {

    point->x = x;
    point->y = y;
    point->z = z;
}

Point * produce_points(int size, void (* producer) (int *, int *, int *)) {

    Point * points;
    points = calloc(size, sizeof(Point));

    for(int i = 0; i < size; i++) {

        int x, y, z;
        producer(&x, &y, &z);
        build_point(&points[i], x, y, z);
    }

    return points;          
}

void expose_point(Point point, void (* callback) (int, int, int)) {
    callback(point.x, point.y, point.z);
}
