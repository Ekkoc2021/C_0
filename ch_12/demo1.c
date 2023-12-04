int main()
{
    register int quick = 10; // 将 quick 变量建议存储在寄存器中

    // 下面的语句尝试获取 quick 变量的地址，会导致编译错误或警告
    // int *ptr = &quick;

    return 0;
}