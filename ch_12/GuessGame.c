#include <stdio.h>
#include <math.h>
#include "myrand.h"
int main()
{
    puts("��������Ϸ!��������ֽ�����Ϸ!");
    int num = randInt();
    // printf("%d", num);
    printf("�����������һ��%dλ��!\n", (int)(floor(log10(num)) + 1));
    int yourGuess;
    while (0 == 0)
    {
        printf("�������������: ");
        if (!scanf("%d", &yourGuess))
        {
            printf("���������:%d!\n", num);
            break;
        }
        if (yourGuess == num)
        {
            printf("��ϲ�¶���!���������:%d!\n", num);
            break;
        }
        if (yourGuess < num)
        {
            puts("���С��!�ٴ��!");
            continue;
        }
        if (yourGuess > num)
        {
            puts("��´���!��С��!");
            continue;
        }
    }
}
