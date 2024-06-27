#include "headers.h"

void prompt(char* root_directory ,int size , int time , char*command) {
    char* username = getlogin();
    char cwd[10000];
    char get_host_name[10000];
    int host_return_value= gethostname(get_host_name , sizeof(get_host_name));
    char* present_directory = getcwd(cwd , sizeof(cwd));
    if(present_directory==NULL)
    {
        printf("The getcwd funtion shows an error\n");
        exit(1);
    }
    if(get_host_name==NULL)
    {
        printf("Unable to get the host name\n");
        exit(1);
    }

    if(strncmp(root_directory , present_directory , size)==0)
    {
        printf("\x1b[1m\033[35m<%s@%s\033[0m:\033[36m~\033[0m\x1b[0m" , username , get_host_name);
        int i=size;
        while(present_directory[i]!='\0')
        {
            printf("\x1b[1m\033[36m%c\033[0m\x1b[0m" , present_directory[i]);
            i++;
        }
    }
    else{
        printf("\x1b[1m\033[35m<%s@%s\033[0m:\x1b[1m\033[36m%s\033[0m\x1b[0m" , username , get_host_name, present_directory);
    }
    if(time>2 && command[0]!='\0')
    {
        printf("\x1b[1m\033[31m%s : %ds\033[35m> \033[0m\x1b[0m" , command , time);
    }
    else{
        printf("\x1b[1m\033[35m> \033[0m\x1b[0m");
    }
}
