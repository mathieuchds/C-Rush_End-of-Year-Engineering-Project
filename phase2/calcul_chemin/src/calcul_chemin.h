#ifndef CALCUL_CHEMIN
#define CALCUL_CHEMIN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "kruskal.h"
#include "Moteur_labyrinthe.h"

typedef struct{
    int * deja_vu;
}S;
typedef struct{
    int depart;
    int arrive;
    int * chemin;
    int taille_chemin;
    labyrinthe * labyrinthe;
    int * noeuds_visites;
}chemin_plus_court;


typedef struct {
    int* chemin;           // Chemin parcouru (ordre de visite, peut contenir plusieurs fois le même noeud)
    int taille_chemin;     // Taille du chemin (nombre d'étapes)
    int* distance_connue;  // Distance minimale connue à chaque étape 
    int* exploration;       // Ordre d'exploration des noeuds
    int taille_exploration; // Taille de l'ordre d'exploration
    labyrinthe* labyrinthe; // Pointeur vers le labyrinthe
} parcours_chemin;

typedef struct {
    int *noeuds_visites;      // Chemin parcouru, terminé par -1
    int *nb_passages;         // Tableau de taille nb_ligne*nb_colonne, nombre de passages par noeud
} resultat_chemin_inconnu;


S* init_S(int nombre_noeuds);
S* BFS(labyrinthe* lab, int origine) ;
chemin_plus_court * chemin_plus_court_bfs(labyrinthe* lab, int origine, int arrive);
void free_chemin_plus_court(chemin_plus_court* c);
chemin_plus_court* chemin_plus_court_dijkstra(labyrinthe* lab, int origine, int arrive) ;
chemin_plus_court* chemin_plus_court_A_etoiles(labyrinthe* lab, int origine, int arrive, int (*heuristique)(int, int, labyrinthe*));
int heuristique_euclidienne(int noeud, int arrive, labyrinthe* lab);
int heuristique_manhattan(int noeud, int arrive, labyrinthe* lab) ;
int heuristique_tchebychev(int noeud, int arrive, labyrinthe* lab);
void afficher_labyrinthe_avec_chemin(chemin_plus_court* c);
void afficher_labyrinthe_avec_chemin_dijkstra(chemin_plus_court* c) ;
void afficher_labyrinthe_avec_chemin_A_etoiles(chemin_plus_court* c);

void affiche_distance(labyrinthe *lab, int* arrives, int nb_arrivees);
int* dijkstra_distances_depuis_arrivee_multiple(labyrinthe* lab, int* arrivees, int nb_arrivees) ;
void afficher_ordre_cases(labyrinthe* lab, parcours_chemin* pc);
parcours_chemin* destination_minisante_destination_connue(labyrinthe * lab, labyrinthe * lab_connu, int origine, int * arrivees,int nb_arrivees);
parcours_chemin* destination_minisante_multi_destinations(labyrinthe* lab, labyrinthe* lab_connu, int origine, int* arrivees, int nb_arrivees);
int prochaine_case_destination_connue(labyrinthe *lab, labyrinthe *lab_connu, int origine, int *arrivees, int nb_arrivees) ;
int prochaine_case_destination_connue_vm(labyrinthe *lab, vision_monstre *vm, int origine, int *arrivees, int nb_arrivees, unsigned long int valeur);
void boucle_affichage_prochaine_case(labyrinthe *lab, labyrinthe *lab_connu, int origine, int *arrivees, int nb_arrivees) ;
void boucle_affichage_prochaine_case_vm(labyrinthe *lab, vision_monstre *vm, int origine, int *arrivees, int nb_arrivees, unsigned long int valeur) ;
void afficher_noeuds_visites(int* noeuds_visites) ;
resultat_chemin_inconnu chemin_destination_inconnue(labyrinthe * lab, labyrinthe * G, int origine, int destination);
int prochaine_case_destination_inconnue_vm(labyrinthe *lab, vision_monstre *vm, int origine, int *destination, unsigned long int valeur);
void boucle_affichage_prochaine_case_inconnue_vm(labyrinthe *lab, vision_monstre *vm, int origine, int *destination, unsigned long int valeur);
#endif
