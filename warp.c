#include "headers.h"

char* warp(char*remaining_token , char*root_directory , int*changes , char*previous_directory_maintained)
{
    char previous_directory[4097];
    // char*previous_remaining_token;
    int flag =0;
    while(1)
    {
        char* token = strtok_r(remaining_token , " \t\n" , &(remaining_token));
        // printf("%c\n" , token[0]);
        if(token==NULL && flag==0)
        {
            (*changes)++;
            int change_in_directory = chdir(root_directory);
            if(change_in_directory !=0)
            {
                printf("Unable to change the directory\n");
                return NULL;
            }
            printf("%s\n" , root_directory);
        }
        if(token==NULL || strcmp(token , ";" )==0|| strcmp(token,"&")==0)
        {
            return remaining_token;
        }
        else if(token[0]=='~')
        {
            flag =1;
            (*changes)++;
            char* check_previous_directory = getcwd(previous_directory , 4097);
            char* new_directory_home= (char*)calloc(4097 , sizeof(char));
            int i=0 , j=0;
            while(root_directory[i]!='\0')
            {
                new_directory_home[j++] = root_directory[i++];
            }
            i=1;
            // printf("%s\n" , root_directory);
            // printf("%s\n" , new_directory_home);
            // printf("%s\n" , token);
            while(token[i]!='\0')
            {
                new_directory_home[j++] = token[i++];
            }
            int check_for_change_in_directory = chdir(new_directory_home);
            if(check_for_change_in_directory !=0)
            {
                printf("Unable to change the directory\n");
                return NULL;
            }
            printf("%s\n" ,new_directory_home );

        }
        else if(strcmp(token,"-")==0)
        {
            flag =1;
            if(*changes == 0)
            {
                printf("warp: OLDPWD not set\n");
            }
            else{
                char temp_cwd[4097];
                char* temp_directory = getcwd(temp_cwd , sizeof(temp_cwd));
                int check_for_change_in_directory = chdir(previous_directory);
                if(check_for_change_in_directory!= 0)
                {
                    printf("Unable to change the directory\n");
                    return NULL;
                }
                printf("%s\n" ,previous_directory );
                strcpy(previous_directory , temp_directory);
            }     
        }
        else{
            flag =1;
            (*changes)++;
            char new_directory[4097];
            char* check_previous_directory = getcwd(previous_directory , 4097);
            int check_for_change_in_directory = chdir(token);
            if(check_for_change_in_directory !=0)
            {
                printf("Unable to change the directory\n");
                return NULL;
            }
            printf("%s\n" ,getcwd(new_directory , sizeof(new_directory)));
        }

        // previous_remaining_token = remaining_token;
    }
    previous_directory_maintained = previous_directory ; 
}
