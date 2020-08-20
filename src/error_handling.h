#ifndef __ERROR_HANDLING_H
#define __ERROR_HANDLING_H
struct exception {
    char * message;
    void (*callback)(char *);
} NULL_POINTER_EX, DEFAULT_EX;

void build_exception(struct exception *, char *, void (*callback) (char *));
void build_def_exception(struct exception *, char *);
void throw_exc(struct exception *);
void throw_def_exc();   

#endif
