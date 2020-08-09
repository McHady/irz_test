#include "problem.h"
#include "error_handling.h"
#include "sp_pnt.h"
#include "str_utils.h"

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
    free(points);
}

void __log_distances(int * distances, int number) {
    char * joint_distances = join_int_arr_with_commas(distances, number);
    PROBLEM_INIT.logger("Point distances: ");
    PROBLEM_INIT.logger(joint_distances);
    free(joint_distances);
}

void __log_point_preinit() {
    char * format = "Known points initialization %d";
    int fsSize = 30;
    char * buffer = str_format(format, fsSize, PROBLEM_INIT.POINT_NUMBER);
    PROBLEM_INIT.logger(buffer);
}

char * X_FORMULA = "";
char * Y_FORMULA = "";
char * Z_FORMULA = "";

int X_formula(int * distances, Point * points);
int Y_formula(int * distances, Point * points);
int Z_formula(int * distances, Point * points);

int __find_coordiante(char coord, int * distances, Point * points) {
    char * formula_str = NULL;
    int (* formula) (int *, Point *);

    switch (coord)
    {
        case 'x':
            formula_str = X_FORMULA;
            formula = X_formula;
            break;
        
        case 'Y':
            formula_str = Y_FORMULA;
            formula = Y_formula;
        
        case 'Z':
            formula_str = Z_FORMULA;
            formula = Z_formula;

        default:
            throw_def_exc();
            return 0;
            break;
    }

    char * message = str_format("Found %s about the formula: %s", 60, coord, formula_str);
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