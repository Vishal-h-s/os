/* Program is to create a child process
Hello I am Child Process
Hello I am Parent Process*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid > 0)
        printf("Hello I am Parent process pid=%d, child pid=%d\n", getpid(), pid);
    else
        printf("Hello I am child process pid=%d\n", getpid());
    return 0;
}