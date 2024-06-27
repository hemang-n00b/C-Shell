#include "headers.h"

extern Node* for_activities;

char* activities(char* remaining_token )
{
    for_activities= activities_print();
    return remaining_token;
}