
#include <stdio.h>
#include <string.h>
int main()
{
    const int constVar = 42;
    int regularVar = 100;

    printf("Address of constVar: %p\n", (void *)&constVar);
    printf("Address of regularVar: %p\n", (void *)&regularVar);
    printf("Address of regularVar: %d\n", &constVar);
    printf("Address of regularVar: %d\n", &regularVar);
    printf("Address of regularVar: %d\n", (int)(&constVar) - (int)(&regularVar));

    struct Point
    {
        int x : 1;
        int y;
    } p;
    p.x = 1;
    printf("%d", p.x);
    return 0;
}