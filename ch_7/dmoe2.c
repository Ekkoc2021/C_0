#include <stdio.h>

int main() {
    int i = 1;

    start:
    printf("Iteration %d\n", i);
    i++;
    int j = 1;
    j++;
    printf("j: %d\n", j);

    if (i <= 5) {
        goto start; // ��ת����ǩ "start" ��
    }

    printf("Program continues...\n");
    return 0;
}