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
pid_t bgProcesses[100000];
int noOfbgPRocesses = 0;
int status;
FILE *filePointer ;


void readCommand(){
    printf("MyShell>> ");
    fgets(input, BUFFERSIZE, stdin);
    while(input[0] == '\n'){
        printf("MyShell>> ");
        fgets(input, BUFFERSIZE, stdin);
    }
    // replace new line with \0 (Null Character)
    char *res_search_input = strchr(input, '\n');
    if(res_search_input != NULL){
        *res_search_input = '\0';
    }
    if(input[0] == NULL){
        printf("%s\n", "Error reading input!");
    }
    token = strtok(input, WHITESPACE);
}

void logger(pid_t pid){
    char dataToBeWritten[50]  = "Process Done: " ;
    char str[100];
    sprintf(str, "%d", pid);
    strcat(dataToBeWritten,str);
    if ( filePointer == NULL )
    {
        printf( "file failed to open." ) ;
    }
    else
    {
        if ( strlen (  dataToBeWritten  ) > 0 )
        {
            fputs(dataToBeWritten, filePointer) ;
            fputs("\n", filePointer) ;
        }
    }
}
void handler(int sig)
{
    for(int i = 0 ; i < 10 ; i++){
        if(bgProcesses[i] != 0 && waitpid(bgProcesses[i], &status, WNOHANG) == bgProcesses[i]) {
            //printf("child process %d has finished\n",bgProcesses[i]);
            logger(bgProcesses[i]);
            bgProcesses[i] =0;
            noOfbgPRocesses--;
        }
    }
}
int main() {
    pid_t child_pid;
    int stat_loc;
    filePointer = fopen("ShellLogs.txt", "w") ;
    //Shell Loop.
    while (1) {
        //Read Input.
        read:
        signal(SIGCHLD,handler);
       // printf("no of back %d\n",noOfbgPRocesses);
        readCommand();
        int status;
        char **command = malloc(8 * sizeof(char *));
        if(command == NULL){
            printf("Cannot Allocate Memory");
        }
        int index = 0;
        if(strcmp(token,"exit")==0){
            //Kill All Childs Processes.
            for(int i=0; i<noOfbgPRocesses; i++){
                logger(bgProcesses[i]);
                if(kill(bgProcesses[i], SIGTERM) == -1 && errno != ESRCH){
                    exit(EXIT_FAILURE);
                }
            }
            fclose(filePointer);
            exit(0);
        }
        else {
            while(token!= NULL){
                //Case of Background Process
                if(strcmp(token,"&")==0){
                    int status;
                    child_pid = fork();
                    if (child_pid == 0) {
                        //Never returns if the call is successful
                        //printf("Background Process %d \n",getpid());
                        if(execvp(command[0], command)==-1){
                            printf("Error\n");
                        }
                       // printf("Wrong or Unsupported Command\n");
                    }
                    else{
                        bgProcesses[noOfbgPRocesses]=child_pid;
                       // printf("process begin %d\n",bgProcesses[noOfbgPRocesses]);
                        noOfbgPRocesses++;
                       // printf("no of current processes %d\n",noOfbgPRocesses);
                        //sleep(0.75);
                        int status1;
/*                        if(WIFEXITED(status1))
                            printf("child exited with = %d\n",WEXITSTATUS(status));*/

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
                printf("Wrong or Unsupported Command\n");
            } else {
                waitpid(child_pid2, &stat_loc, WUNTRACED);
                logger(child_pid2);
                free(command);
            }
        }
    }
    return 0;
}

