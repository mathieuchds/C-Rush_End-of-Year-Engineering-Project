
#ifndef MOTEUR_LABYRINTHE_H
#define MOTEUR_LABYRINTHE_H

#include <math.h>
#include "kruskal.h"

#define EST 4
#define NORD 2
#define OUEST 1
#define SUD 8

typedef struct{
    int * construction;
    int * poids_cases;
    int * boutons;
    int nb_colonne;
    int nb_ligne;
    int nb_boutons;
}labyrinthe;

typedef struct{
    labyrinthe * lab;
    int * memoire;
} vision_monstre;

typedef struct point_interet{
    int spawn_player;
    int spawn_monster; 
    int exit;
}point_interet;

vision_monstre *init_vision_monstre(labyrinthe *lab);
void verifie_case_memoire(vision_monstre *vm, int case_index, long unsigned int valeur);
void update_case_memoire(vision_monstre *vm, int case_index, long unsigned int valeur) ;
void free_vision_monstre(vision_monstre *vm);
labyrinthe *init_labyrinthe( int nb_ligne,int nb_colonne,int nb_boutons);
void generer_boutons_ecartes(labyrinthe *laby);
void calcul_construction(labyrinthe *lab);
void affiche_tab_construction( labyrinthe *lab);
void affiche_tab_poids(labyrinthe *laby);
void affiche_boutons(labyrinthe *laby);
void labyrinthe_textuel( labyrinthe *lab);
void generer_fichier_maze( char *nom_fichier, labyrinthe *lab);
labyrinthe * lire_fichier_maze(char *nom_fichier);
void init_points_interet(labyrinthe *laby, point_interet *pi);
void free_labyrinthe(labyrinthe *lab);
void poids_aleatoire(labyrinthe * lab);
void poids_logique(labyrinthe *lab);
void poids_logique_centrique(labyrinthe *lab);
void poids_classique(labyrinthe *lab) ;
#endif // MOTEUR_LABYRINTHE_H