#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BROADCAST_PORT 12345
#define BROADCAST_ADDR "255.255.255.255"
#define MAX_BUFFER_SIZE 1024

int main()
{
    int udp_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t server_addr_len = sizeof(server_addr);
    char buffer[MAX_BUFFER_SIZE];

    // Create a UDP socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Enable broadcast option for the socket
    int broadcast_enable = 1;
    if (setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) == -1)
    {
        perror("setsockopt");
        close(udp_socket);
        exit(EXIT_FAILURE);
    }

    // Configure server address for broadcasting
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(BROADCAST_ADDR);
    server_addr.sin_port = htons(BROADCAST_PORT);

    while (1)
    {
        printf("Enter message to broadcast (or 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Remove newline character from the input
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }

        // Send the message as a UDP broadcast
        ssize_t bytes_sent = sendto(udp_socket, buffer, strlen(buffer), 0,
                                    (struct sockaddr *)&server_addr, sizeof(server_addr));
        if (bytes_sent == -1)
        {
            perror("sendto");
            close(udp_socket);
            exit(EXIT_FAILURE);
        }

        // Receive response from the server (optional)
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recvfrom(udp_socket, buffer, sizeof(buffer), 0,
                                          (struct sockaddr *)&server_addr, &server_addr_len);
        if (bytes_received == -1)
        {
            perror("recvfrom");
        }
        else
        {
            printf("Received response from server: %s\n", buffer);
        }
    }

    close(udp_socket);
    return 0;
}