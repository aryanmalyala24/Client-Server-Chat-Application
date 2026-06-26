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
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        return 1;
    }

    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup Failed.\n");
        return 1;
    }

    SOCKET sockfd;
    int portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == INVALID_SOCKET)
        error("Socket creation failed.");

    server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        printf("No such host.\n");
        WSACleanup();
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);

    memcpy(&serv_addr.sin_addr.s_addr,
           server->h_addr_list[0],
           server->h_length);

    if (connect(sockfd, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) == SOCKET_ERROR)
        error("Connection failed.");

    printf("Connected to server.\n");

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));

        printf("You: ");
        fgets(buffer, sizeof(buffer), stdin);

        n = send(sockfd, buffer, strlen(buffer), 0);

        if (n == SOCKET_ERROR)
            error("Send failed.");

        if (strncmp(buffer, "Bye", 3) == 0)
            break;

        memset(buffer, 0, sizeof(buffer));

        n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);

        if (n <= 0)
            break;

        buffer[n] = '\0';

        printf("Server: %s", buffer);

        if (strncmp(buffer, "Bye", 3) == 0)
            break;
    }

    closesocket(sockfd);
    WSACleanup();

    return 0;
}