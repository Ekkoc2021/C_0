#include<stdio.h>

int main(){
    int i=10;
    printf("i�ĵ�ַ:%p",&i);

    int num = 10;
    int ptr = &num; // &num ����һ�� int* ���͵�ָ��
    int *p=ptr;
    printf("\nptr:%d \n *p=%d",ptr,*p);
    return 0;
}