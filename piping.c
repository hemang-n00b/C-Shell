#include "headers.h"

extern char* input_string;
char* piping(char* remaining_token , char* root_directory , char*previous_directory , int*changes , int*final_time , char*command , Node*L ,int*include_in_history , int*changes_in_directory  ,Que*Q  ,int* system_call_time )
{
    int iterator=0;
    int count =0 ;
    char gg[4097];
    while(remaining_token[iterator]!='\0')
    {
        if(remaining_token[iterator]=='|')
        {
            count++;
        }
        iterator++;
    }
    char *token = strtok_r(remaining_token, "|", &remaining_token);
        int original_output = dup(STDOUT_FILENO);
    int original_input = dup(STDIN_FILENO);
    int current_pipe[2];
    int previous_pipe[2];
 
    for (int i = 0; i < count; i++)
    {
    // printf("%s\n" , remaining_token);
        if (pipe(current_pipe) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
 
        pid_t pid;
 
        if ((pid = fork()) == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
 
        if (pid == 0)
        {                           
            close(current_pipe[0]); 
 
            
            if (i > 0)
            {
                if (dup2(previous_pipe[0], STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(previous_pipe[0]);
            }
 
            if (dup2(current_pipe[1], STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
        strcpy(gg ,token);
        char * basic = strtok_r(token , " \t\n" ,&token );
            if(strchr(token, '<')!=NULL || strchr(token , '>')!=NULL)
            {
                // printf("%s\n" , gg);
                if(redirect(gg , root_directory , previous_directory , changes_in_directory ,include_in_history , L ,system_call_time , command ,Q )==0)
                    return 0;                   
            }
            else if(strcmp(basic , "iMan")==0)
            {
                token = iman(token);
            }
            else if(strcmp(basic , "peek")==0)
            {
                token= peek(token , root_directory ,previous_directory);
            }
            else if(strcmp(basic , "warp")==0)
            {
                token= warp(token, root_directory ,changes_in_directory , previous_directory);
            }
            else if(strcmp(basic , "activities")==0)
            {
                token = activities(token );
            }
            else if(strcmp(basic , "fg")==0)
            {
                fg(token);
                token = NULL;
            }
            else if(strcmp(basic , "bg")==0)
            {
                bg(token);
                token = NULL ;
            }
            else if(strcmp(basic, "neonate")==0)
            {
                neonate(token);
                token =NULL ;
            }
            else if(strcmp(basic , "seek")==0)
            {
                token = seek(root_directory , token , changes_in_directory , previous_directory);
                // printf("%s" , remaining_token);
            }
            else if(strcmp(basic, "proclore")==0)
            {
                token = proclure(token , root_directory);
            }
            else if(strcmp(basic , "ping")==0)
            {
                token = ping(token);
            }
            else if(strcmp(basic , "pastevents")==0)
            {
            // printf("%s\n" , input_string);
                token = pastevents(include_in_history , Q , token , root_directory , previous_directory , changes_in_directory , L , system_call_time , command );
            // printf("%s\n" , input_string);

            }
            else{
            system_calls2(basic , token);
            }
            exit(EXIT_SUCCESS); 
        }
        else
        {                           
            wait(NULL);
            close(current_pipe[1]); 
            if (i > 0)
            {
                close(previous_pipe[0]); 
            }
 
            previous_pipe[0] = current_pipe[0];
            previous_pipe[1] = current_pipe[1];
 
        }
        // printf("%s\n" , remaining_token );
        token = strtok_r(remaining_token, "|", &remaining_token);
        // printf("%s\n" , token );    

    }
        // printf("%s\n" , token );    
    if (dup2(original_output, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
 
    if (dup2(previous_pipe[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(previous_pipe[0]);
    strcpy(gg ,token);
    char * basic = strtok_r(token , " \t\n" ,&token );
    // strcpy(return_from_tokenize, tokenize(username, systemname, homedir, pipe_list[pipe_count], prevdir, q, bg_check, head));
    if(strchr(token, '<')!=NULL || strchr(token , '>')!=NULL)
    {
        // printf("%s\n" , gg);
        if(redirect(gg , root_directory , previous_directory , changes_in_directory,include_in_history , L , system_call_time , command , Q )==0)
            return 0;                   
    }
    else if(strcmp(basic , "peek")==0)
    {
        token = peek(token, root_directory ,previous_directory);
    }
    else if(strcmp(basic , "warp")==0)
    {
        token= warp(token, root_directory ,changes_in_directory , previous_directory);
    }
    else if(strcmp(basic , "iMan")==0)
    {
        token = iman(token);
    }
    else if(strcmp(basic, "neonate")==0)
    {
        neonate(token);
        token =NULL ;
    }
    else if(strcmp(basic , "activities")==0)
    {
        token = activities(token );
    }
    else if(strcmp(basic , "fg")==0)
    {
        fg(token);
        token = NULL;
    }
    else if(strcmp(basic , "bg")==0)
    {
        bg(token);
        token = NULL ;
    }
    else if(strcmp(basic , "seek")==0)
    {
        token = seek(root_directory , token , changes_in_directory , previous_directory);
        // printf("%s" , remaining_token);
    }
    else if(strcmp(basic, "proclore")==0)
    {
        token = proclure(token , root_directory);
    }
    else if(strcmp(basic , "ping")==0)
    {
        token = ping(token);
    }
    else if(strcmp(basic , "pastevents")==0)
    {
        // printf("%s\n" , input_string);
        token = pastevents(include_in_history , Q  , token , root_directory , previous_directory , changes_in_directory , L , system_call_time , command );

    }
    else{
    system_calls2(basic , token);
    }
    if (dup2(original_input, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
        // printf("%s\n" , input_string);
}
