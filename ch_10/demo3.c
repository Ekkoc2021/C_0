#include <stdio.h>

int main()
{
    int *ptr;
    char *ptr2;
    double *ptr3;

    printf("%zu\n", sizeof(ptr));  // ���ָ��Ĵ�С
    printf("%zu\n", sizeof(ptr2)); // ���ָ��Ĵ�С
    printf("%zu\n", sizeof(ptr3)); // ���ָ��Ĵ�С

    return 0;
}