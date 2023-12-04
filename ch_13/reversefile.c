#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *file = fopen("reversefile.text", "rb");
    if (file == NULL)
    {
        perror("Error opening the file");
        return 1;
    }

    // ��ȡ�ļ���С
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    // �����ȡ�ļ�
    char ch;
    for (long i = file_size - 1; i >= 0; i--)
    {
        fseek(file, i, SEEK_SET);
        ch = fgetc(file);
        // ��������ԶԶ�ȡ�����ݽ��д��������ӡ��洢���������ݽṹ��
        printf("%c", ch);
    }

    fclose(file);

    file = fopen("reversefile.text", "r");
    if (file == NULL)
    {
        perror("Error opening the file");
        return 1;
    }

    // ���ж�ȡ�ļ����������
    char buffer[256]; // ���������ڴ洢ÿ�е�����
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // ��������ԶԶ�ȡ��ÿ�����ݽ��д��������ӡ��洢���������ݽṹ��
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
