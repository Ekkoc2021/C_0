#include <stdio.h>

enum spectrum
{
    read,
    orange,
    yellow,
    green
}; // ����ö��
int main(int argc, char const *argv[])
{
    enum spectrum color; // ����ö�ٱ���
    color = green;
    if (color == orange)
        printf("orange");

    if (color == green)
        printf("green");
    return 0;
}
