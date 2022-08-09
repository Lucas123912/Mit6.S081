uint64
sys_trace(void)
{
    int mask;
    // 取 a0 寄存器中的值返回给 mask
    if (argint(0, &mask) < 0)
        return -1;
    // 把 mask 传给现有进程的 mask
    myproc()->mask = mask;
    return 0;
}
