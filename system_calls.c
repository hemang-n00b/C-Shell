#include "headers.h"

extern Node* for_activities;
extern int child_pid_global;

int redirect(char* remaining_token , char* root_directory , char* previous_directory , int* changes_in_directory , int* include_in_history, Node*L ,int* system_call_time , char*command ,Que*Q )
{
    int output_re = dup(STDOUT_FILENO);
    int input_re = dup(STDIN_FILENO);
    char cmd[4097] , res[4097];
    strcpy(cmd, remaining_token);
    strcpy(res,remaining_token);
    char outputfile[4097], inputfile[4097], buf[4097], filename[4097];
    int prevfile = 0, append = 0, i, indirect = 0, outdirect = 0;
    char *execute = (char*)calloc(4097 , sizeof(char));
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
    execute[i] = '\0';
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
    if (outdirect == 1 && indirect == 1)
    {
        // if(imp==0)
        // {
            int inp = open(inputfile, O_RDONLY);
            if (inp < 0)
            {
                perror("Input file not opening");
                return 0;
            }
            dup2(inp, STDIN_FILENO);
            close(inp);

        // }
        int out;
        if (append == 1)
        {
            out = open(outputfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
            if (out < 0)
            {
                perror("Outputfile not working");
                return 0;
            }
        }
        else
        {
            out = open(outputfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (out < 0)
            {
                perror("Outputfile not working");
                return 0;
            }
        }
        dup2(out, STDOUT_FILENO);
        close(out);
    }

    else if (outdirect == 1)
    {
        int out;
        if (append == 1)
        {
            out = open(outputfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
            if (out < 0)
            {
                perror("Outputfile not working");
                return 0;
            }
        }
        else
        {
            out = open(outputfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (out < 0)
            {
                perror("Outputfile not working");
                return 0;
            }
        }
        dup2(out, STDOUT_FILENO);
        close(out);
    }
    else
    {
        // if(imp ==0)
        // {
            int inp = open(inputfile, O_RDONLY);
            if (inp < 0)
            {
                perror("Input file not opening");
                return 0;
            }
            dup2(inp, STDIN_FILENO);
            close(inp);
        // }
        // printf("Hemang\n%s\n" , inputfile);
    }
    char* basic = strtok_r(execute , " \t\n" , &execute);
    if(strcmp(basic , "peek")==0)
    {
        execute = peek(execute , root_directory ,previous_directory);
    }
    else if(strcmp(basic , "warp")==0)
    {
        execute= warp(execute, root_directory ,changes_in_directory , previous_directory);
    }
    else if(strcmp(basic , "iMan")==0)
    {
        execute = iman(execute);
    }
    else if(strcmp(basic, "neonate")==0)
    {
        neonate(execute);
        execute =NULL ;
    }
    else if(strcmp(basic , "activities")==0)
    {
        execute= activities(execute);
    }
    else if(strcmp(basic , "fg")==0)
    {
        fg(execute);
        execute = NULL;
    }
    else if(strcmp(basic , "bg")==0)
    {
        bg(execute);
        execute = NULL ;
    }
    else if(strcmp(basic , "seek")==0)
    {
        basic = seek(root_directory , basic , changes_in_directory , previous_directory);
        // printf("%s" , remaining_token);
    }
    else if(strcmp(basic, "proclore")==0)
    {
        basic = proclure(basic , root_directory);
    }
    else if(strcmp(basic , "ping")==0)
    {
        basic = ping(basic);
    }
    else if(strcmp(basic , "pastevents")==0)
    {
        execute = pastevents(include_in_history , Q  , token , root_directory , previous_directory , changes_in_directory , L , system_call_time , command );
    }
    else{

    system_calls2(basic, execute );
    }
    

    dup2(output_re , STDOUT_FILENO);
    dup2(input_re , STDIN_FILENO);

    // if(strcmp(y , "warp")==0)
    // {
    //     warp(execute , "/home/hemangjain/Downloads/Hemang ka OSN1/MINI_1/tp");
    // }
    // else{

    // }
    // printf("%s\n" , y);
    return 1;
}

void system_calls2(char*token , char*remaining_token)
{
    int status;
    char*cmd = strdup(token);
    char*args[4097];

    if((strcmp(token , "echo")==0 || strcmp(token , "grep")==0) && strchr(token , '"')!=NULL)
    {
        args[0]=token;
        remaining_token[strlen(remaining_token)-1] = '\0';
        int t =0;
        int c = 0;
        char final [4097];
        while(remaining_token[t]!='\0')
        {
            if(remaining_token[t]!='"' && remaining_token[t]!='\n')
            {
                final[c++] = remaining_token[t];
            }
            t++;
        }
        args[1] = final;
        // printf("%s\n%s" , args[0] , args[1]);
        args[2] = NULL;
    }
    else{

        int i=0 ;
        while(token!=NULL)
        {
            args[i] = token;
            token= strtok_r(remaining_token ," \t\n" , &remaining_token);
            i++;
        }
        args[i] = NULL;
    }
    
    pid_t child_pid = fork();
    child_pid_global = child_pid ;
    if(child_pid ==0)
    {
    // printf("Hemang\n");
        // if(setpgid(0,0)==-1)
        // {
        //     perror("setgpid");
        //     exit(EXIT_FAILURE);
        // }
        execvp(args[0],args );
        perror("execvp");
    }
    else if(child_pid<0)
    {
        perror("fork");
    }
    else{
        pid_t terminated_child_pid = waitpid(child_pid, &status, 0);
        // waitpid(child_pid , &status , WUNTRACED);
    }
}



char* system_calls(char*token , int background , char*remaining_token , int*final_time , char*command , Node*L ,int* include_in_history , int is_piped)
{
    // printf("%s\n" , token);
    char*store = strdup(token);
    char*store2 = strdup(token);
    if(background==0)
    {
        strcpy(command,token);
    }
    char initial_command[4097] ;
    // clock_t start_time , end_time;
    strcpy(initial_command , token);
    struct timespec start_time, end_time;
    char*args[4097];
    // printf("%s\n" , token);
    if((strcmp(token , "echo")==0 || strcmp(token , "grep")==0 || strcmp(token,"sed")==0 ) && strchr(token , '"')!=NULL)
    {
        args[0]=token;
        // remaining_token[strlen(remaining_token)-1] = '\0';
        // printf("%s\n" , remaining_token);
        int t =0;
        int c = 0;
        char final [4097];
        while(remaining_token[t]!='\0')
        {
            if(remaining_token[t]!='"' && remaining_token[t]!='\n')
            {
                final[c++] = remaining_token[t];
            }
            t++;
        }
        final[c] = '\0';
        // printf("%s\n" , final);
        args[1] = final;
        // printf("%s\n%s" , args[0] , args[1]);
        args[2] = NULL;
    }
    else{

        int i=0 ;
        while(token!=NULL)
        {
            args[i] = token;
            token= strtok_r(remaining_token ," \t\n" , &remaining_token);
            i++;
        }
        args[i] = NULL;
    }
    pid_t child_pid = fork();
    // start_time = clock();
    if(background ==0)
    {
        child_pid_global = child_pid ;
    }
    if(child_pid>0)
    {
        for_activities = insert_for_activities( child_pid ,store2 , background);
    }
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    // printf("Hemang\n");
    if(child_pid ==0)
    {
        // printf("Inside execvp\n");

        if(setpgid(0,0)==-1)
        {
            perror("setgpid");
            exit(EXIT_FAILURE);
        }

        execvp(initial_command,args );
        // *include_in_history = 0;
        perror("execvp");
    }
    else if(child_pid<0)
    {
        perror("fork");
    }
    else{
        if(background==0)
        {
            int status;
            double cpu_time_used;
            // printf("Foreground\n");
            // pid_t terminated_child_pid = waitpid(child_pid, &status, 0);
            waitpid(child_pid , &status , WUNTRACED);
            clock_gettime(CLOCK_MONOTONIC, &end_time);    
            int elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                   (end_time.tv_nsec - start_time.tv_nsec) / 1.0e9;
            // end_time = clock();
            // printf("%ld\n%ld\n" , start_time - end_time , CLOCKS_PER_SEC);
            // cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
            (*final_time) = (int)elapsed_time;
        }
        else{
            printf("%d\n" , child_pid);
            store[0] = (char)(store[0]-32);
            L = insert_Node(L , child_pid , store , background);
        }
    }
    // if(background==1)
    // {
    //     pid_t child_pid = fork();
    //     if(child_pid>0)
    //     {
    //         printf("%d" , child_pid);
    //         execvp(initial_command,args );
    //         perror("execvp");
    //         printf("( %d )" , child_pid);
    //     }
    // }
    // else{
    //     double cpu_time_used;
    //     clock_t start_time , end_time;
    //     start_time = clock();
    //     execvp(initial_command,args );
    //     perror("execvp");
    //     end_time = clock();
    //     cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    //     (*final_time) = (int)cpu_time_used;
    // }
    // printf("Hemang\n");
    return token;
}
