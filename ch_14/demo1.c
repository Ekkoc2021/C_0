#include <stdio.h>

struct
{
    char name[100];
    char author[100];
} bigdata;

int main()
{

    gets(bigdata.name);
    gets(bigdata.author);
    printf("����:%s,����:%s\n", bigdata.name, bigdata.author);
    return 0;
}
