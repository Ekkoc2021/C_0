#include <stdio.h>

int main()
{
    // int *p1;
    // const int *p2;
    // const int **pp2;
    // p1 = p2;
    // p2 = p1;
    // pp2 = &p1;
    const int **pp2;
    int *p1;
    const int n = 13;
    pp2 = &p1;
    printf("n=%d", n);

    int *const *pp3;
    pp3 = &p1;
    // *pp3=10;
    *pp2=10; 

    return 0;
}