#include<stdio.h>

int main(){
    // printf("\033[31mLine 1\n\033[0m");
    // printf("\b\b\b\b\b\b\b");
    // printf("Line 2");
    // return 0;
    printf("Line 1");  // 输出第一行内容
    printf("\b\b\b\b\b\b\b");  // 退回到第一行的起始位置
    printf("Line 2");          // 输出新的内容，覆盖第一行的内容


    return 0;
}