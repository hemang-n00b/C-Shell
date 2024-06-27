#include "headers.h"

void die(const char *s)
 {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
 {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}


void enableRawMode()
 {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void neonate(char* remaining_token)
{
    char* character = strtok_r(remaining_token , " \t\n" , &remaining_token);
    char* number = strtok_r(remaining_token , " \t\n" , &remaining_token);

    int time = atoi(number);
    char ch = 'x' ;
    // printf("%d\n" , time);
    // printf("%c\n" ,ch );
    setbuf(stdout, NULL);
    enableRawMode();
    int child_pid=fork();
    if(child_pid==0){
        while(1)
        {
            FILE* f = fopen("/proc/sys/kernel/ns_last_pid","r");
            if(f==NULL)
            {
                perror("Unable to open the file\n");
                return ;
            } 
            char pid[10];
            fgets(pid,10,f);
            printf("%s",pid);
            sleep(time);
        }
    }
    else if(child_pid< 0)
    {
        perror("fork");
        return ;
    }
    else{
        char get_the_input_character ;
        while( read(STDIN_FILENO, &get_the_input_character, 1) == 1)
        {
            if(get_the_input_character == ch)
            {
                break;
            }
        }
        kill(child_pid , SIGKILL);
    }

    disableRawMode();
        
    

}


