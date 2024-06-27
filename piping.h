#ifndef __PIPING__
#define __PIPING__

#include "headers.h"

char* piping(char* remaining_token , char* root_directory , char*previous_directory , int*changes , int*final_time , char*command , Node*L ,int*include_in_history , int*changes_in_directory  ,Que*Q   ,int* system_call_time );

// char* piping2(char* remaining_token , char* root_directory , char*previous_directory , int*changes , int*final_time , char*command , Node*L ,int*include_in_history ,int*changes_in_directory );


#endif