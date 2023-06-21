#include<stdio.h>
int main(){
    float massOfOneMoleculeWater=3e-7;
    int count;
    printf("水的夸克数: _\b");
    scanf("%d",&count);
    printf("%d夸克的水分子共有%f个水分子!",count,(count*950)/massOfOneMoleculeWater);
    return 0;
}