#include <stdio.h>
#define ROWS 2
#define COLS 4
int t(int a[2][2])
{
    printf("长度:%d", sizeof(a) / sizeof(a[0]));
    return 0;
}
int n = 10;
int a2[n];
int main()
{
    int a[2][2] = {{1, 2}, {3, 4}};
    printf("长度:%d\n", sizeof(a) / sizeof(a[0]));
    t(a);
    for (int i = 0; i < n; i++)
    {
        a2[i] = i + 100;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", a2[i]);
    }

    return 0;
}