#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t id = fork();
    int status;
    if (id == 0)
    {
        // 子进程
        sleep(3);
        printf("子进程\n");
        setsid();
        exit(0);
    }
    else
    {
        // 父进程
        printf("父进程!\n");
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("子进程正常结束\n");
        }
        printf("父进程结束!\n");
    }
    return 0;
}
