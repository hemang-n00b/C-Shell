#include "headers.h"

extern Node* for_activities;
extern int child_pid_global ;

void fg(char* remaining_token)
{
    int outdirect =0;
    char *execute = (char*)calloc(4097 , sizeof(char));
    if(strchr(remaining_token , '<') || strchr(remaining_token, '>'))
    {
        char cmd[4097] , res[4097];
        strcpy(cmd, remaining_token);
        strcpy(res,remaining_token);
        char outputfile[4097], inputfile[4097], buf[4097], filename[4097];
        int prevfile = 0, append = 0, i, indirect = 0;
        char*remaining_files = (char*)malloc(sizeof(char)* 4097);
        int flag =0 ;
        for (i = 0; i < strlen(cmd); i++)
        {
            if (cmd[i] == '>' || cmd[i] == '<')
            {
                flag =1;
                break;
            }
            execute[i] = cmd[i]; 
        }
        // execute[i] = '\0';
        int c=0;
        while(i<strlen(cmd))
        {
            remaining_files[c++] = cmd[i++];
        }
        char* args[10];
        int t =0;
        char* token = strtok_r(remaining_files , " \t\n" , &remaining_files);
        while(token!=NULL)
        {
            args[t++] = token;
            token = strtok_r(remaining_files , " \t\n" , &remaining_files);
        }
        int tt=0;
        while(tt<t)
        {
            // printf("%s\n" , args[tt]);
            if(strcmp("<" , args[tt])==0)
            {
                indirect = 1;
                strcpy(inputfile ,args[tt+1]);
            }
            if(strcmp(">" , args[tt])==0)
            {
                outdirect = 1;
                strcpy(outputfile , args[tt+1]);
            }
            if(strcmp(">>" , args[tt])==0)
            {
                outdirect = 1;
                append =1;
                strcpy(outputfile , args[tt+1]);
            } 
            tt++;
        }
        // printf("%s\n\n" ,execute );
        if(indirect ==1)
        {
            FILE* input_pointer = fopen(inputfile , "r");
            if (input_pointer == NULL) {
                perror("Failed to open the file");
                return ;
            }
            char buffer[1024]; 
            while (fgets(buffer, sizeof(buffer), input_pointer) != NULL) {
                strcat(execute ,buffer);
            }
            fclose(input_pointer);
        }
        // printf("%s\n\n" , remaining_token);
        // printf("%s\n\n" ,execute );
    // int insta=0;
    // while(execute[insta]!='\0')
    // {
    //     remaining_token[insta] = execute[insta];
    //     insta++;
    // }
    // remaining_token[insta] = '\0';
    remaining_token = strdup(execute);
    // printf("%s" , remaining_token);
    }
    // char 
    int pid_r=atoi(remaining_token);
    if(kill(pid_r,SIGCONT)==-1){
        perror("Signal error");
        return ;
    }
     int h =atoi(remaining_token);
    change(h , 0);
    int status;
    // printf("%d\n" , pid_r);
    child_pid_global = pid_r;
    if(waitpid(pid_r,&status,WUNTRACED)==-1)
    {
        perror("waitpid");
        return ;
    }
}

void bg(char* remaining_token)
{
    int outdirect =0;
    char *execute = (char*)calloc(4097 , sizeof(char));
    if(strchr(remaining_token , '<') || strchr(remaining_token, '>'))
    {
        char cmd[4097] , res[4097];
        strcpy(cmd, remaining_token);
        strcpy(res,remaining_token);
        char outputfile[4097], inputfile[4097], buf[4097], filename[4097];
        int prevfile = 0, append = 0, i, indirect = 0;
        char*remaining_files = (char*)malloc(sizeof(char)* 4097);
        int flag =0 ;
        for (i = 0; i < strlen(cmd); i++)
        {
            if (cmd[i] == '>' || cmd[i] == '<')
            {
                flag =1;
                break;
            }
            execute[i] = cmd[i]; 
        }
        // execute[i] = '\0';
        int c=0;
        while(i<strlen(cmd))
        {
            remaining_files[c++] = cmd[i++];
        }
        char* args[10];
        int t =0;
        char* token = strtok_r(remaining_files , " \t\n" , &remaining_files);
        while(token!=NULL)
        {
            args[t++] = token;
            token = strtok_r(remaining_files , " \t\n" , &remaining_files);
        }
        int tt=0;
        while(tt<t)
        {
            // printf("%s\n" , args[tt]);
            if(strcmp("<" , args[tt])==0)
            {
                indirect = 1;
                strcpy(inputfile ,args[tt+1]);
            }
            if(strcmp(">" , args[tt])==0)
            {
                outdirect = 1;
                strcpy(outputfile , args[tt+1]);
            }
            if(strcmp(">>" , args[tt])==0)
            {
                outdirect = 1;
                append =1;
                strcpy(outputfile , args[tt+1]);
            } 
            tt++;
        }
        // printf("%s\n\n" ,execute );
        if(indirect ==1)
        {
            FILE* input_pointer = fopen(inputfile , "r");
            if (input_pointer == NULL) {
                perror("Failed to open the file");
                return ;
            }
            char buffer[1024]; 
            while (fgets(buffer, sizeof(buffer), input_pointer) != NULL) {
                strcat(execute ,buffer);
            }
            fclose(input_pointer);
        }
        // printf("%s\n\n" , remaining_token);
        // printf("%s\n\n" ,execute );
    // int insta=0;
    // while(execute[insta]!='\0')
    // {
    //     remaining_token[insta] = execute[insta];
    //     insta++;
    // }
    // remaining_token[insta] = '\0';
    remaining_token = strdup(execute);
    // printf("%s" , remaining_token);
    }
    int pid_r=atoi(remaining_token);
    if(kill(pid_r,SIGCONT)==-1){
        perror("Signal error");
        return;
    }  
    // int h =atoi(pid);
    // change(h , 1);
}