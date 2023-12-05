#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[1024];
    const char *message = "Hello from server!";

    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);       // 设置监听端口
    server_addr.sin_addr.s_addr = INADDR_ANY; // 监听所有可用的网络接口

    // 绑定套接字到地址和端口
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port 8080...\n");

    // 接收客户端发送的数据
    ssize_t bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);

    if (bytes_received == -1)
    {
        perror("recvfrom");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("Received data from client: %s\n", buffer);

    // 向客户端发送响应消息
    ssize_t bytes_sent = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&client_addr, client_addr_len);

    if (bytes_sent == -1)
    {
        perror("sendto");
    }
    else
    {
        printf("Sent data to client: %s\n", message);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}