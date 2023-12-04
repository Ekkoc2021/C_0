#include <stdio.h>

int main()
{
    int *ptr;
    char *ptr2;
    double *ptr3;

    printf("%zu\n", sizeof(ptr));  // 输出指针的大小
    printf("%zu\n", sizeof(ptr2)); // 输出指针的大小
    printf("%zu\n", sizeof(ptr3)); // 输出指针的大小

    return 0;
}