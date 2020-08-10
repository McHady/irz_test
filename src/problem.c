#include "problem.h"
#include "error_handling.h"
#include "sp_pnt.h"
#include "str_utils.h"
#include "stdio.h"

#define false = 0;
#define true = 1;

int __is_problem_inited();
void __problem_solution();
void __init_defaults();

void problem_solution() {
    __init_defaults();
    if (__is_problem_inited){

        __problem_solution();
    }
    else throw_exc(&NULL_POINTER_EX);
}

void __init_defaults() {
    Point orgn = {0, 0, 0};
    if (&PROBLEM_INIT.ORIGIN_POINT == NULL) PROBLEM_INIT.ORIGIN_POINT = orgn;
    int num = 4;
    if (PROBLEM_INIT.POINT_NUMBER == 0) PROBLEM_INIT.POINT_NUMBER = num;
}

int __is_problem_inited(){
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
    free(points);
}

void __log_distances(int * distances, int number) {
    /* char * joint_distances = join_int_arr_with_commas(distances, number); */
    PROBLEM_INIT.logger("Point distances: ");
    /* PROBLEM_INIT.logger(joint_distances); */
    printf("ρ[%d]=%d", 1, distances[0]);
    for(int i = 1; i < number; i++) {
        printf(", ρ[%d]=%d", i+1, distances[i]);
    }
    printf("\n");
    /*free(joint_distances);*/
}

void __log_point_preinit() {
    PROBLEM_INIT.format_logger("Known %d points initialization", PROBLEM_INIT.POINT_NUMBER);
}

char * X_FORMULA_STR = "x(t)";
char * Y_FORMULA_STR = "y(t)";
char * Z_FORMULA_STR = "z(t)";

int X_formula(int * distances, Point * points);
int Y_formula(int * distances, Point * points);
int Z_formula(int * distances, Point * points);

int __find_coordiante(char coord, int * distances, Point * points) {
    char * formula_str = NULL;
    int (* formula) (int *, Point *);

    switch (coord)
    {
        case 'x':
            formula_str = X_FORMULA_STR;
            formula = X_formula;
            break;
        
        case 'y':
            formula_str = Y_FORMULA_STR;
            formula = Y_formula;
            break;
        
        case 'z':
            formula_str = Z_FORMULA_STR;
            formula = Z_formula;
            break;

        default:
            throw_def_exc();
            return 0;
            break;
    }

    PROBLEM_INIT.format_logger("Found %c about the formula: %s", coord, formula_str);
    return formula(distances, points);
}

int X_formula(int * distances, Point * points) {
    return 0;
}

int Y_formula(int * distances, Point * points) {
    return 0;
}
int Z_formula(int * distances, Point * points) {
    return 0;
}