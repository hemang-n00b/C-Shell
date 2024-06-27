#include "headers.h"

extern Node* for_activities;
extern int child_pid_global;
extern jmp_buf env ;

char* ping(char* remaining_token)
{
    // int outdirect =0;
    // char *execute = (char*)calloc(4097 , sizeof(char));
    // if(strchr(remaining_token , '<') || strchr(remaining_token, '>'))
    // {
    //     char cmd[4097] , res[4097];
    //     strcpy(cmd, remaining_token);
    //     strcpy(res,remaining_token);
    //     char outputfile[4097], inputfile[4097], buf[4097], filename[4097];
    //     int prevfile = 0, append = 0, i, indirect = 0;
    //     char*remaining_files = (char*)malloc(sizeof(char)* 4097);
    //     int flag =0 ;
    //     for (i = 0; i < strlen(cmd); i++)
    //     {
    //         if (cmd[i] == '>' || cmd[i] == '<')
    //         {
    //             flag =1;
    //             break;
    //         }
    //         execute[i] = cmd[i]; 
    //     }
    //     // execute[i] = '\0';
    //     int c=0;
    //     while(i<strlen(cmd))
    //     {
    //         remaining_files[c++] = cmd[i++];
    //     }
    //     char* args[10];
    //     int t =0;
    //     char* token = strtok_r(remaining_files , " \t\n" , &remaining_files);
    //     while(token!=NULL)
    //     {
    //         args[t++] = token;
    //         token = strtok_r(remaining_files , " \t\n" , &remaining_files);
    //     }
    //     int tt=0;
    //     while(tt<t)
    //     {
    //         // printf("%s\n" , args[tt]);
    //         if(strcmp("<" , args[tt])==0)
    //         {
    //             indirect = 1;
    //             strcpy(inputfile ,args[tt+1]);
    //         }
    //         if(strcmp(">" , args[tt])==0)
    //         {
    //             outdirect = 1;
    //             strcpy(outputfile , args[tt+1]);
    //         }
    //         if(strcmp(">>" , args[tt])==0)
    //         {
    //             outdirect = 1;
    //             append =1;
    //             strcpy(outputfile , args[tt+1]);
    //         } 
    //         tt++;
    //     }
    //     // printf("%s\n\n" ,execute );
    //     if(indirect ==1)
    //     {
    //         FILE* input_pointer = fopen(inputfile , "r");
    //         if (input_pointer == NULL) {
    //             perror("Failed to open the file");
    //             return NULL;
    //         }
    //         char buffer[1024]; 
    //         while (fgets(buffer, sizeof(buffer), input_pointer) != NULL) {
    //             strcat(execute ,buffer);
    //         }
    //         fclose(input_pointer);
    //     }
    //     // printf("%s\n\n" , remaining_token);
    //     // printf("%s\n\n" ,execute );
    // // int insta=0;
    // // while(execute[insta]!='\0')
    // // {
    // //     remaining_token[insta] = execute[insta];
    // //     insta++;
    // // }
    // // remaining_token[insta] = '\0';
    // remaining_token = strdup(execute);
    // // printf("%s" , remaining_token);
    // }
    char* pid_str = strtok_r(remaining_token , " \t\n" , &remaining_token);
    char* signum_str = strtok_r(remaining_token , " \t\n" , &remaining_token);
    pid_t target_pid = atoi(pid_str);
    int signal_number = atoi(signum_str);

    if (target_pid <= 1) {
        fprintf(stderr, "Invalid PID: %d\n", target_pid);
        return remaining_token;
    }

    signal_number %= 32;
    
    if (kill(target_pid, signal_number) == 0) {
        printf("Sent signal %d to process with PID %d\n", signal_number, target_pid);
    } else {
        perror("Error sending signal");
        return remaining_token;
    }
    return remaining_token;
}

void ctrl_c_handler(int sig)
{
    printf("CTRL+C was pressed\n");
    // Node* i  = for_activities->next;
    // while(i!=NULL)
    // {
    //     if(i->is_background ==0)
    //     {
    //         if( kill(i->process_id , SIGINT)!=0)
    //         {
    //             perror("kill failed");
    //         }
    //         break;
    //     }
    //     i=i->next;
    // }
    if(child_pid_global!=-1)
    {
        kill( child_pid_global, SIGINT);
        child_pid_global =-1;
    }
        longjmp(env ,1);

}

void ctrl_d_handler(int sig)
{
    printf("CTRL+D was pressed\n");
    if(sig==SIGQUIT){
        kill(0,SIGKILL);
        exit(1);
        }
}

void ctrl_z_handler(int sig)
{
    printf("CTRL+Z was pressed\n");
    int flag=0;
    if(sig==SIGINT)
        flag=1;
    Node* i = for_activities->next;
    while(i!=NULL)
    {
        if(i->is_background==0)
        {
            kill(i->process_id,SIGTSTP);
            kill(i->process_id,SIGSTOP);
            i->is_background =1;
        }
        i=i->next;
    }
}