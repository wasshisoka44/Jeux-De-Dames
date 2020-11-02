#ifndef H_DAME
#define H_DAME

#include <stdio.h>
#include <stdlib.h>

#define J2_PION 2
#define J2_DAME 4
#define J1_PION  1
#define J1_DAME  3
#define VIDE  0
#define TAILLE 10
#define J2 0
#define J1 1

typedef struct pion
{
    int x;
    int y;
} Pion;

void start(int plateau[]);
Pion choisir_pion();
void affiche_plateau(int plateau[]);

static int nb_noir = 20;
static int nb_blanc = 20;

#endif
