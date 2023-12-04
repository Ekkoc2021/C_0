#include <stdio.h>
int sum1(int n[], int count);
int main()
{
    int n[] = {1, 2, 3, 4, 5, 6};
    printf("ºÍµÈÓÚ:%d\n", sum1(n, 6));
    printf("n[1]=%d", n[1]);
    return 0;
}
int sum1(int n[], int count)
{
    int s = 0;
    for (int i = 0; i < count; i++)
    {
        s = s + n[i];
    }
    n[1] = 998;
    return s;
}