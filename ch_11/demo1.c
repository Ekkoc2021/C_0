#include <stdio.h>

int main()
{
    char *s = "hello wrold!";
    char *s2 = "hello wrold!";
    char s3[] = "hello wrold!";
    printf("%p==%p==%p\n", s, s2, s3);
    int n = 10;
    int *i = (int[]){n, 2, 3};
    int *i2 = (int[]){1, 2, 3};
    int i3[] = {1, 2, 3};
    printf("%p==%p==%p", i, i2, i3);
    int i4[3] = {1, 2, 3, 5, 6};
    for (size_t i = 0; i < 3; i++)
    {
        printf("%d", i4[i]);
    }

    return 0;
}