#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
int main(int argc, const char* args[])
{
    int child;
    int pipefd[2];
    int pipefd1[2];
    if (-1 == pipe(pipefd) || -1 == pipe(pipefd1))
        exit(1);
    char ch;
    if (0 == (child = fork()))
    {
        close(pipefd[1]);//关闭管道0的写
        close(pipefd1[0]);//关闭管道1的读
        read(pipefd[0], &ch, 1);
        printf("%d: received ping\n", getpid());
        write(pipefd1[1], "1", 1);
        close(pipefd[0]);
        close(pipefd1[1]);
        exit(0);
    }
    else
    {
        close(pipefd[0]);//关闭管道0的读
        close(pipefd1[1]);//关闭管道1的写
        write(pipefd[1], "1", 1);
        read(pipefd1[0], &ch, 1);
        printf("%d: received pong\n", getpid());
        close(pipefd1[0]);
        close(pipefd[1]);
        wait(0);
    }
    exit(0);
}