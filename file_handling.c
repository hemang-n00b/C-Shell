#include "headers.h"

void WriteContent(FILE *filePointer , Que*Q)
{
    if(filePointer==NULL)
    {
        printf("NULL File\n");
        return ;
    }
    while(!IsEmpty(Q))
    {
        fprintf(filePointer, "%s", show_front(Q));
        Q = pop(Q);
    }
    freeQue(Q);
}

Que* ReadContent(FILE *filePointer , Que*Q)
{
    char line[4097];
    int i=0;
     while (fgets(line, sizeof(line), filePointer)) {
        size_t len = strlen(line);
        Q = push(Q , line);
        i++;
    }
    return Q;
}

Que* PushCommand(Que*Q , char*str)
{
    if(Q->number_of_elements<15)
    {
        Q = push(Q , strdup(str));
    }
    else{
        Q = push(Q , strdup(str));
        Q = pop(Q );
    }
}