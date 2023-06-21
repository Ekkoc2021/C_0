#include<stdio.h>
int main(){
    float myfloat;
    printf("输入一个浮点数: _\b");
    scanf("%f",&myfloat);
    printf("The input is %f or %e",myfloat,myfloat);
    return 0;
}