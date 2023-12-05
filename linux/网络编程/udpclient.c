#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);                   // 服务器端口号
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器IP地址

    // 向服务器发送数据
    const char *message = "Hello from client!";
    ssize_t bytes_sent = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (bytes_sent == -1)
    {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 接收服务器的响应
    ssize_t bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);

    if (bytes_received == -1)
    {
        perror("recvfrom");
    }
    else
    {
        buffer[bytes_received] = '\0';
        printf("Received data from server: %s\n", buffer);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}