#include "problem.h"
#include "error_handling.h"
#include "sp_pnt.h"
#include "stdio.h"

#define false = 0;
#define true = 1;

int __is_problem_inited();
void __problem_solution();

void problem_solution() {
    
    if (__is_problem_inited){

        __problem_solution();
    }
    else throw_exc(&NULL_POINTER_EX);
}

int is_problem_inited(){
    return PROBLEM_INIT.point_input_callback != NULL && 
        PROBLEM_INIT.result_callback != NULL &&
        PROBLEM_INIT.satellite_distance_producer != NULL &&
        PROBLEM_INIT.logger != NULL;
}

void __log_distances(int *, int);
void __log_point_preinit();
int __find_coordiante(char, int *, Point *);

void __problem_solution() {
    int * distances = PROBLEM_INIT.satellite_distance_producer(PROBLEM_INIT.POINT_NUMBER);
    __log_distances(distances, PROBLEM_INIT.POINT_NUMBER);

    __log_point_preinit();
    Point * points = produce_points(PROBLEM_INIT.POINT_NUMBER, PROBLEM_INIT.point_input_callback);
    
    int x = __find_coordiante('x', distances, points);
    int y = __find_coordiante('y', distances, points);
    int z = __find_coordiante('z', distances, points);
    PROBLEM_INIT.result_callback(x, y, z);
}

void __log_point_preinit() {
    char * format = "Known points initialization %d";
    int fsSize = 30;
    char * buffer = calloc(fsSize, sizeof(char));
    snprintf(buffer, fsSize, format, PROBLEM_INIT.POINT_NUMBER);
    PROBLEM_INIT.logger(buffer);
}