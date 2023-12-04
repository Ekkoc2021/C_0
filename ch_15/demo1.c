#include <stdio.h>
struct bf2
{
    unsigned short a : 15; // 15位 short为16位
    unsigned short b : 15; // b会主动到下一short类型上,a与b留下一个空白位
    unsigned short : 1;    // 未命名的字段宽度主动填充空白位
    unsigned short c : 12; // b与c留下一个空白位
    unsigned short : 0;    // 强制下一个字段对齐到新的16位上
    unsigned short d : 2;  // 够放,但是也被强制对齐
} t;

int main(int argc, char const *argv[])
{
    printf("%d", sizeof(t));
    return 0;
}
