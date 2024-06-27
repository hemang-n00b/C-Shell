#ifndef __QUE__
#define __QUE__

#include "headers.h"

typedef struct Que{
    int front;
    int rear ;
    char**arr;
    int number_of_elements;
}Que;

Que* createQue();
bool IsEmpty(Que*Q);
Que* push(Que*Q , char*str);
char* show_rear(Que*Q);
void freeQue(Que*Q);
Que*pop(Que*Q );
char* show_front(Que*Q);

#endif