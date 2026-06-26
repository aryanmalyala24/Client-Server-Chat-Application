#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

void error(const char *msg)
{
    fprintf(stderr, "%s Error Code: %d\n", msg, WSAGetLastError());
    WSACleanup();
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Port not provided.\n");
        return 1;
    }

    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup Failed.\n");
        return 1;
    }

    SOCKET sockfd, newsockfd;
    int portno, n;

    char buffer[256];

    struct sockaddr_in serv_addr, cli_addr;
    int clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == INVALID_SOCKET)
        error("Socket creation failed.");

    memset(&serv_addr, 0, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
        error("Binding failed.");

    if (listen(sockfd, 5) == SOCKET_ERROR)
        error("Listen failed.");

    printf("Server started on port %d\n", portno);
    printf("Waiting for client...\n");

    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if (newsockfd == INVALID_SOCKET)
        error("Accept failed.");

    printf("Client connected.\n");

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        n = recv(newsockfd, buffer, sizeof(buffer) - 1, 0);

        if (n <= 0)
            break;

        buffer[n] = '\0';

        printf("Client: %s", buffer);

        memset(buffer, 0, sizeof(buffer));

        fgets(buffer, sizeof(buffer), stdin);

        n = send(newsockfd, buffer, strlen(buffer), 0);

        if (n == SOCKET_ERROR)
            error("Send failed.");

        if (strncmp(buffer, "Bye", 3) == 0)
            break;
    }

    closesocket(newsockfd);
    closesocket(sockfd);

    WSACleanup();

    return 0;
}