#include<stdio.h>

int main(){
    char c;
    int input;
    printf("输入一个ASCII码值: _\b");
    scanf("%d",&input);
    c=input;
    printf("ASCII码值对应的字符:%c",c);
    return 0;
}