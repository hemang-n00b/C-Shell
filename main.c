#include "headers.h"


Node* for_activities;
int child_pid_global  ;
jmp_buf env ;
char*input_string;

int main()
{
    child_pid_global =-1;
    Node*L = createLinked(); 
    for_activities = createLinked();
    char root_directory[4097];
    char* root_directory_check = getcwd(root_directory , sizeof(root_directory));
    int changes_in_directory = 0;
    char*previous_directory;
    char filename[5000] ;
    snprintf(filename , 5000, "%s/folder/file.txt" , root_directory);
    // printf("%s\n" , filename);
    char command[4097];
    int*system_call_time = (int*)malloc(sizeof(int)) ;
    // if(child_pid_global!=-1 && kill(child_pid_global , 0)==0)
    // {
        if (signal(SIGINT, ctrl_c_handler) == SIG_ERR) {
            perror("signal");
            // return 1;
        }
    // }
    if (signal(SIGQUIT, ctrl_d_handler) == SIG_ERR) {
        perror("signal");
        // return 1;
    }
    if (signal(SIGTSTP, ctrl_z_handler) == SIG_ERR) {
        perror("signal");
        // return 1;
    }
    *system_call_time =0;
    sigsetjmp(env,1);
    while(1)
    {
        Que*Q = createQue();
        FILE* FilePointer = fopen(filename , "r");
        Q = ReadContent(FilePointer , Q);
        fclose(FilePointer);
        prompt(root_directory_check ,strlen(root_directory_check)  ,*(system_call_time) ,command);
        
        *system_call_time = 0;
        command[0]='\0';
        char input[4096];
        int include_in_history =1;
        int background =0;
        fgets(input, 4096, stdin);
        input_string =(char*)calloc(4097 , sizeof(char));
        strcpy(input_string , input);
        L = delete_Node(L);
        char*remaining_token_semicolon = strdup(input);
        while(1)
        {
            if(remaining_token_semicolon==NULL)
            {
                break;
            }
            char*token_separating_semicolon = strtok_r(remaining_token_semicolon , ";\n" , &remaining_token_semicolon);
            if(token_separating_semicolon==NULL)
            {
                break;
            }
            while(1)
            {
                if(token_separating_semicolon==NULL)
                {
                    break;
                }
                char token_remember[4097] ;
                strcpy(token_remember , token_separating_semicolon); 
                char*token_separating_and = strtok_r(token_separating_semicolon , "&" , &token_separating_semicolon);
                if(token_separating_and==NULL)
                {
                    break;
                }
                if(strcmp(token_separating_and ,token_remember )==0)
                {
                    background = 0;
                }
                else{
                    background = 1;
                }
                char* remaining_token = token_separating_and;
                while(1)
                {    
                    if(remaining_token==NULL)
                    {   
                        break;
                    }
                    int iterator =0;
                    int is_piped = 0;
                    while(remaining_token[iterator]!='\0')
                    {
                        if(remaining_token[iterator]=='|')
                        {
                            is_piped=1;
                            remaining_token = piping(remaining_token ,root_directory ,previous_directory ,&changes_in_directory , system_call_time , command, L ,&include_in_history  , &changes_in_directory ,Q   , system_call_time);
                            // printf("Jain\n");
                            // printf("%s\n" , input_string);

                            remaining_token =NULL;
                            break;
                        }
                        iterator++;
                    }
                    if(remaining_token==NULL)
                    {   
                        break;
                    }
                    char* ff = strdup(remaining_token);
                    
                    char* token = strtok_r( remaining_token, " \t\n" ,&remaining_token );
                    if(token==NULL)
                    {
                        break;
                    }
                    if(strchr(remaining_token, '<')!=NULL || strchr(remaining_token , '>')!=NULL)
                    {
                        // printf("%s\n" , ff);
                        if(redirect(ff  , root_directory , previous_directory , &changes_in_directory,&include_in_history , L , system_call_time , command , Q )==0)
                            return 0;
                        remaining_token=NULL;
                        // pause();                           
                        break;
                    }
                    else if(strcmp(token , "activities")==0)
                    {
                        remaining_token = activities(remaining_token );
                    }
                    else if(strcmp(token , "iMan")==0)
                    {
                        remaining_token = iman(remaining_token);
                        // printf("Hemang\n");
                    }
                    else if(strcmp(token , "fg")==0)
                    {
                        fg(remaining_token);
                        remaining_token = NULL ;
                    }
                    else if(strcmp(token , "bg")==0)
                    {
                        bg(remaining_token);
                        remaining_token = NULL ;
                    }
                    else if(strcmp(token , "pastevents")==0)
                    {
                        remaining_token = pastevents(&include_in_history , Q  , remaining_token , root_directory , previous_directory , &changes_in_directory , L , system_call_time , command );
                    }
                    else if(strcmp(token,"warp")==0)
                    {
                        remaining_token = warp(remaining_token , root_directory ,&changes_in_directory , previous_directory);
                    }
                    else if(strcmp(token , "peek")==0)
                    {
                    remaining_token = peek(remaining_token , root_directory ,previous_directory);
                    }
                    else if(strcmp(token , "seek")==0)
                    {
                        remaining_token = seek(root_directory , remaining_token , &changes_in_directory , previous_directory);
                        // printf("%s" , remaining_token);
                    }
                    else if(strcmp(token , "proclore")==0)
                    {
                        remaining_token = proclure(remaining_token , root_directory);
                    }
                    else if(strcmp(token , "ping")==0)
                    {
                        remaining_token = ping(remaining_token);
                    }
                    else if(strcmp(token , "neonate")==0)
                    {
                        neonate(remaining_token);
                        remaining_token =NULL ;
                    }
                    else{
                        if(strchr(remaining_token, '<')!=NULL || strchr(remaining_token , '>')!=NULL)
                        {
                            // printf("%s\n" , ff);
                            if(redirect(ff  , root_directory , previous_directory , &changes_in_directory,&include_in_history , L , system_call_time , command , Q )==0)
                                return 0;
                            remaining_token=NULL;
                            // pause();                           
                            break;
                        }
                        else{
                            // printf("%s\n" ,remaining_token );
                        remaining_token = system_calls(token , background , remaining_token ,system_call_time , command , L , &include_in_history , 0);
                        }
                    }
                }
            }
        }
        if(include_in_history ==1 && strcmp(show_rear(Q) , input_string)!=0 && strstr(input_string , "pastevents")==NULL)
        {
            // printf("%s\n" , input_string);
            Q = PushCommand(Q , input_string);
        }
        FILE* FilePointer_2 = fopen(filename , "w");
        WriteContent(FilePointer_2 , Q);
        fclose(FilePointer_2);
    }

    
}
