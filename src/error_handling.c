#include "stdio.h"
#include "error_handling.h"

void __default_exception_callback(char * message);

void build_exception(struct exception* ex, char * message, void (* callback)(char *)) {
    ex->callback = callback;
    ex->message = message;
}

void build_def_exception(struct exception * ex, char * message) {
    build_exception(ex, message, __default_exception_callback);
}

void throw_exc(struct exception * ex) {
    ex->callback(ex->message);
}

void throw_def_exc() {
    throw_exc(&DEFAULT_EX);
}

void __default_exception_callback(char * message){
    printf("Exception %s has been trown", message);
}

#ifndef __ERROR_HANDLING_INIT
#define __ERROR_HANDLING_INIT

void __initialize() {
    build_def_exception(&NULL_POINTER_EX, "NULL POINTER");
    build_def_exception(&DEFAULT_EX, "DEFAULT");
}

#endif