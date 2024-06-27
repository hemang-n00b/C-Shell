#include "headers.h"

void print_directory(int d, int f, char *str, char *file_folder_to_be_found, int *count, char *stored_part , char*og_directory)
{

    
    // printf("%s\n" , str);
    DIR *directory = opendir(str);
    if (directory == NULL)
    {
        printf("No such directory exists.");
        return;
    }
    struct dirent **namelist;
    int n = scandir(str, &namelist, NULL, alphasort);
    for (int i = 0; i < n; i++)
    {
        char concatenated_string[4097] , new_og[4097];
        snprintf(concatenated_string, sizeof(concatenated_string), "%s/%s", str, namelist[i]->d_name);
        if (namelist[i]->d_name[0] != '.')
        {
            struct stat file_stat;
            if (stat(concatenated_string, &file_stat) == -1)
            {
                continue;
            }
            char present_dir[8195];
            snprintf(present_dir, sizeof(present_dir), "%s/%s", str, namelist[i]->d_name);
            snprintf(new_og , 8195 , "%s/%s" ,og_directory , namelist[i]->d_name );
            if (strncmp(file_folder_to_be_found, namelist[i]->d_name, strlen(file_folder_to_be_found)) == 0)
            {
                if (d == 1 && S_ISDIR(file_stat.st_mode) && namelist[i]->d_name[0] != '.')
                {
                    (*count)++;
                    printf("\033[34m%s\n\033[0m", present_dir);
                    strcpy(stored_part, present_dir);
                }
                else if (f == 1 && S_ISREG(file_stat.st_mode) && namelist[i]->d_name[strlen(file_folder_to_be_found)]=='.')
                {
                    (*count)++;
                    printf("\033[32m%s\n\033[0m", present_dir);
                    strcpy(stored_part, present_dir);
                }
                else if(d==0 && f==0 && (namelist[i]->d_name[strlen(file_folder_to_be_found)]=='.' || namelist[i]->d_name[strlen(file_folder_to_be_found)]=='\0'))
                {
                    (*count)++;
                    if(S_ISDIR(file_stat.st_mode))
                        printf("\033[34m%s\n\033[0m", present_dir);
                    else if(S_ISREG(file_stat.st_mode))
                        printf("\033[32m%s\n\033[0m", present_dir);
                    strcpy(stored_part, present_dir);
                }
            }
            if (S_ISDIR(file_stat.st_mode) && namelist[i]->d_name[0] != '.')
            {
                print_directory(d, f, present_dir, file_folder_to_be_found, count, stored_part , new_og);
            }
        }
    }
}

char *seek(char *root_directory, char *remaining_token, int *changes, char *previous_directory)
{

int outdirect =0;
    char *execute = (char*)calloc(4097 , sizeof(char));
    if(strchr(remaining_token , '<') || strchr(remaining_token, '>'))
    {
        char cmd[4097] , res[4097];
        strcpy(cmd, remaining_token);
        strcpy(res,remaining_token);
        char outputfile[4097], inputfile[4097], buf[4097], filename[4097];
        int prevfile = 0, append = 0, i, indirect = 0;
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
        // execute[i] = '\0';
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
        // printf("%s\n\n" ,execute );
        if(indirect ==1)
        {
            FILE* input_pointer = fopen(inputfile , "r");
            if (input_pointer == NULL) {
                perror("Failed to open the file");
                return NULL;
            }
            char buffer[1024]; 
            while (fgets(buffer, sizeof(buffer), input_pointer) != NULL) {
                strcat(execute ,buffer);
            }
            fclose(input_pointer);
        }
        // printf("%s\n\n" , remaining_token);
        // printf("%s\n\n" ,execute );
    // int insta=0;
    // while(execute[insta]!='\0')
    // {
    //     remaining_token[insta] = execute[insta];
    //     insta++;
    // }
    // remaining_token[insta] = '\0';
    remaining_token = strdup(execute);
    // printf("%s" , remaining_token);
    }

    int count = 0;
    char *previous_remaining_token = remaining_token;
    int d = 0, f = 0, e = 0;
    char hemang[4097];
    char*get_return_directory = getcwd(hemang , sizeof(4097));
    while (1)
    {
        char *token = strtok_r(remaining_token, " \n\t", &remaining_token);
        if (token == NULL)
        {
            return remaining_token;
        }
        if (strcmp(token, "-d") == 0)
        {
            d = 1;
        }
        else if (strcmp(token, "-f") == 0)
        {
            f = 1;
        }
        else if (strcmp(token, "-e") == 0)
        {
            e = 1;
        }
        else
        {
            if (d == 1 && f == 1)
            {
                printf("Invalid flags!\n");
                return remaining_token;
            }
            char stored_part[4097];
            char pres_dir[4097];
            char *present_directory = getcwd(pres_dir, 4097);
            // printf("%s\n" , present_directory);
            char *changing_directory = strtok_r(remaining_token, " \n\t", &remaining_token);
            if (changing_directory == NULL)
            {
                changing_directory = present_directory;
            }
            if (changing_directory[0] == '~')
            {
                char *new_directory_home = (char *)calloc(4097, sizeof(char));
                int i = 0, j = 0;
                while (root_directory[i] != '\0')
                {
                    new_directory_home[j++] = root_directory[i++];
                }
                i = 1;
                while (changing_directory[i] != '\0')
                {
                    new_directory_home[j++] = changing_directory[i++];
                }
                // printf("%s\n", new_directory_home);
                changing_directory = new_directory_home;
            }
            int check_for_change_in_directory = chdir(changing_directory);
            char*og_directory = strdup(changing_directory);
            char *final_directory = ".";
            strcat(og_directory ,"/");
            strcat(og_directory , final_directory);
            // printf("%s\n" , og_directory);
            print_directory(d, f, final_directory, token, &count, stored_part , og_directory);
            if (count == 0)
            {
                printf("No match found!\n");
                // check_for_change_in_directory = chdir(present_directory);
                return remaining_token;
            }
            int t = 0;
            if (e == 1)
            {
                if (count == 1)
                {
                    DIR *directory = opendir(stored_part);
                    struct stat file_stat;
                    if (stat(stored_part, &file_stat) == -1)
                    {
                        perror("stat");
                        continue;
                    }               
                    if (directory != NULL)
                    {
                        t=1;
                        int check_for_change_in_directory = chdir(stored_part);
                    }
                    else if ( S_ISREG(file_stat.st_mode))
                    {
                        FILE *file = fopen(stored_part, "r");
                        if (file == NULL)
                        {
                            perror("fopen");
                            return remaining_token;
                        }

                        char buffer[1024];
                        size_t bytes_read;

                        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0)
                        {
                            fwrite(buffer, 1, bytes_read, stdout);
                        }
                    }
                }
                else if (count == 0)
                {
                    
                    printf("No match found!\n");
                }
            }
            if (t == 0)
                check_for_change_in_directory = chdir(present_directory);
        }
        // previous_remaining_token = remaining_token;
    }
}