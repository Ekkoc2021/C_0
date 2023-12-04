#include <stdio.h>

int main()
{
    int *ptr;
    int i = 10;
    ptr = &i;
    int(*(*ptr2)[2])[3];
    int i2[2][3] = {{1, 2, 3}, {11, 22, 33}};
    ptr2 = i2;
    printf("ÄãºÃ:%d\n", *ptr);
    printf("ÄãºÃ2:%d\n", ptr2[0][0]);

    // int *p2;
    // double i = 122;
    // p2 = &i;
    // printf("p2=%d", *p2);

    int *p11 = &i;
    const int **p22 = &p11;
    *p22 = 10;
    printf("i=%d", i);
    return 0;
}