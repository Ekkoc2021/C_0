#include<stdio.h>

int main(){

    float salary;
    printf("你的月薪水:");
    printf("$____\b\b\b\b");
    scanf("%f",&salary);
    printf("年薪水:%f",salary*12);
    return 0;
}