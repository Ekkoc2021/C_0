#include <stdio.h>

struct demo3
{
    int name;
    int id;
};
typedef struct demo3 d3;

typedef struct
{
    int name;
    int id;
} d4;

typedef int arr5[5];
int main(int argc, char const *argv[])
{
    d4 d = {81, 29};
    arr5 a;
    int((*ar)[2])[3];
    printf("%d, %d", d.name, a[2]);
    return 0;
}
