#include <time.h>
/*
ʵ��rand()����==>����α�������
ʹ��time.hͷ�ļ���ȡ��ǰʱ��
*/

static char isSet = 0;
static int se = 1;
int setSend(int seed)
{
    extern int se;
    extern char isSet;
    se = seed;
    isSet = 1;
    return isSet;
}

int randInt()
{
    extern int se;
    if (isSet)
    {
        se = se * 9999823 + 34234;
    }
    se = ((int)time(NULL)) * 9999823 + 34234;
    isSet = 1;
    return (int)(se);
}

// test

// int main(int argc, char const *argv[])
// {
//     int seed = (int)time(NULL);
//     printf("%d %d", time(0), randInt());
//     return 0;
// }