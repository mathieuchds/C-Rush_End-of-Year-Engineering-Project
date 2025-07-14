#ifndef NOEUD_ARRETE_H
#define NOEUD_ARRETE_H

#include <stdio.h>
#include <stdlib.h>
#define NOMBRE_NOEUDS_MAX 25000 // À ajuster si besoin
#define P_MAX 500
#define N_MAX 500
// Déclaration des variables globales
extern int aretes[NOMBRE_NOEUDS_MAX][2];
extern int nombre_noeuds;
extern int nombre_aretes;

extern int nb_ligne;
extern int nb_colonne;

// Fonctions de manipulation du graphe
void init_noeud_arrete();
void remplir_aleatoire(int nbr_noeuds, int nbre_aretes);
void remplir_graphe_labyrinthe(int nbr_ligne_local,int nbr_colonne_local);
void genenerer_fichier_dot(const char *nom_fichier);
void extraire_composantes_connexes_noeud_arete();
int nombre_classe_noeud_arete();
void creer_graph_partition_noeud_arrete(const char *nom_fichier);

#endif // NOEUD_ARRETE_H