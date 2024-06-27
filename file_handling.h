#ifndef __FILE_HANDLE__
#define __FILE_HANDLE__

#include"headers.h"

Que* PushCommand(Que*Q , char*str);
Que* ReadContent(FILE *filePointer , Que*Q);
void WriteContent(FILE *filePointer , Que*Q);


#endif