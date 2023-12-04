#include <stdio.h>

int main()
{
    // __DATE__ : Mmm dd yyyy��ʽ���ַ���
    printf("Compilation date: %s\n", __DATE__);

    // __FILE__ : ��ǰԴ�����ļ�����
    printf("Current file: %s\n", __FILE__);

    // __LINE__ : ��ǰ���λ�õ��к�:12
    printf("Current line number: %d\n", __LINE__);

// __STDC__ : ����Ϊ1��ʾ��ѭc��׼
#ifdef __STDC__
    printf("STDC is defined and set to %d\n", __STDC__);
#else
    printf("STDC is not defined\n");
#endif

// __STDC_HOSTED__ : Ϊ�������û���Ϊ1,����Ϊ0
#ifdef __STDC_HOSTED__
    printf("STDC_HOSTED is defined and set to %d\n", __STDC_HOSTED__);
#else
    printf("STDC_HOSTED is not defined\n");
#endif

// __STDC_VERSION__ : Ϊc99ʱ����Ϊ199901L
#ifdef __STDC_VERSION__
    printf("STDC_VERSION is defined and set to %ld\n", __STDC_VERSION__);
#else
    printf("STDC_VERSION is not defined\n");
#endif

    // __TIME__ : Դ�ļ�����ʱ��
    printf("Compilation time: %s\n", __TIME__);

    return 0;
}