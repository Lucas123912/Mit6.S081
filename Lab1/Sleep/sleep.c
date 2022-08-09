#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main(int argc, const char* argv[])
{
    if (2 != argc)
    {
        fprintf(2, "Usage:sleep [time]\n");
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}