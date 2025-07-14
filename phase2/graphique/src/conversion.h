
#ifndef MOTEUR_LABYRINTHE_H
#define MOTEUR_LABYRINTHE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EST 4
#define NORD 2
#define OUEST 1
#define SUD 8

void generer_fichier_maze2(const char *nom_fichier, int *construction_mur, int nb_ligne, int nb_colonne);
int * lire_fichier_maze2(const char *nom_fichier, int *nb_ligne, int *nb_colonne);
#endif // MOTEUR_LABYRINTHE_H