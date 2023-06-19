#include <stdio.h>
// int printf (const char *__format, ...);
// 注释掉#include<stdio.h> 自己声明printf函数,也能编译运行
int main(void){
    int num;
    num=1;
    printf("I am a simple ");
    printf("computer.\n");
    printf("My favorite number is %d because it is first.\n",num);
    printf("compute.\br\n");
    printf("hello\tworld!");
    return 0;
}