#include <stdio.h>

void demoFunction()
{
    // ������д����������ľ�̬����
    static int staticVar = 0;

    // ��ӡ��̬������ֵ
    printf("Static Variable: %d\n", staticVar);

    // �޸ľ�̬������ֵ
    staticVar++;
}

int main()
{
    // ��ε���demoFunction����
    demoFunction(); // ��� Static Variable: 0
    demoFunction(); // ��� Static Variable: 1
    demoFunction(); // ��� Static Variable: 2

    return 0;
}