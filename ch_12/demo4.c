#include <stdio.h>

void outerFunction()
{
    // �����ڲ�������ͨ������ָ��ʵ�֣�
    void innerFunction()
    {
        printf("This is an \"internal\" function.\n");
    }

    // ʹ�ú���ָ���������ڲ�����
    // void (*functionPointer)() = innerFunction;
    innerFunction();
}

int main()
{
    outerFunction();

    return 0;
}