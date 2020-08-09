#include "problem.h"
#include "error_handling.h"

#define false = 0;
#define true = 1;

int __is_problem_inited();
int __problem_solution();

void problem_solution() {
    
    if (__is_problem_inited){

        __problem_solution();
    }
    else throw_exc(&NULL_POINTER_EX);
}

int is_problem_inited(){
    return PROBLEM_INIT.POINT_INPUT_CALLBACK != NULL && 
        PROBLEM_INIT.RESULT_CALLBACK != NULL &&
        PROBLEM_INIT.SATTELLITE_DISTANCE_PRODUCER != NULL &&
        PROBLEM_INIT.LOGGER != NULL;
}