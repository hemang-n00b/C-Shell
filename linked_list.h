#ifndef _LINKED_LIST_
#define _LINKED_LIST_
#include "headers.h"

typedef struct Node{
    struct Node*next;
    pid_t process_id ; 
    char* process_name;
    int is_background;
}Node;

Node* change(pid_t pid , int is_background);
Node* createNode(pid_t process_id , char*process_name , int is_background);
Node*createLinked();
Node* insert_Node(Node*L , pid_t process_id , char*process_name , int is_background);
Node* delete_Node(Node*L);
Node* insert_for_activities( pid_t process_id , char*process_name ,int is_background);
Node* activities_print();



#endif