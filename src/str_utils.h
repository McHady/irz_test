#pragma once

char * str_format(char * format, int result_size, ...);
char * concat(char * first, int f_size, char * second, int s_size);
char * int_to_str(int);
char * join_int_arr(int * arr, int size, char * delimeter, int delimeter_size);
char * join_int_arr_with_commas(int * arr, int size);

struct {
    int MAX_DIGIT_NUMBER;
} STR_INIT;
