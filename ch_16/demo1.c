#include <stdio.h>
#define H "hello"
#define PR(...) printf(__VA_ARGS__)
int main(int argc, char const *argv[])
{
    char *s = "H world";
    const int a = 2 * 2;
    PR("%d %s", a, s);
    return 0;
}
