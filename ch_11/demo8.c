#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Total number of command-line arguments: %d\n", argc);

    // ���ÿ�������в���
    for (int i = 0; i < argc; i++)
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    

    return 0;
}