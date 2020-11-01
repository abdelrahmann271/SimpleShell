/*
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>


#define BUFLEN 10

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;
    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    command[index] = NULL;
    return command;
}

int main()
{

//First Example

*/
/*    printf("Hello \n");
    fork();
    printf("bye\n");*//*


//Second Example

*/
/*    int i;
    char  buffer[BUFLEN+1];
    pid_t fork_return;

    fork_return  = fork( );
*//*
*/
/*    printf("%d",fork_return);*//*
*/
/*
    if (fork_return == 0)
    {
        strncpy(buffer, "CHILD\n", BUFLEN); *//*
*/
/*in the child process*//*
*/
/*
        buffer[BUFLEN] = '\0';
    }
    else if(fork_return > 0)
    {
        strncpy(buffer, "PARENT\n", BUFLEN); *//*
*/
/*in the parent process*//*
*/
/*
        buffer[BUFLEN] = '\0';
    }
    else if(fork_return == -1)
    {
        printf("ERROR:\n");
        switch (errno)
        {
            case EAGAIN:
                printf("Cannot fork process: System Process Limit Reached\n");
            case ENOMEM:
                printf("Cannot fork process: Out of memory\n");
        }
        return 1;
    }

    for (i=0; i<5; ++i) *//*
*/
/*both processes do this*//*
*/
/*
    {
        sleep(1); *//*
*/
/*5 times each*//*
*/
/*
        write(1, buffer, strlen(buffer));
    }*//*


    int status;
    pid_t fork_return;

    fork_return = fork();

    if (fork_return == 0) */
/* child process *//*

    {
        printf("\n I'm the child! %d %d",getpid(),getppid());
        exit(0);
    }
    else if (fork_return > 0) */
/* parent process *//*

    {
        wait(&status);
        printf("\n I'm the parent! %d %d %d",getpid(),getppid(),getpgrp());
        if (WIFEXITED(status))
            printf("\n Child returned: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
*/
