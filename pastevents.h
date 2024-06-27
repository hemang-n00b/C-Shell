#ifndef __PASTEVENTS__
#define __PASTEVENTS__

#include "headers.h"
#include "linked_list.h"

char* pastevents(int* include_in_history ,Que*Q  , char*remaining_token_2  , char*root_directory , char* previous_directory , int* changes_in_directory , Node*L ,int* system_call_time , char*command );
char * replace(char* new , char* old , char* str);


#endif