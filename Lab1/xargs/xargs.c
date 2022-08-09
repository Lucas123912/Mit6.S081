#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    char buf[64];
    int ret;
    puts("-------------------");
    while ((ret = read(0, buf, sizeof(buf))) > 0)
    {
        buf[ret] = 0;
        printf("%s", buf);
    }
    puts("-------------------");
    return 0;
}