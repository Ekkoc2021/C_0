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

    // 获取文件大小
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    // 倒序读取文件
    char ch;
    for (long i = file_size - 1; i >= 0; i--)
    {
        fseek(file, i, SEEK_SET);
        ch = fgetc(file);
        // 在这里可以对读取的数据进行处理，例如打印或存储到其他数据结构中
        printf("%c", ch);
    }

    fclose(file);

    file = fopen("reversefile.text", "r");
    if (file == NULL)
    {
        perror("Error opening the file");
        return 1;
    }

    // 逐行读取文件并输出内容
    char buffer[256]; // 缓冲区用于存储每行的内容
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // 在这里可以对读取的每行内容进行处理，例如打印或存储到其他数据结构中
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
