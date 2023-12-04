#include <stdio.h>
#define P(x) a##x

int main(int argc, char const *argv[])
{
    int P(1) = 2; // int a1;
    int P(2) = 4;
    printf("%d %d", a1, a2);
    return 0;
}
