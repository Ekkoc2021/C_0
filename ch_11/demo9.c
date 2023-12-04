#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    const char *inputStr = "10";

    char *endptr;
    long int num = strtol(inputStr, &endptr, 2);

    // ���ת���Ƿ�ɹ�
    if (*endptr != '\0')
    {
        printf("Error: Invalid characters found in the input.\n");
        return 1;
    }

    printf("Converted number: %ld\n", num);
    return 0;
}