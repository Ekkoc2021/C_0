#include <stdio.h>

int main()
{
    extern int globalStaticVar;
    printf("Global static variable: %d\n", globalStaticVar);
    return 0;
}
int globalStaticVar = 111;