#include <stdio.h>

int main()
{
    int a[] = {12, 22, 32, 42, 52};
    int c = 101;
    int d = 102;
    printf("%d\n", c);
    printf("%d\n", *(&d + 1));
    int b[] = {a}; // 这样赋值发生了奇怪的行为
    printf("b的长度:%d\n", sizeof(b) / sizeof(int));
    // b[1] = 100;
    printf("a的值=%d,   b[0]=%d,    b[1]=%d,    a[0]=%d\n", a, b[0], b[1], a[0]); 
    printf("b的地址%p,a的地址%p\n", &b[0], &a[0]);
    printf("b+1的地址%p,a的地址%p", b + 1, &a[0]);
    return 0;
}