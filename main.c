#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<signal.h>


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

void interrupt_handler(int sig, pid_t child_pid)
{
    int status;
    //pid_t pid;
    //pid = wait(NULL);
/*   if(waitpid(child_pid, &status, WNOHANG) != 0) {
        // child process has finished
        printf("child process %d has finished",child_pid);
    }*/
    //printf("Pid %d exited.\n", pid);
}

int main() {
        pid_t child_pid;
        int stat_loc;
        int status;
        //Shell Loop.
        while (1) {
            //Read Input.
            read:

            if(child_pid != 0 && waitpid(child_pid, &status, WNOHANG) != 0) {
                // child process has finished
                printf("child process %d has finished\n",child_pid);
            }
            readCommand();
            int status;
            char **command = malloc(8 * sizeof(char *));
            int index = 0;
            if(strcmp(token,"exit")==0){
                exit(0);
            }
            else {
                while(token!= NULL){
                    //Case of Background Process
                    if(strcmp(token,"&")==0){
                        int status;
                        //signal(SIGCHLD, interrupt_handler);
                        //interrupt_handler(status,child_pid);
                        child_pid = fork();
/*                        if(waitpid(child_pid, &status, WNOHANG) != 0) {
                            // child process has finished
                            printf("child process has finished");
                        }*/
                        if (child_pid == 0) {
                            //Never returns if the call is successful
                            printf("Background Process %d \n",getpid());
                            if(execvp(command[0], command) == -1){
                                printf("Error");
                            }
                            else{
                                printf("a7aaaa");
                            }
                            printf("This won't be printed if execvp is successul\n");
                        }
                        else{
                            //interrupt_handler(status,child_pid);
                            sleep(0.5);
                            goto read;
                        }
                    }
                    command[index] = token;
                    index++;
                    token = strtok(NULL, WHITESPACE);
                }
                //Other Commands
                pid_t child_pid2;
                child_pid2 = fork();
                if (child_pid2 == 0) {
                    //Never returns if the call is successful
                    execvp(command[0], command);
                    printf("This won't be printed if execvp is successul\n");
                } else {
                    waitpid(child_pid2, &stat_loc, WUNTRACED); //problem
                }
            }

        }
        return 0;
    }

