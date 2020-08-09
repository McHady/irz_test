#include <stdio.h>
#include "problem.h"
#include "time.h" 

void __point_input(int, int *, int *, int *);
void __result_callback(int, int, int);
int * __sattelite_distanses(int);
void __log(char *);

int MAX_DISTANCE = 100;

int main(void) {

    PROBLEM_INIT.POINT_INPUT_CALLBACK = __point_input;
    PROBLEM_INIT.RESULT_CALLBACK = __result_callback;
    PROBLEM_INIT.SATTELLITE_DISTANCE_PRODUCER = __sattelite_distanses;
    PROBLEM_INIT.LOGGER = __log;

    problem_solution();
}

void __point_input(int i, int * x, int * y, int * z) {
    printf("Enter %d point coordinates: ", i);
    scanf("%d %d %d\n", x, y, z);
}


void __result_callback(int x, int y, int z) {
    printf("\nSought point coordinates: x=%d, y=$d, z=%d\n", x, y, z);
}

int * __sattelite_distanses(int number) {
    int * distances = calloc(number, sizeof(int));

    for(int i = 0; i < number; i++){
        srand(i);
        distances[i] = rand() / RAND_MAX; 
    }

    return distances;
}

void __log(char * message){
    time_t now = time(0);
    printf("log %s: %s\n", ctime(now), message);    
}