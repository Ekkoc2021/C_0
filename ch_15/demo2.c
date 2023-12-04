#include <stdio.h>
#include <stdlib.h>
struct a
{
    unsigned short i : 2;
    unsigned short i1 : 2;
    unsigned short i2 : 2;
    unsigned short i3 : 2;
};
union t2
{
    struct a b;
    unsigned short c;
};
char *itobs(short n, char *ps)
{
    short i;
    static int size = 8 * sizeof(unsigned short);
    for (i = size - 1; i >= 0; i--, n >>= 1)
    {
        ps[i] = (01 & n) + '0';
    }
    ps[size] = '\0';
    return ps;
}

int main(int argc, char const *argv[])
{
    struct a t;
    union t2 t1;
    t1.b.i = 0b110;
    t1.b.i3 = 2;
    char *str = malloc(2);
    printf("%s", itobs(t1.c, str));

    free(str);
    return 0;
}
