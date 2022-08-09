// kernel / kalloc.c
// Return the number of bytes of free memory
uint64
free_mem(void)
{
    struct run* r;
    // counting the number of free page
    uint64 num = 0;
    // add lock
    acquire(&kmem.lock);
    // r points to freelist
    r = kmem.freelist;
    // while r not null
    while (r)
    {
        // the num add one
        num++;
        // r points to the next
        r = r->next;
    }
    // release lock
    release(&kmem.lock);
    // page multiplicated 4096-byte page
    return num * PGSIZE;
}