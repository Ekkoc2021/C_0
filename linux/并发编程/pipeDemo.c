#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
int main(int argc, char const *argv[])
{
    // 创建一个无名管道
    int fileDes[2];
    char buff[20];
    if (pipe(fileDes) > 0)
    {
        perror("create pipe:");
        exit(EXIT_FAILURE);
    }

    // 创建一个子进程
    pid_t pid = fork();
    if (pid == 0)
    {
        // 子进程
        close(fileDes[0]);
        //  先写
        write(fileDes[1], "hello world!", 20);
        printf("写结束!\n");
        // sleep(1);

        for (size_t i = 0; i < 2; i++)
        {
            close(fileDes[i]);
            /* code */
        }
        printf("子进程已经关闭写管道!\n");
        sleep(5);
    }
    else
    {
        // 父进程
        close(fileDes[1]);
        sleep(3);
        read(fileDes[0], buff, 20);
        printf("父进程:%s\n", buff);
        // 写
        // write(fileDes[1], "abcdc", 20);

        // 阻塞等待
        waitpid(pid, NULL, 0);
        for (size_t i = 0; i < 2; i++)
        {
            close(fileDes[i]);
            /* code */
        }
    }

    return 0;
}
