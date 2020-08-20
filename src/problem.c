#include "problem.h"
#include "error_handling.h"
#include "sp_pnt.h"
#include "str_utils.h"
#include "stdio.h"
#include "math.h"

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

void __log_distances(double *, int);
void __log_point_preinit();
double __find_coordiante(char);

Point * POINTS;
double * DISTANCES;

void __problem_solution() {
    DISTANCES = PROBLEM_INIT.satellite_distance_producer(PROBLEM_INIT.POINT_NUMBER);
    __log_distances(DISTANCES, PROBLEM_INIT.POINT_NUMBER);

    __log_point_preinit();
    POINTS = produce_points(PROBLEM_INIT.POINT_NUMBER, PROBLEM_INIT.point_input_callback);
    
    double x = __find_coordiante('x');
    double y = __find_coordiante('y');
    double z = __find_coordiante('z');
    PROBLEM_INIT.result_callback(x, y, z);
    free(POINTS);
    free(DISTANCES);
}

void __log_distances(double * distances, int number) {
    /* char * joint_distances = join_int_arr_with_commas(distances, number); */
    PROBLEM_INIT.logger("Point distances: ");
    /* PROBLEM_INIT.logger(joint_distances); */
    printf("ρ[%d]=%f", 1, distances[0]);
    for(int i = 1; i < number; i++) {
        printf(", ρ[%d]=%f", i+1, distances[i]);
    }
    printf("\n");
    /*free(joint_distances);*/
}

void __log_point_preinit() {
    PROBLEM_INIT.format_logger("Known %d points initialization", PROBLEM_INIT.POINT_NUMBER);
}

char * X_FORMULA_STR = "Xa = (R^2 - 2*Yp1*Ya - 2*Zp1*Za - ρ1^2)/2*Xp1";
char * Y_FORMULA_STR = "Ya = (Za * (2*Yp2*Zp1-3*Xp2*Yp1*Zp2) - Yp2 * (R^2 - 1) - ρ1^2 * Xp1 * Yp1)/((Xp2*Yp1 - Yp2) * 2*Xp1)";
char * Z_FORMULA_STR = "Za = (R^2 * (Xp1 - Xp2 - Xp3) - Xp1 * (R^3 + 2*Xp1 + ρ1^2 + ρ2^2 - ρ3^2))/(2*Xp3*Zp1 - 2*Xp1*Zp1 + Xp2*Zp1)";

double X_formula();
double Y_formula();
double Z_formula();

double __find_coordiante(char coord) {
    char * formula_str = NULL;
    double (* formula) ();

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
    return formula();
}

double x_p(int i) {
    return POINTS[i].x;
}
double y_p(int i) {
    return POINTS[i].y;
}
double z_p(int i) {
    return POINTS[i].z;
}

double ro(int i){
    return DISTANCES[i];
}

///формула нахождения X(t)
double X_formula() {
    double r = PROBLEM_INIT.SPHERE_RADIUS;
    double numerator = pow(r, 2) - 2 * x_p(1) * Y_formula() - 2 * z_p(1) * Z_formula() - pow(ro(1), 2);
    return numerator /2*x_p(1); 
}

///формула нахождения Y(t)
double Y_formula() {
    double r = PROBLEM_INIT.SPHERE_RADIUS;
    double za_group = Z_formula() * (2 * y_p(2) * z_p(1) - 3 * x_p(2) * z_p(2));
    double appendix = -1 * y_p(2) * (pow(r, 2) - 1) - pow(ro(1), 2) * x_p(1) * y_p(1);
    double numenator = za_group + appendix;
    double denominator = 2 * x_p(1) * (x_p(2) * y_p(1) - y_p(2));
    return numenator/denominator;
}

///формула нахождения Z(t)
double Z_formula() {
    double r = PROBLEM_INIT.SPHERE_RADIUS;
    double r_sqr_grp = pow(r, 2) + (x_p(1) - x_p(2) + x_p(3));
    double xp1_grp = x_p(1) * (pow(r, 3) + 2 * x_p(1) + pow(ro(1), 2) + pow(ro(2), 2) - pow(ro(3), 2));
    double numenator = r_sqr_grp - xp1_grp;
    double denominator = 2 + x_p(3) * z_p(1) - 2 * x_p(1) * z_p(1) + x_p(2) * z_p(1); 
    return numenator/denominator;
}