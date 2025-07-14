#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "noeud_arrete.h"
#include <time.h>
extern int nb_aretes_A;
extern int aretes_A[(P_MAX-1)*N_MAX+P_MAX*(N_MAX-1)][2];

void algorithme_kruskal( int ,int);
void algorithme_kruskal_densite( int ,int,int p);
void melange_Fisher_Yates(int nombre_aretes);
void generer_fichier_dot_A(const char *nom_fichier);
//void generer_fichier_maze(const char *nom_fichier);

#endif // KRUSKAL_Hg