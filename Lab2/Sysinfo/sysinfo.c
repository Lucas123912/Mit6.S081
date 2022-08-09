// kernel/sysproc.c
// add header
#include "sysinfo.h"
uint64
sys_sysinfo(void)
{
    // addr is a user virtual address, pointing to a struct sysinfo
    uint64 addr;
    struct sysinfo info;
    struct proc* p = myproc();
    if (argaddr(0, &addr) < 0)
        return -1;
    // get the number of bytes of free memory
    info.freemem = free_mem();
    // get the number of processes whose state is not UNUSED
    info.nproc = nproc();
    if (copyout(p->pagetable, addr, (char*)&info, sizeof(info)) < 0)
        return -1;
    return 0;
}