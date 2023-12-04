#include <stdio.h>

int main()
{
    const int a[] = {1, 2, 3};
    int b[] = {a};
    printf("%d", b[0]);
    return 0;
}