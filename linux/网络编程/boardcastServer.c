
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BROADCAST_PORT 12345
#define MAX_BUFFER_SIZE 1024

int main()
{
    int udp_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];

    // Create a UDP socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0); // 普通的UDP
    if (udp_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address for receiving broadcasts
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // 接收任意ip
    server_addr.sin_port = htons(BROADCAST_PORT);

    // Bind the socket to the server address
    if (bind(udp_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(udp_socket);
        exit(EXIT_FAILURE);
    }

    printf("UDP Broadcast Server is listening on port %d...\n", BROADCAST_PORT);

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        // Receive data from a client
        ssize_t bytes_received = recvfrom(udp_socket, buffer, sizeof(buffer), 0,
                                          (struct sockaddr *)&client_addr, &client_addr_len);

        if (bytes_received == -1)
        {
            perror("recvfrom");
        }
        else
        {
            printf("Received from %s:%d: %s\n", inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port), buffer);

            // Process the received data as needed

            // Send a response to the client
            // (e.g., echo the received message back to the sender)
            ssize_t bytes_sent = sendto(udp_socket, buffer, bytes_received, 0,
                                        (struct sockaddr *)&client_addr, client_addr_len);
            if (bytes_sent == -1)
            {
                perror("sendto");
            }
        }
    }

    close(udp_socket);
    return 0;
}