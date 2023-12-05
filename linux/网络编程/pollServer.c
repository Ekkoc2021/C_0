#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include <errno.h>

#define MAX_CLIENTS 5
#define PORT 8080

int main()
{
    int server_socket, new_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);
    struct pollfd fds[MAX_CLIENTS + 1]; // +1 for the server_socket
    char buffer[1024];
    int clientCount = 0;

    // Create server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set server address information
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_socket, 5) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Initialize the pollfd structure for the server socket
    fds[0].fd = server_socket;
    fds[0].events = POLLIN;
    clientCount++;

    for (int i = 1; i <= MAX_CLIENTS; i++)
    {
        fds[i].fd = -1; // Initialize client sockets as unused
    }

    while (1)
    {
        int activity = poll(fds, clientCount + 1, -1);

        if (activity == -1)
        {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        if (fds[0].revents & POLLIN)
        {
            // New client connection
            if ((new_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length)) == -1)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            if (clientCount >= MAX_CLIENTS + 1)
            {
                printf("Too many clients. Connection rejected.\n");
                write(new_socket, "Server is busy. Try again later.\n", sizeof("Server is busy. Try again later.\n"));
                close(new_socket);
            }
            else
            {

                for (int i = 1; i < MAX_CLIENTS + 1; i++)
                {
                    if (fds[i].fd == -1)
                    {
                        fds[i].fd = new_socket;
                        fds[i].events = POLLIN;
                        clientCount++;
                        printf("New connection, socket fd is %d\n", new_socket);
                        break;
                    }
                }
            }
        }

        for (int i = 1; i <= MAX_CLIENTS; i++)
        {
            if (fds[i].fd != -1 && (fds[i].revents & POLLIN))
            {
                // Client data available for reading
                int valread = read(fds[i].fd, buffer, sizeof(buffer));
                if (valread <= 0)
                {
                    // Client disconnected
                    printf("Client %d disconnected\n", fds[i].fd);
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    clientCount--;
                }
                else
                {
                    // Process client data
                    buffer[valread] = '\0';
                    printf("Received data from client %d: %s", fds[i].fd, buffer);
                }
            }
        }
    }

    // Close the server socket
    close(server_socket);

    return 0;
}