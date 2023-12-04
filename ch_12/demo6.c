#include <stdio.h>
const int a = 10;
void f2(int *a1)
{
    printf("³¤¶È:%d\n", sizeof(a1) / sizeof(int));
    for (size_t i = 0; i < 2; i++)
    {
        printf("shuzhi:%d\n", a1[i]);
    }
}
int main()
{
    int c = 100;
    int *const volatile c2 = &c;
    *c2 = 99;
    int d = 98;
    extern int const a;

    printf("%d\n", a + 2);
    int *restrict a11 = &d;
    *a11 += 100;
    d += 200;
    *a11 += 10;
    printf("%d\n", d);
    int a1123[] = {1,
                   2,
                   3,
                   5};
    int *p111 = (int[]){1,
                        2,
                        3,
                        5};
    printf("shuzhi:%d\n", p111[2]);
    f2(p111);
    return 0;
}
