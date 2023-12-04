#include <stdio.h>
int main()
{
    int b[2] = {1, 3};
    int a[2][3] = {
        b,
        {3, 5}};
    a[0][0] = 99;
    printf("%d\n", b[0]);
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            printf("[%d][%d]=%d\n", i, j, a[i][j]);
        }
    }

    return 0;
}