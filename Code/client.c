#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 256
#define CLIENT_PORT 1234

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        puts("usage : ./tcp_client [addr] [port]");
        exit(1);
    }
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        dprintf(2, "Socket failed\n");
        exit(1);
    }

    int cs = socket(AF_INET, SOCK_STREAM, 0);
    if (cs < 0)
    {
        dprintf(2, "Socket failed\n");
        exit(1);
    }

    // Client info
    struct sockaddr_in csin;
    csin.sin_family = AF_INET;
    csin.sin_port = htons(CLIENT_PORT);
    csin.sin_addr.s_addr = htonl(INADDR_ANY);
    for (int i = 0; i < 8; i++)
    {
        csin.sin_zero[i] = 0;
    }

    // Server info
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons((unsigned short)atol(argv[2]));
    inet_aton(argv[1], &sin.sin_addr);
    for (int i = 0; i < 8; i++)
    {
        sin.sin_zero[i] = 0;
    }

    // Debug
    printf("Server: %s, Client: %s\n", inet_ntoa(sin.sin_addr), inet_ntoa(csin.sin_addr));

    if (connect(s, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) < 0)
    {
        dprintf(2, "Connect failed : %s\n", strerror(errno));
        exit(1);
    }

    // Msg buffer
    char pion[BUF_SIZE + 1];
    char x[BUF_SIZE + 1];
    char y[BUF_SIZE + 1];
    bzero(pion, BUF_SIZE + 1);
    bzero(x, BUF_SIZE + 1);
    bzero(y, BUF_SIZE + 1);
    ssize_t msg_len;

    

    while (1)
    {
        bzero(pion, BUF_SIZE + 1);
        printf("Quel pion voulez vous bougez ? : ");
        fgets(pion, BUF_SIZE, stdin);
        if (!strlen(pion))
            break;
        printf("Vous déplacez le pion %s", pion);

        bzero(x, BUF_SIZE + 1);
        printf("Nouvelle coordonnée de x : ");
        fgets(x, BUF_SIZE, stdin);

        bzero(y, BUF_SIZE + 1);
        printf("Nouvelle coordonnée de y : ");
        fgets(y, BUF_SIZE, stdin);

        printf("Le pion %s a pour nouvelle coordonnée [%s,%s]", pion, x,y);
        // Send input stream
        msg_len = send(s, (void *)pion, strlen(pion), 0);
        if (msg_len < 0)
        {
            dprintf(2, "Send failed : %s\n", strerror(errno));
            close(s);
            exit(1);
        }
        // Receive server response
        if ((msg_len = recv(s, (void *)pion, BUF_SIZE, 0)) <= 0)
        {
            printf("Server offline : %s\n", strerror(errno));
        }
        printf("\n");
    }
    puts("Connection ended");
    close(s);
    close(cs);
    return (0);
}
