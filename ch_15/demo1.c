#include <stdio.h>
struct bf2
{
    unsigned short a : 15; // 15λ shortΪ16λ
    unsigned short b : 15; // b����������һshort������,a��b����һ���հ�λ
    unsigned short : 1;    // δ�������ֶο���������հ�λ
    unsigned short c : 12; // b��c����һ���հ�λ
    unsigned short : 0;    // ǿ����һ���ֶζ��뵽�µ�16λ��
    unsigned short d : 2;  // ����,����Ҳ��ǿ�ƶ���
} t;

int main(int argc, char const *argv[])
{
    printf("%d", sizeof(t));
    return 0;
}
