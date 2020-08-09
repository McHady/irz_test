#include "stdlib.h"
#include "stdio.h"
#include "sp_pnt.h"

void build_point(Point * point, int x, int y, int z) {

    point->x = x;
    point->y = y;
    point->z = z;
}

Point * produce_points(int number, void (* producer) (int, int *, int *, int *)) {

    Point * points = calloc(number, sizeof(Point));

    for(int i = 0; i < number; i++) {

        int x, y, z;
        producer(i, &x, &y, &z);
        build_point(&points[i], x, y, z);
    }

    return points;          
}

void expose_point(Point point, void (* callback) (int, int, int)) {
    callback(point.x, point.y, point.z);
}


void __testing_point_producer(int, int *, int *, int *);
void __testing_expose_callback(int, int, int);

int main(void){
    Point singlePoint;
    build_point(&singlePoint, 1, 2, 3);
    expose_point(singlePoint, __testing_expose_callback);

    int number = 2;
    Point * pointArray = produce_points(number, __testing_point_producer);
    for (int i = 0; i < number; i++){
        expose_point(pointArray[i], __testing_expose_callback);
    }
}

void __testing_point_producer(int i, int * x, int * y, int * z) {
    *x = i; *y = i; *z = i;
}

void __testing_expose_callback(int x, int y, int z){
    printf_s("\nx=%d, y=%d, z=%d\n", x, y, z);
}