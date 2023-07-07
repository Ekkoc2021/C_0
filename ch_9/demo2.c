#include<stdio.h>

int main(){
    int i=10;
    printf("i的地址:%p",&i);

    int num = 10;
    int ptr = &num; // &num 返回一个 int* 类型的指针
    int *p=ptr;
    printf("\nptr:%d \n *p=%d",ptr,*p);
    return 0;
}