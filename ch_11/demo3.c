#include <stdio.h>

int main()
{
    char s[4] = "he";
    for (size_t i = 0; i < 4; i++)
    {
        printf("%d\n", s[i] == '\0');
    }

    return 0;
}