// 使用系统调用实现 cp命令
#include <stdio.h>
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
void usage(char *arg0)
{
    printf("usage: %s source destination\n", arg0);
}
int main(int argc, char *args[])
{
    if (argc < 3)
    {
        usage(args[0]);
    }

// test
#ifdef DEBUG
    printf("source:%s \n", args[1]);
    printf("destination:%s \n", args[2]);
#endif
    int fd = open(args[1], O_RDONLY, 0666);
    if (fd < 0)
    {
        perror("源文件不存在");
        exit(EXIT_FAILURE);
    }
    int desfd = open(args[2], O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (desfd < 0)
    {
        perror("文件已经存在!");
        exit(EXIT_FAILURE);
    }

    char buff[32];
    int length;
    while ((length = read(fd, buff, sizeof(buff))) > 0)
    {
        // 0 结尾 -1 发生错误, 大于0,读取的结果
        write(desfd, buff, length);
    }

    fsync(desfd); // 刷新
    close(fd);
    close(desfd);

    return 0;
}
