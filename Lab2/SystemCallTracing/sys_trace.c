uint64
sys_trace(void)
{
    int mask;
    // ȡ a0 �Ĵ����е�ֵ���ظ� mask
    if (argint(0, &mask) < 0)
        return -1;
    // �� mask �������н��̵� mask
    myproc()->mask = mask;
    return 0;
}
