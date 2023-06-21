#include<stdio.h>
int main(){
    float oneInch=2.54;
    int height;
    printf("你的身高(英寸): _\b");
    scanf("%d",&height);
    printf("你的身高为:%f厘米",oneInch*height);
    return 0;
}