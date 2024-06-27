#include "headers.h"

char* iman(char* remaining_token)
{
    
    char*token = strtok_r(remaining_token , " \t\n" ,&remaining_token );
    char *host = "man.he.net"; 
    char page[4097];
    snprintf(page , 4097 , "http://man.he.net/?topic=%s&section=all" , token);
    

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *server = gethostbyname(host);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80); 


    if (server == NULL) {
        perror("Host error");
        // return 1;

        return remaining_token;
    }

    if (sockfd < 0) {
        perror("Socket error");
        // return 1;
        return remaining_token;

    }



    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection error");
        // return 1;
        return remaining_token;

    }

    char request[10097];
    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", page, host);
    // printf("%s\n" , request);
    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("Request sending error");
        // return 1;
        return remaining_token;

    }

    char response[4097];
    ssize_t bytes_received;
    int flag=0;
    while ((bytes_received = recv(sockfd, response, sizeof(response), 0)) > 0) {
        // printf("%s" , response);
        int iterator=0;
        if(flag ==1)
        {
            char* to_break = strstr(response , "AUTHOR");
            if(to_break!=NULL)
            {
                for(int i=0 ; i<to_break - response ; i++)
                {
                    printf("%c" , response[i]);
                }
                break;
            }
        }
        char* result = strstr(response , "NAME\n");
        if(result!=NULL)
        {
            flag = 1;
            char* to_break = strstr(result , "AUTHOR");
            if(to_break!=NULL)
            {
                for(int i=0 ; i<to_break - result ; i++)
                {
                    printf("%c" , result[i]);
                }
                break;
            }
            else{
                printf("%s" , result);
            }
        }       
    }
    if(flag==0)
    {
        printf("ERROR\n\tNo such command\n");
    }

    if (bytes_received < 0) {
        perror("Response receiving error");
        // return 1;
        return remaining_token;

    }
    close(sockfd);

    return remaining_token;
}