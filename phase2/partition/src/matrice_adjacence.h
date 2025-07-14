#ifndef ADJACENCE_H
#define ADJACENCE_H 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listes.h" 
#include "partition.h"

typedef struct {
    int ** matrice;
    int taille;
} matrice_adjacence;
int nombre_classe();
void extraire_composantes_connexes(matrice_adjacence m);
matrice_adjacence creer_matrice_adjacence(int taille);
void generer_fichier_dot_m(matrice_adjacence m, const char *nom_fichier);
void creer_graph_partition(const char *nom_fichier, matrice_adjacence m);
#endif // ADJACENCE_Hs(m);