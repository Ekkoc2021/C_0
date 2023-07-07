#include<stdio.h>

int main(){
    char c1;
    char c2;

    // c1=getchar();
    // printf("getchar第一个读取:%c\n",c1);
    scanf("%c",&c2);
    printf("scanf读取:%c\n",c2);
    c1=getchar();
    printf("getchar第二个读取:%c\n",c1);
    return 0;
}