#include "str_utils.h"
#include "vadefs.h"
#include "stdio.h"
#include "stdlib.h"

char * str_format(char * format, int result_size, ...) {
    va_list ap;
    char * buffer = calloc(result_size, sizeof(char));
    snprintf(buffer, result_size, format, ap);
    return buffer;
}

char * concat(char * first, int f_size, char * second, int s_size) {
    if (f_size != 0)
        return str_format("%s%s", f_size+s_size, first, second);
    else 
        return str_format("%s", second);
}

char * int_to_str(int number) {
    return str_format("%d", number);
}

char * join_int_arr(int * arr, int size, char * delimeter, int delimeter_size) {
    char * common_format = concat( 
                            concat("%d", 2, delimeter, delimeter_size), 
                            2+delimeter_size,
                            "%s",
                            2);
    int format_str_size = 4 + delimeter_size;
    int appending_size = MAX_DIGIT_NUMBER + delimeter_size + format_str_size;

    char * buffer = concat(buffer, 0, common_format, format_str_size);
    int current_buffer_size = 0;

    for(int *iter = arr; iter <= &arr[size - 2]; iter++) {
        current_buffer_size += appending_size;
        buffer = str_format(buffer, current_buffer_size, *iter, common_format);
    }

    buffer = str_format(buffer, current_buffer_size, "%d");
    buffer = str_format(buffer, current_buffer_size+MAX_DIGIT_NUMBER-2, int_to_str(arr[size-1]));

    return buffer;
}

char * join_int_arr_with_commas(int * arr, int size) {
    return join_int_arr(arr, size, ", ", 2);
}