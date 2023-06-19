#include<stdio.h>
int main(){
    if(0){
        printf("hello world!");
    }

    printf("%d\n",sizeof(long)); // 4 字节
    printf("%d\n",sizeof(int)); // 4  字节
    printf("%d\n",sizeof(long long));// 8 字节
    printf("%d\n",sizeof(short)); // 2字节
    return 0;
}