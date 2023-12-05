#include <stdio.h>

void testAutoStaticVar()
{
    static int count = 10;
    for (int i = 0; i < 10; i++)
    {
        count++;
    }

    printf("count address:%d  count:%d \n", &count, count);
}

int main(int argc, char const *argv[])
{

    testAutoStaticVar();
    testAutoStaticVar();
    return 0;
}
