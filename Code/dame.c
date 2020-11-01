#include "dame.h"

/* créer un plateau de jeu avec les pions bien placés*/
void init_game(int plateau[])
{

    //créer les cases vides
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            plateau[i * TAILLE + j] = VIDE;
        }
    }

    //créer les pions noires
    for (int i = 0; i < 4; i++)
    {
        for (int j = (i + 1) % 2; j < TAILLE; j += 2)
        {
            plateau[i * TAILLE + j] = J1_PION;
        }
    }

    //créer les pions blancs
    for (int i = TAILLE - 1; i > TAILLE - 5; i--)
    {
        for (int j = (i + 1) % 2; j < TAILLE; j += 2)
        {
            plateau[i * TAILLE + j] = J2_PION;
        }
    }
}

/* demande à l'utilisateur de choisir une case */
Pion choisir_case()
{
    printf("Choisissez un pion !");
    Pion p;
    printf("coordonnée X : ");
    scanf("%d", &p.x);
    while (p.x < 0 || p.x > TAILLE)
    {
        printf("\nveuillez rentrer des coordonnées valides");
        scanf("%d", &p.x);
    }
    printf("coordonnée Y : ");
    scanf("%d", &p.y);
    while (p.y < 0 || p.y > TAILLE)
    {
        printf("\nveuillez entrer des coordonnées valides");
        scanf("%d", &p.y);
    }
    return p;
}

void deplace_pion(Pion p, int plateau[]){
    Pion temp;
    printf("Saisir nouvelle coordonée X: ");
    scanf("%d", &temp.x);
    while (temp.x < 0 || temp.x > TAILLE)
    {
        printf("\nveuillez rentrer des coordonnées valides");
        scanf("%d", &temp.x);
    }
    printf("Saisir nouvelle coordonnée Y : ");
    scanf("%d", &temp.y);
    while (temp.y < 0 || temp.y > TAILLE)
    {
        printf("\nveuillez entrer des coordonnées valides");
        scanf("%d", &temp.y);
    }
    plateau[p.x][p.y]=VIDE;
    plateau[temp.x][temp.y]=J1_PION;
    afficher_plateau(plateau);
}

void indice(int taille)
{
    printf("    ");
    for (int i = 0; i < taille; i++)
    {
        printf("%d ", i);
    }
    printf("\n\n");
}

/* affiche l'état du plateau de jeu */
void afficher_plateau(int plateau[])
{
    indice(TAILLE);
    for (int i = 0; i < TAILLE; i++)
    {
        printf("%d  |", i);
        for (int j = 0; j < TAILLE; j++)
        {
            printf("%d|", plateau[i * TAILLE + j]);
        }
        printf("\n");
    }
    printf("\n");
}

