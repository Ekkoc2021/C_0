#include <stdio.h>
typedef int (*f)();
struct demo5
{
    f b;
} d1;
int b()
{
    printf("jel");
    return 0;
}
int main()
{
    int arr1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int arr2[2][3] = {{7, 8, 9}, {10, 11, 12}};

    int((*ar1)[2])[3] = &arr1; // ar1ָ��һ������2��Ԫ�ص����飬ÿ��Ԫ����һ������3������Ԫ�ص�����
    int(*ar2)[2][3] = &arr2;   // ar2ָ��һ������2��Ԫ�ص����飬ÿ��Ԫ����һ������3������Ԫ�ص�����

    // ����Ԫ�ط�ʽ��ͬ
    printf("%d\n", (*ar1)[0][1]); // �����2
    printf("%d\n", (*ar2)[1][2]); // �����12

    int (*f[2])();

    int a()
    {
        printf("hello");

        return 1;
    }
    f[0] = &a;
    (*f[0])();
    d1.b = &b;
    (*(d1.b))();
    return 0;
}