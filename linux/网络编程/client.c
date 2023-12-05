#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int client_socket;
    struct sockaddr_in server_address;
    char server_ip[] = "127.0.0.1"; // 服务器的IP地址
    int server_port = 8080;         // 服务器的端口号
    char message[1024];

    // 创建套接字
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址信息
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // 从键盘输入数据并发送到服务器
    while (1)
    {
        printf("Enter a message (or 'q' to quit): ");
        fgets(message, sizeof(message), stdin);

        // 如果输入 'q'，则退出循环
        if (message[0] == 'q' || message[0] == 'Q')
        {
            break;
        }

        // 发送数据到服务器
        if (send(client_socket, message, strlen(message), 0) == -1)
        {
            perror("send");
            exit(EXIT_FAILURE);
        }

        printf("Message sent to server: %s", message);
    }

    // 关闭套接字
    close(client_socket);

    return 0;
}