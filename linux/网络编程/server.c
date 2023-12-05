#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>

#define MAX_CLIENTS 5
#define PORT 8080

int main()
{
    int clientCount = 0; // 客户端数量
    int server_socket, new_socket, max_socket, activity, valread;
    int client_sockets[MAX_CLIENTS] = {0};
    fd_set readfds;
    char buffer[1024];
    struct sockaddr_in server_addr;

    // 创建服务器套接字
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 准备服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定地址和端口
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(server_socket, 5) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);
    struct timeval timeout;
    timeout.tv_sec = 5; // 设置超时时间为1秒
    timeout.tv_usec = 0;

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);
        max_socket = server_socket;
        timeout.tv_sec = 5; // 设置超时时间为1秒
        timeout.tv_usec = 0;

        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            if (client_sockets[i] > 0)
            {
                FD_SET(client_sockets[i], &readfds);
                if (client_sockets[i] > max_socket)
                {
                    max_socket = client_sockets[i];
                }
            }
        }

        // 使用 select 监听套接字的可读事件
        activity = select(max_socket + 1, &readfds, NULL, NULL, &timeout);
        if ((activity < 0) && (errno != EINTR))
        {
            perror("select");
        }
        printf("进行了一次select!连接数量:%d,activity:%d\n", clientCount, activity);
        if (activity == 0)
        {
            printf("超时\n");
            // 超时，可以执行一些检查操作
            // 如果所有的客户端没有正常关闭而是异常关闭,read返回值将是-1,而不是0,没法即时关闭文件描述符
            // 需要通过一种机制去检测是否断开链接==>可以是在超时的时候检测一遍,但是依旧不保险
            // 还可以通过定时器去整体检查一遍
        }

        if (FD_ISSET(server_socket, &readfds))
        {

            // 有新的连接请求
            if ((new_socket = accept(server_socket, NULL, NULL)) < 0)
            {
                exit(EXIT_FAILURE);
                perror("accept");
            }
            if (clientCount >= MAX_CLIENTS)
            {
                write(new_socket, "服务器正忙!稍后重连!\n", sizeof("服务器正忙!稍后重连!"));
                close(new_socket);
                printf("有新连接!当前连接数量已经满,已经拒绝:%d \n", new_socket);
            }
            else
            {

                clientCount++;
                printf("New connection, socket fd is %d\n", new_socket);

                // 添加新的客户端套接字到数组
                for (int i = 0; i < MAX_CLIENTS; i++)
                {
                    if (client_sockets[i] == 0)
                    {
                        client_sockets[i] = new_socket;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            if (FD_ISSET(client_sockets[i], &readfds))
            {
                // 有数据可读==>socket中=0表示断开连接,同时这里的read是阻塞式的,最好设置为非阻塞
                if ((valread = read(client_sockets[i], buffer, sizeof(buffer))) == 0)
                {
                    // 客户端断开连接
                    printf("客户端:%d断开连接\n", client_sockets[i]);
                    clientCount--;
                    close(client_sockets[i]);
                    client_sockets[i] = 0;
                }
                else
                {
                    // 处理客户端的数据
                    buffer[valread] = '\0';
                    printf("Received data from client %d: %s", client_sockets[i], buffer);
                }
            }
        }
    }
    return 0;
}