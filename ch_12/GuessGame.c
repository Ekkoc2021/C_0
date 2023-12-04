#include <stdio.h>
#include <math.h>
#include "myrand.h"
int main()
{
    puts("猜数字游戏!输入非数字结束游戏!");
    int num = randInt();
    // printf("%d", num);
    printf("这个是数字是一个%d位数!\n", (int)(floor(log10(num)) + 1));
    int yourGuess;
    while (0 == 0)
    {
        printf("请输入你的数字: ");
        if (!scanf("%d", &yourGuess))
        {
            printf("这个数字是:%d!\n", num);
            break;
        }
        if (yourGuess == num)
        {
            printf("恭喜猜对了!这个数字是:%d!\n", num);
            break;
        }
        if (yourGuess < num)
        {
            puts("你猜小了!再大点!");
            continue;
        }
        if (yourGuess > num)
        {
            puts("你猜大了!再小点!");
            continue;
        }
    }
}
