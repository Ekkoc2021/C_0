#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#define MULTICAST_GROUP "224.0.0.1"
#define PORT 12345

int main()
{
    int sockfd;
    struct sockaddr_in multicast_addr;
    struct ip_mreq mreq;
    char buffer[1024];

    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 正常设置地址
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 接收任意地址
    multicast_addr.sin_port = htons(PORT);

    // 绑定到特定端口
    if (bind(sockfd, (struct sockaddr *)&multicast_addr, sizeof(multicast_addr)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 加入多播组
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    // 设置为多播
    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // 接收多播消息
        ssize_t recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, 0);
        if (recv_len < 0)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }
        buffer[recv_len] = '\0';
        printf("Received: %s\n", buffer);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}