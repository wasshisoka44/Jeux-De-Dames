#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "dame.h"

int main(int argc, char *argv[])
{
    int sockfd, connfd, plateau[TAILLE * TAILLE];
    char message[100];
    Pion p;
    struct sockaddr_in servaddr;

    if (argc != 3)
    {
        printf("Il vous faut une adresse et un port\n");
        return 0;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Erreur : Socket");
        exit(-1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &servaddr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("La connection avec le serveur à échouer\n");
        exit(0);
    }
    else
        printf("Connecté au serveur\n");

    while (1)
    {
        recv(sockfd, &plateau, sizeof(plateau), 0);
        recv(sockfd, &message, sizeof(message), 0);
        printf("%s\n", message);
        p=choisir_pion(plateau);
        deplace_pion(p,plateau);
        write(sockfd, (const char *)&p, sizeof(p));
    }
    close(sockfd);
    return 0;
}