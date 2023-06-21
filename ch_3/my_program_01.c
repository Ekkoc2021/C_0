#include<stdio.h>
int main(){
    // 上溢 下溢 处理
    int max=2147483647;
    int min=-2147483648;
    printf("a=%d,a+1=%d\n",max,max+1);

    float Value = 1000000;
    for (size_t i = 0; i < 10; i++){
        Value=Value*Value;
        printf("Value= %f \n", Value);
    }
    float Value2 = 0.000010;
    for (size_t i = 0; i < 10; i++){
        Value2=Value2/2;
        printf("Value= %f \n", Value2);
    }
    

    return 0;
}