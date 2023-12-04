#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    int *p = (int *)malloc(30 * sizeof(int));
    p[1] = 100;
    printf("hello world! %d", p[1]);
    free(p);
    return 0;
}
