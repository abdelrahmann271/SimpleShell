#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


//Definitions
#define WHITESPACE " \t\r\n\v\f"
#define BUFFERSIZE 256

//Globals
char *token;
char input[BUFFERSIZE];

void readCommand(){
    printf("MyShell>> ");
    fgets(input, BUFFERSIZE, stdin);
    // replace new line with \0 (Null Character)
    char *res_search_input = strchr(input, '\n');
    if(res_search_input != NULL){
        *res_search_input = '\0';
    }
    if(input == NULL){
        printf("%s\n", "Error reading input!");
    }
    token = strtok(input, WHITESPACE);
}

int main() {
        pid_t child_pid;
        int stat_loc;
        //Shell Loop.
        while (1) {
            //Read Input.
            readCommand();
            char **command = malloc(8 * sizeof(char *));
            int index = 0;
            if(strcmp(token,"exit")==0){
                exit(0);
            }
            else{
                printf("Command Not Found");
            }
            while(token!= NULL){
                command[index] = token;
                index++;
                token = strtok(NULL, WHITESPACE);
            }
            //Commands
            child_pid = fork();
            if (child_pid == 0) {
            //Never returns if the call is successful

                execvp(command[0], command);
                printf("This won't be printed if execvp is successul\n");
            } else {
                waitpid(child_pid, &stat_loc, WUNTRACED);
            }
        }
        return 0;
    }

