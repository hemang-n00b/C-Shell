
#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

#include "linked_list.h"
#include "headers.h"

int redirect(char* remaining_token , char* root_directory , char* previous_directory , int* changes_in_directory , int* include_in_history, Node*L ,int* system_call_time , char*command ,Que*Q );
void system_calls2(char*token , char*remaining_token);
char* system_calls(char*token , int background , char*remaining_token , int*final_time , char*command , Node*L , int*include_in_history  , int is_piped);

#endif

