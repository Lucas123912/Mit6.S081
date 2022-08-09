#include "kernel/types.h"
#include "user/user.h"
const int MAX = 35;//把35改大一点，在qemu下运行会炸掉。在自己虚拟机上运行没问题
const int READ = 0;
const int WRITE = 1;

void primes(int prev_read)
{
    int prime;
    if (read(prev_read, &prime, sizeof(int)) <= 0)
        exit(0);
    printf("prime %d\n", prime);
    int pipefd[2];
    pipe(pipefd);
    if (0 == fork())
    {
        //子进程关闭写端
        close(pipefd[WRITE]);
        primes(pipefd[READ]);
        //子进程关闭写端
        close(pipefd[READ]);
    }
    else
    {
        int temp;
        //父进程关闭读端
        close(pipefd[READ]);
        while (read(prev_read, &temp, sizeof(int)))
            if (temp % prime != 0)//不是当前素数的倍数的数写入管道中
                write(pipefd[WRITE], &temp, sizeof(int));
        //父进程关闭写端
        close(pipefd[WRITE]);
        wait(0);
    }
    exit(0);
}
int main(int argc, const char* argv[])
{
    int pipefd[2];
    pipe(pipefd);
    if (0 == fork())
    {
        //子进程关闭写端
        close(pipefd[WRITE]);
        primes(pipefd[READ]);
        //子进程关闭读端
        close(pipefd[READ]);
    }
    else
    {
        //父进程关闭读端
        close(pipefd[READ]);
        for (int i = 2; i <= MAX; i++)
            write(pipefd[WRITE], &i, sizeof(int));
        //父进程关闭写端
        close(pipefd[WRITE]);
        wait(0);
    }
    exit(0);
}