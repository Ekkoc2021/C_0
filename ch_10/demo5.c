#include <stdio.h>

int main()
{
    int a[] = {12, 22, 32, 42, 52};
    int c = 101;
    int d = 102;
    printf("%d\n", c);
    printf("%d\n", *(&d + 1));
    int b[] = {a}; // ������ֵ��������ֵ���Ϊ
    printf("b�ĳ���:%d\n", sizeof(b) / sizeof(int));
    // b[1] = 100;
    printf("a��ֵ=%d,   b[0]=%d,    b[1]=%d,    a[0]=%d\n", a, b[0], b[1], a[0]); 
    printf("b�ĵ�ַ%p,a�ĵ�ַ%p\n", &b[0], &a[0]);
    printf("b+1�ĵ�ַ%p,a�ĵ�ַ%p", b + 1, &a[0]);
    return 0;
}