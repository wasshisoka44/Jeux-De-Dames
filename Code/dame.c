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

/* vérifie que le coup est règlementaire */
Booleen verif_coup(int plateau[], Pion p, Pion p_dest)
{
    if (p_dest.x % 2 == p_dest.y % 2)
    {
        printf("mouvement interdit : ce n'est pas un déplacement diagonal.\n");
        return false;
    }

    //vérifie qu'on ne dépasse pas la limite de déplacement des pions
    if (plateau[p.x * TAILLE + p.y] == J2_PION || plateau[p.x * TAILLE + p.y] == J1_PION)
    {
        //le joueur se déplace de 2 cases sur un coté => veut prendre un pion ennemi
        if (abs(p.y - p_dest.y) == 2)
        {
            //doit vérifier qu'il y a bien un pion ennemi entre le départ et l'arrivée.
        }

        //mettre la transformation en dame ici ?
    }
}

/* à appeler avant chaque choix du joueur pour s'assurer qu'il fait le meilleur coup */
void verif_coup_obligatoire(int plateau[], int joueur)
{
}

/* simule un tour d'action d'un joueur */
void jouer_coup(int plateau[], int joueur)
{
    Booleen verif = true;
    Pion p, p_dest;
    while (verif)
    {
        printf("chosir le pion à jouer.\n");
        p = choisir_case();
        printf("x = %d, y = %d\n", p.x, p.y);
        while (plateau[p.x * TAILLE + p.y] % 2 != joueur || plateau[p.x * TAILLE + p.y] == VIDE)
        {
            printf("\nVous devez choisir un pion qui vous appartient.\n");
            p = choisir_case();
            printf("x = %d, y = %d\n", p.x, p.y);
        }

        printf("chosir la destination.\n");
        p_dest = choisir_case();
        while (plateau[p_dest.x * TAILLE + p_dest.y] != VIDE)
        {
            printf("choisir une destination valide\n");
            p_dest = choisir_case();
        }
        if (!verif_coup(plateau, p, p_dest))
            verif = false;
    }
    plateau[p_dest.x * TAILLE + p_dest.y] = plateau[p.x * TAILLE + p.y];
    plateau[p.x * TAILLE + p.y] = VIDE;
}

/* vérifie que le jeu est terminé */
Booleen game_over(int plateau[])
{
    if (nb_blanc <= 0 || nb_noir <= 0)
        return true;
    return false;
}

void indice(int taille){
    printf("    ");
    for (int i=0; i<taille; i++){
        printf("%d ",i);
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

/* vous avez pas besoin que je vous dise ce que fait cette fonction si ?*/
int global()
{
    int plateau[TAILLE * TAILLE];

    init_game(plateau);
    afficher_plateau(plateau);
    while (1)
    {
        jouer_coup(plateau, J2);
        afficher_plateau(plateau);
        if (game_over(plateau))
        {
            printf("Blanc gagne !\n");
            break;
        }
        jouer_coup(plateau, J1);
        afficher_plateau(plateau);
        if (game_over(plateau))
        {
            printf("Noir gagne !\n");
            break;
        }
    }
    return 0;
}