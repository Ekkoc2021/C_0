#define _STRDEBUG_

typedef struct
{
    char *ch;
    int length;
} Str;

// 求解next数组,substr中存放字符串从下标1开始
// next数组的含义,模式串中第i位对应next数组,也就是模式串中第1~i-1位组成的字符串的最大前后缀长度+1
// 模式匹配中则不表示,当前第i位匹配失败时,调整到模式的第next[i]位进行匹配
void getnext(Str substr, int next[])
{
    // next数组求解的思路就是将模式串已经求取成功next数组部分当做模式串做一次匹配!

    // substr中ch是从1开始存数据
    // next的长度为substr.length+1,首位也就是next[0]没有意义

    int i, j; // 由于substr.ch为索引1开始存储的字符串,下标和第几位相同
    // i:当前要求的最大前后缀的子串的末尾
    // j:求取当前最大前后缀的初始化阶段,含义为1到i-1位的字符串的最大前缀的末位的下一位,也就是next[i]
    // 由next数组的定义,当求得1~i的最大前后缀后需要加1,然后填入next[i+1]
    // 显然初始阶段,如果substr.ch[i] == substr.ch[j],说明当前最大前后缀只要在1~i-1的最大前后缀长度+1即可,也就是next[i+1]=next[i]+1即可
    // 初始阶段不相等,需要重置j的,再次看做两个字符串匹配问题,通过next数组快速回溯重置j

    next[1] = 0;
    i = 1, j = next[1];
    // next数组的第1位不需要求,默认为0
    // 从next的第二位求起,通过上面i与j的定义,i=1,j=next[1]

    while (i < substr.length)
    {

        if (j == 0 || substr.ch[i] == substr.ch[j])
        {
            // j==0的含义,就是没子串,最大前后缀为0
            // j!=0,但是 substr.ch[i] == substr.ch[j]说明,最大前后缀为j+1
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
        /*

            如此回溯的原因:j != 0同时substr.ch[i] != substr.ch[j],j=0的含义已经解释

            这个时候1~i最长前后缀不可能在ch[j]之后,如果存在,那么一定也是1~i-1的最长前后缀,这和已经求出的1~i-1的最长前后缀长度j-1矛盾,这个信息使得我们排除了一部分
            本来我们要在1~j找最长前缀,已经知道1~j-1和i-1-(j-1)~i-1相等, 所以我们判断substr.ch[i] == substr.ch[j],结果是不等所以跳到了这里!!
            所以我们只要在1~j-1之间找一个从1~i最长前缀即可
            暴力的解法就是:
            就是逐渐缩小范围,然后依次比较:
                范围到1~i-1:
                    ch[1]==ch[j-i+1],ch[2]==ch[j-i+2]...,ch[i-1]==ch[j]
                出现不匹配,再次缩小到1~i-2
                    ch[1]==ch[j-i+2],ch[2]==ch[j-i+3]...,ch[i-2]==ch[j]
                ...如此重复直到完全匹配,或缩小到ch[1]==ch[j]都不匹配的时候说明最长前后缀为0

            上面的操作如此似曾相识!其实就是我们在使用暴力匹配多个字符之后出现匹配失败时,逐渐右移动模式串逐个再次匹配的过程
            我们解决这个问题的方法就是提前找字串的next数组,匹配失败直接跳转到对应位置继续重新匹配,ok!我们去把从1~j作为一个模式串去找到的next数组?
            等等!从1~j的next数组我们已经找过了直接用就行了
                于是:j=next[j],再次进行substr.ch[i] == substr.ch[j],同时j不等于0,再不匹配继续回溯

        */
    }
}

// todo 修改next数组,使得能处理从0开始字符串!!!

//----------------TEST-------------------
#ifdef _STRDEBUG_
#include <stdio.h>
int main(int argc, char const *argv[])
{
    Str str = {.ch = " ABABABBB", .length = 9};
    int mynext[str.length + 1];
    getnext(str, mynext);
    for (int i = 0; i < str.length; i++)
    {
        printf(" %c ", str.ch[i]);
    }
    printf("\n");
    for (int i = 0; i < str.length; i++)
    {
        printf(" %d ", mynext[i]);
    }
    return 0;
}
#endif
//---------------------------------------
