#include <stdio.h>
#include <stddef.h>
#include <string.h>
int main()
{
    size_t size = sizeof(size_t);

    printf("size_t size: %d bytes\n", size);

    char *b = {"hello", "world"};
    printf("%d\n", sizeof(*b) / sizeof(char));

    int a[] = {{1, 2, 3, 4},
               {4, 5, 6}};
    printf("%d\n", sizeof(a) / sizeof(int));

    char dest[20] = "Hello, ";
    const char src[] = "World!";

    strcat(dest, src);

    printf("Concatenated string: %s\n", dest);

    int *ptr;
    if (ptr == NULL)
    {
        printf("Ö¸Õë³õÊ¼ÎªnULL");
    }
    return 0;
}