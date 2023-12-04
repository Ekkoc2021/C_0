#include <stdio.h>

void demoFunction()
{
    // 定义具有代码块作用域的静态变量
    static int staticVar = 0;

    // 打印静态变量的值
    printf("Static Variable: %d\n", staticVar);

    // 修改静态变量的值
    staticVar++;
}

int main()
{
    // 多次调用demoFunction函数
    demoFunction(); // 输出 Static Variable: 0
    demoFunction(); // 输出 Static Variable: 1
    demoFunction(); // 输出 Static Variable: 2

    return 0;
}