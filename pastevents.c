#include "headers.h"

extern Node* for_activities;
// extern char*input_string;

char* replaceSubstring(char *str, const char *oldSubstr,  char *newSubstr) {
    char *pos = strstr(str, oldSubstr);

    if (pos != NULL) {
        int oldLen = strlen(oldSubstr);
        int newLen = strlen(newSubstr);
        int tailLen = strlen(pos + oldLen);

        memmove(pos + newLen, pos + oldLen, tailLen + 1);
        memcpy(pos, newSubstr, newLen);
        int i=0 ,c=0; 
        char*hemang = (char*)malloc(sizeof(char)*4097);
        // printf("%s" , newSubstr);
        while(newSubstr[i]!='\0')
        {
            if(newSubstr[i]!='\n')
            {
                hemang[c++] = newSubstr[i];
            }
            i++;
        }
        // hemang[c]  = '\n';
        return hemang;
        // printf("%s" , hemang);
    }
}

char * replace(char* new , char* old , char* str)
{
    char* hemang = (char* )calloc(4097 , sizeof(char));
    int it =0;
    char* occ1 = strstr(str , old);
    if(occ1==NULL)
    {
        exit(1);
    }
    int pos = occ1 -str;
    for(int i=0 ; i< pos ; i++)
    {
        hemang[it++] = str[i];
    }
    int c=0;
    while(new[c]!='\0')
    {
        hemang[it++] = new[c++];
    }
    int len1 = strlen(str);
    int len2 = strlen(old);
    pos = pos+ len2;
    while(str[pos]!='\0')
    {
        hemang[it++] = str[pos++];
    }
    hemang[it]='\0';
    return hemang;
}





char* pastevents(int* include_in_history ,Que*Q  , char*remaining_token_2  , char*root_directory , char* previous_directory , int* changes_in_directory , Node*L ,int* system_call_time , char*command)
{
    // int outdirect =0;
    // char *execute = (char*)calloc(4097 , sizeof(char));
    // if(strchr(remaining_token_2 , '<') || strchr(remaining_token_2, '>'))
    // {
    //     char cmd[4097] , res[4097];
    //     strcpy(cmd, remaining_token_2);
    //     strcpy(res,remaining_token_2);
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
    // remaining_token_2 = strdup(execute);
    // // printf("%s" , remaining_token);
    // }
    // printf("%s" , input_string);
    if(remaining_token_2==NULL)
    {
        for(int i=Q->rear ; i>=Q->front ; i--)
        {
            printf("%s" , Q->arr[i]);
        }
        *include_in_history =0;
        return remaining_token_2;
    }
    while(1)
    {
        char* tokenize = strtok_r(remaining_token_2 , " \n\t" , &remaining_token_2 );
        if(tokenize==NULL)
        {
            for(int i=Q->rear ; i>=Q->front ; i--)
            {
                printf("%s" , Q->arr[i]);
            }
            // printf("Hemang\n");
            *include_in_history =0;
            // printf("%s\n" , remaining_token_2);
            return remaining_token_2;
        }
        else if(strcmp(tokenize , "purge")==0)
        {
            while(!IsEmpty(Q))
            {
                pop(Q);
            }
            *include_in_history = 0;
            return remaining_token_2;
        }
        else if(strcmp(tokenize , "execute")==0)
        {
            char* index_to_token = strtok_r(remaining_token_2 , " \n\t" , &remaining_token_2 );
            char number[3];
            int i=0 ,c=0;
            while(index_to_token[i]!='\0')
            {
                if(index_to_token[i]>='0'&& index_to_token[i]<='9')
                {
                    number[c++] = index_to_token[i];
                }
                i++;
            }
            int number_to_execute = atoi(number);
            int count = number_to_execute;
            int value = Q->rear +1;
            while(count--)
            {
                value--;
            }
            
            if(value>=0 && number_to_execute<=15)
            {
                char* event_to_manipulate =strdup(Q->arr[value]);
                event_to_manipulate[strlen(event_to_manipulate) -1] = '\0';
                // printf("%s" , event_to_manipulate);
                char original_substring[] = "pastevents execute ";
                strcat(original_substring , number);
                char* cht = strdup(input_string);
                char* cht2 = strdup(input_string);
                // printf("%s\n" , input_string);
                replaceSubstring(cht2 , original_substring , event_to_manipulate);
                // printf("%s\n" , event_to_manipulate);
                // printf("%s\n" , input_string);
                 char* gu =replace(event_to_manipulate , original_substring , cht);
                strcpy(input_string , gu);
                // printf("%s\n" , input_string);


            int background =0;
            char*remaining_token_semicolon = event_to_manipulate;
            while(1)
            {
                // printf("%s\n" , remaining_token_semicolon);
                char*token_separating_semicolon = strtok_r(remaining_token_semicolon , ";\n" , &remaining_token_semicolon);
                // printf("%s\n" , token_separating_semicolon);
                if(token_separating_semicolon==NULL)
                {
                    break;
                }
                while(1)
                {
                    char token_remember[4097] ;
                    strcpy(token_remember , token_separating_semicolon); 
                    // printf("%s\n" , remaining_token_semicolon);
                    char*token_separating_and = strtok_r(token_separating_semicolon , "&" , &token_separating_semicolon);
                    // printf("%s\n" , token_separating_and);
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
                    // printf("%d\n" , background);
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
                            remaining_token = piping(remaining_token ,root_directory ,previous_directory ,changes_in_directory , system_call_time , command, L ,include_in_history  , changes_in_directory ,Q   , system_call_time);
                            // printf("Jain\n");
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
                        if(redirect(ff  , root_directory , previous_directory , changes_in_directory,include_in_history , L , system_call_time , command , Q )==0)
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
                    else if(strcmp(token,"warp")==0)
                    {
                        remaining_token = warp(remaining_token , root_directory ,changes_in_directory , previous_directory);
                    }
                    else if(strcmp(token , "peek")==0)
                    {
                    remaining_token = peek(remaining_token , root_directory ,previous_directory);
                    }
                    else if(strcmp(token , "seek")==0)
                    {
                        remaining_token = seek(root_directory , remaining_token , changes_in_directory , previous_directory);
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
                            if(redirect(ff  , root_directory , previous_directory , changes_in_directory,include_in_history , L , system_call_time , command , Q )==0)
                                return 0;
                            remaining_token=NULL;
                            // pause();                           
                            break;
                        }
                        else{
                            // printf("%s\n" ,remaining_token );
                        remaining_token = system_calls(token , background , remaining_token ,system_call_time , command , L , include_in_history , 0);
                        }
                    }
                    }
                }
            }

            }
            else if(number_to_execute>15){
                *include_in_history =0;
                printf("More then 15 events are not stored in database\n");
            }
            else{
                *include_in_history =0;
                printf("Less Than %d events are executed\n" , number_to_execute);
            }
            return remaining_token_2;
        }

    }

}