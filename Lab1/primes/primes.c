#include "kernel/types.h"
#include "user/user.h"
const int MAX = 35;//��35�Ĵ�һ�㣬��qemu�����л�ը�������Լ������������û����
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
        //�ӽ��̹ر�д��
        close(pipefd[WRITE]);
        primes(pipefd[READ]);
        //�ӽ��̹ر�д��
        close(pipefd[READ]);
    }
    else
    {
        int temp;
        //�����̹رն���
        close(pipefd[READ]);
        while (read(prev_read, &temp, sizeof(int)))
            if (temp % prime != 0)//���ǵ�ǰ�����ı�������д��ܵ���
                write(pipefd[WRITE], &temp, sizeof(int));
        //�����̹ر�д��
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
        //�ӽ��̹ر�д��
        close(pipefd[WRITE]);
        primes(pipefd[READ]);
        //�ӽ��̹رն���
        close(pipefd[READ]);
    }
    else
    {
        //�����̹رն���
        close(pipefd[READ]);
        for (int i = 2; i <= MAX; i++)
            write(pipefd[WRITE], &i, sizeof(int));
        //�����̹ر�д��
        close(pipefd[WRITE]);
        wait(0);
    }
    exit(0);
}