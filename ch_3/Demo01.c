#include<stdio.h>
#include<stdbool.h>
int main(){
    if(0){
        printf("hello world!");
    }

    printf("%d\n",sizeof(32)); //int ���� 4
    printf("%d\n",sizeof(long)); // 4 
    printf("%d\n",sizeof(int)); // 4  
    printf("%d\n",sizeof(long long));// 8 
    printf("%d\n",sizeof(short)); // 2

    printf("%d\n",sizeof(char)); // 1

    printf("%d\n",sizeof(32.01)); // double ���� 8�ֽ�
    printf("%d\n",sizeof(float)); // 4�ֽ�
    printf("%d\n",sizeof(double)); // 8�ֽ�
    printf("%d\n",sizeof(long double)); //16�ֽ�(64λ�������16)

    printf("%d\n",sizeof(_Bool)); // 1�ֽ�
    bool b=-111;
    if(b==true){
        int a=9.009;
        printf("hello %d \n",a);
    }
     printf("%d\n",sizeof(bool)); // 1�ֽ�
    return 0;
}