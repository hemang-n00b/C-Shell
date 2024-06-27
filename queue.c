#include "headers.h"
#include "queue.h"

Que* createQue()
{
    Que*Q = (Que*)malloc(sizeof(Que));
    Q->front = 0;
    Q->rear = -1;
    Q->arr = (char**)malloc(sizeof(char*)*31);
    Q->number_of_elements =0;
    return Q;
}

char* show_front(Que*Q)
{
    char* to_return  = strdup(Q->arr[Q->front]);
    return to_return;
}
bool IsEmpty(Que*Q)
{
    if(Q->front - Q->rear ==1)
    {
        return true;
    }
    return false;
}

Que* push(Que*Q , char*str)
{
    Q->rear++;
    if(Q->rear>31)
    {
        Q->rear=0;
    }
    Q->arr[Q->rear] = strdup(str);
    Q->number_of_elements++;
    return Q;
}
Que*pop(Que*Q )
{
    Q->front++;
    Q->number_of_elements--;
    return Q;
}
char* show_rear(Que*Q)
{
    // printf("Ashok\n");
    if(Q->rear!=-1)
        return Q->arr[Q->rear];
    else{
        return "&nbsp";
    }
}

void freeQue(Que*Q)
{
    free(Q->arr);
    free(Q);
}