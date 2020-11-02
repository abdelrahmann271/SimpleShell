/*
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void handler(int sig)
{
    pid_t pid;

    pid = wait(NULL);

    printf("Pid %d exited.\n", pid);
}

int main(void)
{
    signal(SIGCHLD, handler);

    if(!fork())
    {
        printf("Child pid is %d\n", getpid());
        exit(0);
    }
    printf("Parent pid is %d\n", getpid());

    getchar();
    return 0;
}
*/
