#include <stdio.h>

int main()
{
    // __DATE__ : Mmm dd yyyy形式的字符串
    printf("Compilation date: %s\n", __DATE__);

    // __FILE__ : 当前源代码文件名称
    printf("Current file: %s\n", __FILE__);

    // __LINE__ : 当前输出位置的行号:12
    printf("Current line number: %d\n", __LINE__);

// __STDC__ : 设置为1表示遵循c标准
#ifdef __STDC__
    printf("STDC is defined and set to %d\n", __STDC__);
#else
    printf("STDC is not defined\n");
#endif

// __STDC_HOSTED__ : 为本机设置环境为1,否则为0
#ifdef __STDC_HOSTED__
    printf("STDC_HOSTED is defined and set to %d\n", __STDC_HOSTED__);
#else
    printf("STDC_HOSTED is not defined\n");
#endif

// __STDC_VERSION__ : 为c99时设置为199901L
#ifdef __STDC_VERSION__
    printf("STDC_VERSION is defined and set to %ld\n", __STDC_VERSION__);
#else
    printf("STDC_VERSION is not defined\n");
#endif

    // __TIME__ : 源文件编译时间
    printf("Compilation time: %s\n", __TIME__);

    return 0;
}