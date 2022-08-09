// kernel/proc.c
// Return the number of processes whose state is not UNUSED
uint64
nproc(void)
{
    struct proc* p;
    // counting the number of processes
    uint64 num = 0;
    // traverse all processes
    for (p = proc; p < &proc[NPROC]; p++)
    {
        // add lock
        acquire(&p->lock);
        // if the processes's state is not UNUSED
        if (p->state != UNUSED)
        {
            // the num add one
            num++;
        }
        // release lock
        release(&p->lock);
    }
    return num;
}