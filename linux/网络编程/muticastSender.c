#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MULTICAST_GROUP "224.0.0.1"
#define PORT 12345

int main()
{
    int sockfd;
    struct sockaddr_in multicast_addr;
    char message[] = "Hello, Multicast Group!";

    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置多播组地址和端口
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    multicast_addr.sin_port = htons(PORT);

    while (1)
    {
        // 发送消息到多播组
        if (sendto(sockfd, message, sizeof(message), 0, (struct sockaddr *)&multicast_addr, sizeof(multicast_addr)) < 0)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        printf("Sent: %s\n", message);
        sleep(2); // 间隔2秒发送一次消息
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}