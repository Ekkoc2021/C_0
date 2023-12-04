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

    int((*ar1)[2])[3] = &arr1; // ar1指向一个包含2个元素的数组，每个元素是一个包含3个整数元素的数组
    int(*ar2)[2][3] = &arr2;   // ar2指向一个包含2个元素的数组，每个元素是一个包含3个整数元素的数组

    // 访问元素方式不同
    printf("%d\n", (*ar1)[0][1]); // 输出：2
    printf("%d\n", (*ar2)[1][2]); // 输出：12

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