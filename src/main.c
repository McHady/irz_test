#include "stdio.h"
#include "problem.h"
#include "time.h" 
#include "str_utils.h"

void __point_input(int, int *, int *, int *);
void __result_callback(int, int, int);
int * __sattelite_distanses(int);
void __log(char *);

int MAX_DISTANCE = 100;

int main(void) {
    STR_INIT.MAX_DIGIT_NUMBER = 5;

    PROBLEM_INIT.SPHERE_RADIUS = 10;
    PROBLEM_INIT.point_input_callback = __point_input;
    PROBLEM_INIT.result_callback = __result_callback;
    PROBLEM_INIT.satellite_distance_producer = __sattelite_distanses;
    PROBLEM_INIT.logger = __log;

    problem_solution();
    return 0;
}

void __point_input(int i, int * x, int * y, int * z) {
    printf("Enter %d point coordinates: ", i);
    scanf("%d %d %d\n", x, y, z);
}


void __result_callback(int x, int y, int z) {
    printf("\nSought point coordinates: x=%d, y=%d, z=%d\n", x, y, z);
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
    time_t now;
    time(&now);
    printf("log %s%s\n", ctime(&now), message);    
    free(message);
}