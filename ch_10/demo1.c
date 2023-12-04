#include <stdio.h>

int main()
{
    int a=8;
    int arr[6] = {[5] = 222, [2] = 3};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        printf("µÚ%d¸öÔªËØ=%d\n", i, arr[i]);
    }

    return 0;
}