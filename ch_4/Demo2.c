#include <stdio.h>

int main() {
    int num;
    char name[50];

    printf("Enter an integer: ");
    scanf("%d", &num);

    printf("Enter a name: ");
    scanf("%s", name);

    printf("Integer: %d\n", num);
    printf("Name: %s\n", name);

    return 0;
}