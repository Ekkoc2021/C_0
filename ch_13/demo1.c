#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *file = fopen("reversefile.text", "r");
    printf("%d\n", ftell(file));
    printf("%c\n", getc(file));
    printf("%d\n", ftell(file));
    printf("%c\n", getc(file));
    printf("%d\n", ftell(file));
    printf("%c", getc(file));
    return 0;
}