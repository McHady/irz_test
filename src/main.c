#include "stdio.h"
#include "problem.h"
#include "time.h" 
#include "str_utils.h"
#include "vadefs.h"
#include "stdarg.h"

void __point_input(int, int *, int *, int *);
void __result_callback(int, int, int);
int * __sattelite_distanses(int);
void __log(char *);
void __flog(char *, ...);

int MAX_DISTANCE = 100;

int main(void) {
    STR_INIT.MAX_DIGIT_NUMBER = 5;

    PROBLEM_INIT.SPHERE_RADIUS = 10;
    PROBLEM_INIT.point_input_callback = __point_input;
    PROBLEM_INIT.result_callback = __result_callback;
    PROBLEM_INIT.satellite_distance_producer = __sattelite_distanses;
    PROBLEM_INIT.logger = __log;
    PROBLEM_INIT.format_logger = __flog;

    problem_solution();
    return 0;
}

void __point_input(int i, int * x, int * y, int * z) {
    printf("Enter %d point coordinates: ", i+1);
    scanf("%d %d %d", x, y, z);
}


void __result_callback(int x, int y, int z) {
    printf("\nSought point coordinates: x=%d, y=%d, z=%d\n", x, y, z);
}

int * __sattelite_distanses(int number) {
    int * distances = calloc(number, sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < number; i++){
        distances[i] = rand() / MAX_DISTANCE; 
    }

    return distances;
}

void __log(char * message){
    time_t now;
    time(&now);
    printf("log %s%s\n", ctime(&now), message);    
}

void __flog(char * format, ...) {
    time_t now;
    time(&now);
    printf("log %s", ctime(&now));
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}