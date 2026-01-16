#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *arg[])
{
    // Fork a new process
    int pid;
    pid = fork();
    if (pid < 0)
    {
        printf("fork failed\n");
        exit(1);
    }
    // Parent process
    else if (pid == 0)
    {
        execlp("whoami", "1s", NULL);
        exit(0);
    }
    else
    {
        // Child process
        printf("\nProcess ID is: %d\n", getpid());
        wait(NULL);
        exit(0);
    }
}
