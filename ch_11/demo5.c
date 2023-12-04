#include <stdio.h>

int main()
{
    char str[2];

    char *ptr;
    printf("Enter a string: ");
    ptr = gets(str);

    printf("You entered: %s\n", str);
    printf("You entered: %s\n", ptr);

    return 0;
}