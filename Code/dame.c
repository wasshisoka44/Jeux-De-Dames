#include "dame.h"

/* créer un plateau de jeu avec les pions bien placés*/
void start(int plateau[])
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
Pion choisir_pion(int plateau[])
{
    affiche_plateau(plateau);
    printf("Choisissez un pion !\n");
    Pion p;
    printf("coordonnee X : ");
    scanf("%d", &p.x);
    while (p.x < 0 || p.x > TAILLE)
    {
        printf("\nLa coordonnee x n'est pas valide");
        scanf("%d", &p.x);
    }
    printf("coordonnee Y : ");
    scanf("%d", &p.y);
    while (p.y < 0 || p.y > TAILLE)
    {
        printf("\nLa coordonnee y n'est pas valide");
        scanf("%d", &p.y);
    }
    return p;
}

void deplace_pion(Pion p, int plateau[]){
    Pion temp;
    printf("Saisir nouvelle coordonee X: ");
    scanf("%d", &temp.x);
    while (temp.x < 0 || temp.x > TAILLE)
    {
        printf("\nLa coordonnee x n'est pas valide");
        scanf("%d", &temp.x);
    }
    printf("Saisir nouvelle coordonnée Y : ");
    scanf("%d", &temp.y);
    while (temp.y < 0 || temp.y > TAILLE)
    {
        printf("\nLa coordonnee y n'est pas valide");
        scanf("%d", &temp.y);
    }
    /*plateau[p.x][p.y]=VIDE;
    plateau[temp.x][temp.y]=J1_PION;*/
    affiche_plateau(plateau);
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
void affiche_plateau(int plateau[])
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

