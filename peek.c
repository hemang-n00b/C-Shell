#include "headers.h"

char* peek(char* remaining_token , char* root_directory , char*previous_directory)
{

    int flag = 0;
    char*file_path=NULL;
    char*previous_token=NULL;
    int a=0 , l=0; 
    while(1)
    {
        char* token = strtok_r(remaining_token , " \t\n" , &remaining_token);
        if(token==NULL)
        {
            if(flag==1){

                return remaining_token;
            }
            else{
                flag=1;
                char present_directory_home[4097];
                char*new_directory = getcwd(present_directory_home , sizeof(present_directory_home));
                int check_for_change_of_directory = chdir(new_directory);
                if(check_for_change_of_directory != 0)
                {
                    printf("Unable to change the directory\n");
                    return NULL;
                }
                struct dirent **namelist;
                int check_to_whether_scandir_works = scandir(new_directory, &namelist, NULL, alphasort);
                if(check_to_whether_scandir_works<0)
                {
                    printf("Unable to implement scandir\n");
                    return remaining_token;
                }
                if(a==0 && l==0)
                {
                    for(int i=0 ; i< check_to_whether_scandir_works; i++)
                    {
                        if(namelist[i]->d_name[0]!='.')
                        {
                            char path[8195];
                            snprintf(path, sizeof(path), "%s/%s", new_directory, namelist[i]->d_name);
                            struct stat file_stat;
                            if(stat(path , &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            if(S_ISDIR(file_stat.st_mode))
                                printf("\033[34m%s\033[0m" , namelist[i]->d_name);
                            else if(file_stat.st_mode & S_IXUSR)
                                printf("\033[32m%s\033[0m" , namelist[i]->d_name);
                            else{
                                printf("%s" , namelist[i]->d_name);
                            }
                            printf("\n");
                        }
                    }
                }
                else if(a==1 && l==0)
                {
                    for(int i=0 ; i< check_to_whether_scandir_works; i++)
                    {
                        char path[8195];
                            snprintf(path, sizeof(path), "%s/%s", new_directory, namelist[i]->d_name);
                            struct stat file_stat;
                            if(stat(path , &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            if(S_ISDIR(file_stat.st_mode))
                                printf("\033[34m%s\033[0m" , namelist[i]->d_name);
                            else if(file_stat.st_mode & S_IXUSR)
                                printf("\033[32m%s\033[0m" , namelist[i]->d_name);
                            else{
                                printf("%s" , namelist[i]->d_name);
                            }
                            printf("\n");                      
                    }
                // printf("Hemang\n");
                }
                else if(a==0 && l==1)
                {
                    DIR*directory = opendir(new_directory);
                    if(directory==NULL)
                    {
                        printf("No such directory exists.\n");
                        return remaining_token;
                    }
                struct dirent **namelist;
                    int n = scandir(new_directory, &namelist, NULL, alphasort);
                    for(int i=0 ; i<n ; i++)
                    {
                        if (namelist[i]->d_name[0] != '.') {
                            char path[8195];
                            snprintf(path, sizeof(path), "%s/%s", new_directory, namelist[i]->d_name);
                            struct stat file_stat;
                            if(stat(path , &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
                            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
                            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
                            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

                            struct passwd *user_info = getpwuid(file_stat.st_uid);
                            struct group *group_info = getgrgid(file_stat.st_gid);
                            printf(" %2lu %8s %8s %8ld ", (unsigned long)file_stat.st_nlink , user_info ? user_info->pw_name : "" , group_info ? group_info->gr_name : "" , (long)file_stat.st_size);

                            char time_str[30];
                            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                            printf("%s \t", time_str);
                            if(S_ISDIR(file_stat.st_mode))
                                printf("\033[34m%s\033[0m" , namelist[i]->d_name);
                            else if(file_stat.st_mode & S_IXUSR)
                                printf("\033[32m%s\033[0m" , namelist[i]->d_name);
                            else{
                                printf("%s" , namelist[i]->d_name);
                            }
                            printf("\n");
                        }
                    }
                }
                
                else{
                    DIR*directory = opendir(new_directory);
                    if(directory==NULL)
                    {
                        printf("No such directory exists.\n");
                        return remaining_token;
                    }
                struct dirent **namelist;
                int n = scandir(new_directory, &namelist, NULL, alphasort);
                    for(int i=0 ; i<n ; i++) {
                            char path[8195];
                            snprintf(path, sizeof(path), "%s/%s", new_directory, namelist[i]->d_name);
                            struct stat file_stat;
                            if(stat(path , &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
                            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
                            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
                            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

                            struct passwd *user_info = getpwuid(file_stat.st_uid);
                            struct group *group_info = getgrgid(file_stat.st_gid);
                            printf(" %2lu %8s %8s %8ld ", (unsigned long)file_stat.st_nlink , user_info ? user_info->pw_name : "" , group_info ? group_info->gr_name : "" , (long)file_stat.st_size);

                            char time_str[30];
                            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                            printf("%s \t", time_str);
                            if(S_ISDIR(file_stat.st_mode))
                                printf("\033[34m%s\033[0m" , namelist[i]->d_name);
                            else if(file_stat.st_mode & S_IXUSR)
                                printf("\033[32m%s\033[0m" , namelist[i]->d_name);
                            else{
                                printf("%s" , namelist[i]->d_name);
                            }
                            printf("\n");
                        
                    }
                }
                return remaining_token;
            }
        }
        if(strcmp(token , "-l")==0)
        {
            l=1;
        }
        else if(strcmp(token , "-a")==0)
        {
            a=1;
        }
        else if(strcmp(token , "-al")==0 || strcmp(token , "-la")==0)
        {
            l=1;
            a=1;
        }        
        else{
            flag=1;
            char* remaining_file_path = file_path;
                if(token==NULL)
                {
                    break;
                } 
                char present_directory[4097];
                char*check_present_directory = getcwd(present_directory ,sizeof(present_directory));
                char new_directory[4097];
                if(token[0]=='~')
                {
                    int i=0 , j=0;
                    while(root_directory[i]!='\0')
                    {
                        new_directory[j++] = root_directory[i++];
                    }
                    i=1;
                    while(token[i]!='\0')
                    {
                        new_directory[j++] = token[i++];
                    }
                }
                else if(strcmp(token , "-") == 0)
                {
                    strcpy(new_directory , previous_directory);
                }
                else{
                    strcpy(new_directory , token);
                }
                int check_for_change_of_directory = chdir(new_directory);
                if(check_for_change_of_directory != 0)
                {
                    printf("Unable to change the directory\n");
                    return NULL ;
                }
                struct dirent **namelist;
                int check_to_whether_scandir_works = scandir(new_directory, &namelist, NULL, alphasort);
                if(check_to_whether_scandir_works<0)
                {
                    printf("Unable to implement scandir\n");
                    return remaining_token;
                }
                if(a==0 && l==0)
                {
                    for(int i=0 ; i< check_to_whether_scandir_works; i++)
                    {
                        if(namelist[i]->d_name[0]!='.')
                            printf("%s\n", namelist[i]->d_name);
                    }
                }
                else if(a==1 && l==0)
                {
                    for(int i=0 ; i< check_to_whether_scandir_works; i++)
                    {
                        printf("%s\n", namelist[i]->d_name);
                    }
                }
                else if(a==0 && l==1)
                {
                    DIR*directory = opendir(new_directory);
                    if(directory==NULL)
                    {
                        printf("No such directory exists.\n");
                        return remaining_token;
                    }
                struct dirent **namelist;
                    int n = scandir(new_directory, &namelist, NULL, alphasort);
                    for(int i=0 ; i<n ; i++)
                    {
                        if (namelist[i]->d_name[0] != '.') {
                            char path[8195];
                            snprintf(path, sizeof(path), "%s/%s", new_directory, namelist[i]->d_name);
                            struct stat file_stat;
                            if(stat(path , &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
                            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
                            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
                            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

                            struct passwd *user_info = getpwuid(file_stat.st_uid);
                            struct group *group_info = getgrgid(file_stat.st_gid);
                            printf(" %2lu %8s %8s %8ld ", (unsigned long)file_stat.st_nlink , user_info ? user_info->pw_name : "" , group_info ? group_info->gr_name : "" , (long)file_stat.st_size);

                            char time_str[30];
                            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                            printf("%s \t", time_str);
                            printf("%s" , namelist[i]->d_name);
                            printf("\n");
                        }
                    }
                }
                
                else{
                    DIR*directory = opendir(new_directory);
                    if(directory==NULL)
                    {
                        printf("No such directory exists.\n");
                        return remaining_token;
                    }
                struct dirent **namelist;
                int n = scandir(new_directory, &namelist, NULL, alphasort);
                    for(int i=0 ; i<n ; i++) {
                            char path[8195];
                            snprintf(path, sizeof(path), "%s/%s", new_directory, namelist[i]->d_name);
                            struct stat file_stat;
                            if(stat(path , &file_stat) == -1)
                            {
                                perror("opendir");
                                break;
                            }
                            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
                            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
                            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
                            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
                            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
                            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

                            struct passwd *user_info = getpwuid(file_stat.st_uid);
                            struct group *group_info = getgrgid(file_stat.st_gid);
                            printf(" %2lu %8s %8s %8ld ", (unsigned long)file_stat.st_nlink , user_info ? user_info->pw_name : "" , group_info ? group_info->gr_name : "" , (long)file_stat.st_size);

                            char time_str[30];
                            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                            printf("%s \t", time_str);
                            printf("%s" , namelist[i]->d_name);
                            printf("\n");
                        
                    }
                }
                check_for_change_of_directory = chdir(check_present_directory);
                if(check_for_change_of_directory != 0)
                {
                    printf("Unable to change the directory\n");
                    return remaining_token;
                }
            
        }
        previous_token = remaining_token;
    }
}