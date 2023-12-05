#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/local_socket1"

int main()
{
    int sockfd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t server_addr_len = sizeof(server_addr);
    socklen_t client_addr_len = sizeof(client_addr);
    char send_buffer[256];
    char recv_buffer[256];

    // 创建本地套接字
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置本地套接字地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // 设置客户端套接字地址结构
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, "/tmp/client_socket", sizeof(client_addr.sun_path) - 1);

    // 绑定客户端套接字到本地地址
    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // 发送消息到接收方
        const char *message = "Hello from sender!";
        if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }

        printf("Sent: %s\n", message);

        // 接收来自接收方的回复消息
        ssize_t recv_len = recvfrom(sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr *)&server_addr, &server_addr_len);
        if (recv_len < 0)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        recv_buffer[recv_len] = '\0';
        printf("Received reply: %s\n", recv_buffer);
        sleep(2);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}