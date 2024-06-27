#include "headers.h"

extern Node* for_activities;
Node* createNode(pid_t process_id , char*process_name , int is_background)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->process_id = process_id;
    n->process_name = process_name;
    n->is_background = is_background;
    n->next = NULL;
    return n;
}
Node*createLinked()
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->next = NULL;
    return n;
}
Node* insert_Node(Node* L , pid_t process_id , char*process_name,int is_background)
{
    Node* t = createNode(process_id , process_name ,is_background);
    t->next =L->next;
    L->next = t;
    return L;
}

Node* delete_Node(Node*L)
{
    Node* i = L->next;
    Node*previous = L;
    while(i!=NULL)
    {
        int status;
        int check_for_background_process_completion = waitpid(i->process_id ,&status , WNOHANG);
        if(check_for_background_process_completion == i->process_id)
        {
            if (WIFEXITED(status))
            {
                printf("%s Exited Normally (%d)\n" , i->process_name , i->process_id);
            }
             else {
                perror("waitpid");
                return L;
            }
            previous->next = i->next;
            i=i->next;
        }
        else{

            previous = previous->next;
            i=i->next;
        }
    }
    return L;
}

Node* change(pid_t pid , int is_background)
{
    Node* i = for_activities->next;
    Node* previous = for_activities;
    while(i!=NULL)
    {
        if(i->process_id==pid)
        {
            if(i->is_background != is_background)
            {
                i->is_background = !i->is_background ;

            }
            else{
                printf("Can't switch the state of the process\n");
            }
            break;
        }
        i = i->next;
    }
    return for_activities ;
}

Node* activities_print()
{
    Node* i = for_activities->next ;
    Node* previous = for_activities;
    while(i!=NULL)
    {
        // // printf("Hemang\n");
        // if(kill(i->process_id , 0)==0)
        // {
        //     printf("%d \t:  %s - Running\n" , i->process_id , i->process_name);
        // }
        // else{
        //     printf("%d \t:  %s - Stopped\n" , i->process_id , i->process_name);
        // }
        // previous = previous->next;
        //     i=i->next;

            int status;
            // int stat=waitpid(i->process_id,&status,WNOHANG);
        if(waitpid(i->process_id,&status,WNOHANG)==0){
            printf("%d : ",i->process_id);
            printf("%s - ",i->process_name);
            
            char* proc_path=(char*)malloc(sizeof(char)*53);
            snprintf(proc_path,53,"/proc/%d/stat",i->process_id);
            // printf("%s\n",proc_path);
            FILE*file_ptr = NULL;
            file_ptr=fopen(proc_path,"r");
            if(file_ptr==NULL)
            {
                perror("Unable to open file");
                break;
            }
            char* received_bytes = (char*)malloc(sizeof(char)* 1024);
            int index = 0;  
            char thirdElements[400][1025];
            while (fgets(received_bytes,1024, file_ptr)) {
               
                // printf("%s\n" , received_bytes);
                char *token = strtok_r(received_bytes, " \t\n" , &received_bytes);

                int count = 0;
                while (token != NULL) {
                    if (count == 2) { 
                        strcpy(thirdElements[index], token); 
                        index++;
                        break; 
                    }
                    token = strtok_r(received_bytes, " \t\n" , &received_bytes);
                    count++;
                }
                // printf("%s\n" , thirdElements[0]);
            
            }
            // printf("\n");
            // printf("%s\n" ,thirdElements[0] );
            if(thirdElements[0][0]=='R' || thirdElements[0][0]=='S'){
                printf("Running\n");
            }
            else{
                printf("Stopped\n");
            }
            i=i->next;
            previous = previous->next;
        }
        else{
            previous->next = i->next;
            i=i->next;
        }
        
    }
    return for_activities;
}

Node* insert_for_activities(pid_t process_id , char*process_name , int is_background )
{
    Node* t = createNode(process_id , process_name ,is_background);
    Node* i = for_activities->next;
    Node* previous = for_activities;
    while(i!=NULL)
    {
        char str1[20];
        snprintf(str1 ,20,"%d" , process_id);
        char str2[20];
        snprintf(str2 ,20,"%d" , i->process_id);
        if(strcmp(str1 , str2)<=0)
        {
            break;
        }
        previous =i ;
        i=i->next;
    }
    previous->next = t;
    t->next = i;
    return for_activities;
}