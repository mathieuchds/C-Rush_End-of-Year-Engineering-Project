#ifndef PARTITION_H
#define PARTITION_H

#include <stdio.h>
#include <stdlib.h>
#include "listes.h"
#define NOMBRE_ELEM_MAX 25000
/* implémentation des fonctions de partition avec marqueurs */

extern int ensemble[NOMBRE_ELEM_MAX];
extern int taille_partition;

extern int parent[NOMBRE_ELEM_MAX];
extern int hauteur[NOMBRE_ELEM_MAX];
extern int taille_partition_forest;

void init_partition_marqueurs(int taille);

int recuperer_classe_marqueurs(int x);
void fusion_marqueurs( int x, int y);
list * lister_classe_marqueurs(int classe);

list ** lister_partition_marqueurs();


/* Implémentation des fonctions de partition avec arborescence*/



void init_partition_forest(int taille);
int recuperer_classe_forest(int x);
void fusion_forest(int x, int y);
list * lister_classe_forest(int classe);
list ** lister_partition_forest();

#endif // PARTITION_H