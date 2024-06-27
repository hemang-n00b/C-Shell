#include "headers.h"

int st_to_number(char * st)
{
    int length=0;
    for(int i=0;i<strlen(st);i++)
    {
        length=length*10 + ((int)st[i]-48);
    }
    return length;
}

char* proclure(char* remaining_token , char*root_directory)
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
    int pgrp,tpgid,pid,vm_size;
    char status,fg_bg;
    char*index_to_token = strtok_r(remaining_token , " \t\n" , &remaining_token);
    // printf("Hemang\n");
    if(index_to_token ==NULL)
    {
        pid = getpid();
        char executable_path_dir[4097];
        snprintf(executable_path_dir,sizeof(executable_path_dir),"/proc/%d/exe",pid);
        char *final_exe = (char *)calloc(4097,sizeof(char));
        char *executable_path=(char *)calloc(4097,sizeof(char));
        ssize_t n_bytes=readlink(executable_path_dir,executable_path,4097-1);
        if(n_bytes!=1)
        {
            if(strncmp(root_directory , executable_path , strlen(root_directory))==0)
            {
                int i=strlen(root_directory);
                int curr=1;
                final_exe[0] = '~';
                while(executable_path[i]!='\0')
                {
                    final_exe[curr++]= executable_path[i];
                    i++;
                }
            }
            else{
                strcpy(final_exe ,executable_path );
            }
            
        }
        else
        {
            printf("error\n");
            return NULL;
        }
        char stat_path[4097];
        snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
        FILE *fid = fopen(stat_path, "r");
        if (fid == NULL)
        {
            printf("error opening file\n");
            return NULL;
        }
        char *stat_file=(char *)calloc(sizeof(char),5000);
        while (fgets(stat_file, 5000, fid))
        {
            char **list = (char **)malloc(sizeof(char *) * 52);
            for (int i = 0; i < 52; i++)
            {
                list[i] = (char *)calloc(30,sizeof(char));
            }
            int to_count=0;
            char *token = strtok(stat_file, " :\t\n\0");
            while (token != NULL)
            {
                list[to_count++] = token;
                token = strtok(NULL," :\t\n\0");
            }
            status=list[2][0];
            vm_size=st_to_number(list[22]);
            pgrp=st_to_number(list[4]);
            tpgid=st_to_number(list[7]);
        }
        fclose(fid);
        if(pgrp!=tpgid)
        {
            fg_bg='-';
        }
        else
        {
            fg_bg='+';
        }   

        printf("pid : %d\n",pid);
        printf("process status : %c%c\n",status,fg_bg);
        printf("Process group : %d\n",pgrp);
        printf("Virtual Memory : %d KB\n",vm_size/1024);
        printf("Executable path : %s\n",final_exe);
    }
    else{
        char number[11];
        int i=0 ,curr=0;
        while(index_to_token[i]!='\0')
        {
            if(index_to_token[i]>='0'&& index_to_token[i]<='9')
            {
                number[curr++] = index_to_token[i];
            }
            i++;
        }
        int number_to_execute = atoi(number);
        pid = number_to_execute;
        char executable_path_dir[4097];
        snprintf(executable_path_dir,sizeof(executable_path_dir),"/proc/%d/exe",pid);
        char *final_exe=(char *)calloc(4097,sizeof(char));
        char *executable_path=(char *)calloc(4097,sizeof(char));
        ssize_t n_bytes=readlink(executable_path_dir,executable_path,4097-1);
        // printf("%s\n" , executable_path);
        if(n_bytes!=1)
        {
            if(strncmp(root_directory , executable_path , strlen(root_directory))==0)
            {
                int i=strlen(root_directory);
                int curr=1;
                final_exe[0] = '~';
                while(executable_path[i]!='\0')
                {
                    final_exe[curr++]= executable_path[i];
                    i++;
                }
            }
            else{
                strcpy(final_exe ,executable_path );
            }
            
        }
        else
        {
            printf("error\n");
            return NULL;
        }
        char stat_path[4097];
        snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
        FILE *fid = fopen(stat_path, "r");
        if (fid == NULL)
        {
            printf("error opening file\n");
            return NULL;
        }
        char *stat_file=(char *)calloc(sizeof(char),5000);
        while (fgets(stat_file, 5000, fid))
        {
            char **list = (char **)malloc(sizeof(char *) * 60);
            for (int i = 0; i < 52; i++)
            {
                list[i] = (char *)calloc(40,sizeof(char));
            }
            int to_count=0;
            char *token = strtok(stat_file," :\t\n\0");
            while (token != NULL)
            {
                list[to_count++] = token;
                token = strtok(NULL," :\t\n\0");
            }
            status=list[2][0];
            vm_size=st_to_number(list[22]);
            pgrp=st_to_number(list[4]);
            tpgid=st_to_number(list[7]);
        }
        fclose(fid);
        if(pgrp!=tpgid)
        {
            fg_bg='-';
        }
        else
        {
            fg_bg='+';
        }   

        printf("pid : %d\n",pid);
        printf("process status : %c%c\n",status,fg_bg);
        printf("Process group : %d\n",pgrp);
        printf("Virtual Memory : %d KB\n",vm_size/1024);
        printf("Executable path : %s\n",final_exe);

    }
    return remaining_token;
}

