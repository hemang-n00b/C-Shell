#ifndef __NEONATE__
#define __NEONATE__

#include "headers.h"

void die(const char *s);
// struct termios orig_termios;
void disableRawMode();
void enableRawMode();
void neonate(char* remaining_token);



#endif