#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "dame.h"

int main(int argc, char *argv[])
{
    int sockfd, len, connfd[2], plateau[TAILLE * TAILLE];
    Pion p;

    struct sockaddr_in servaddr, cliaddr;

    if (argc != 2)
    {
        printf("Il faut un port\n");
        return 0;
    }

    //création de socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Erreur : Socket");
        exit(-1);
    }

    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(atoi(argv[1]));

    //lie la socket à l'adresse IP
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Erreur : Socket");
        exit(-1);
    }

    //serveur écoute
    if ((listen(sockfd, 1)) != 0)
    {
        printf("Erreur \n");
        exit(0);
    }
    printf("Le serveur fonctionne...\n");

    len = sizeof(cliaddr);

    //accepte le client
    for (int i = 0; i < 2; i++)
    {
        if ((connfd[i] = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0)
        {
            printf("Connection avec le client échouer\n");
            exit(0);
        }
        else
            printf("Le joueur %d vient de se connecter\n", i + 1);
    }

    char buf[100] = "A vous de jouez ! ";

    start(plateau);
    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            write(connfd[i], (const char *)&plateau, sizeof(plateau));
            printf("Le Joueur %d dépalce un piont\n", i + 1);
            write(connfd[i], (const char *)&buf, sizeof(buf));
            recv(connfd[i], &p, sizeof(p), 0);
            printf("Le joueur %d à déplacer le pion :\n x : %d\ny : %d\n", i + 1, p.x, p.y);
        }
    }
    close(sockfd);
    return 0;
}