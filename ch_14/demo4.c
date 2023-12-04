#include <stdio.h>

enum spectrum
{
    read,
    orange,
    yellow,
    green
}; // 定义枚举
int main(int argc, char const *argv[])
{
    enum spectrum color; // 声明枚举变量
    color = green;
    if (color == orange)
        printf("orange");

    if (color == green)
        printf("green");
    return 0;
}
