#include <stdio.h>

void outerFunction()
{
    // 定义内部函数（通过函数指针实现）
    void innerFunction()
    {
        printf("This is an \"internal\" function.\n");
    }

    // 使用函数指针来调用内部函数
    // void (*functionPointer)() = innerFunction;
    innerFunction();
}

int main()
{
    outerFunction();

    return 0;
}