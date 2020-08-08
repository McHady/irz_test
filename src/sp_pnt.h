#ifndef __SP_PNT_H
#define __SP_PNT_H
typedef struct {
    int x; 
    int y; 
    int z;
} Point;

void build_point(Point *, int, int, int);

Point * produce_points(int, void (int *, int *, int *));

void expose_point(Point, void (int, int, int)); 

#endif