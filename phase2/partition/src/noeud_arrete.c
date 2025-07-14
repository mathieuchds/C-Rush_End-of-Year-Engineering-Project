#include "noeud_arrete.h"
#include "partition.h"
#include <math.h>


int aretes[NOMBRE_NOEUDS_MAX][2];
int nombre_noeuds;
int nombre_aretes;
int nb_ligne=0;
int nb_colonne=0;
void init_noeud_arrete() {
    nombre_noeuds = 0;
    nombre_aretes = 0;
    for (int i = 0; i < NOMBRE_NOEUDS_MAX; i++) {
        aretes[i][0] = -1;
        aretes[i][1] = -1;
    }
}
void remplir_graphe_labyrinthe(int nbr_ligne_local, int nbr_colonne_local) {
    nb_ligne = nbr_ligne_local;
    nb_colonne = nbr_colonne_local;
    nombre_noeuds = nb_ligne * nb_colonne;
    nombre_aretes = 0;

    // On parcourt chaque case du labyrinthe
    for (int i = 0; i < nb_ligne; i++) {
        for (int j = 0; j < nb_colonne; j++) {
            int idx = i * nb_colonne + j;
            // Voisin de droite
            if (j + 1 < nb_colonne) {
                aretes[nombre_aretes][0] = idx;
                aretes[nombre_aretes][1] = idx + 1;
                nombre_aretes++;
            }
            // Voisin du bas
            if (i + 1 < nb_ligne) {
                aretes[nombre_aretes][0] = idx;
                aretes[nombre_aretes][1] = idx + nb_colonne;
                nombre_aretes++;
            }
        }
    }
    // Remplir le reste avec -1
    for (int i = nombre_aretes; i < NOMBRE_NOEUDS_MAX; i++) {
        aretes[i][0] = -1;
        aretes[i][1] = -1;
    }
    
    genenerer_fichier_dot("test");


}
void remplir_aleatoire(int nbr_noeuds,int nbre_aretes) {
    if (nbr_noeuds < 0 || nbr_noeuds >= NOMBRE_NOEUDS_MAX) {
        fprintf(stderr, "Nombre de noeuds hors limites\n");
        exit(EXIT_FAILURE);
    }
    nombre_noeuds = nbr_noeuds;
    nombre_aretes = nbre_aretes;
    int a;
    int b;
    
    for (int i = 0; i < nbre_aretes; i++) {
        a=rand() % nbr_noeuds;
        b=rand() % nbr_noeuds;
        if (a == b) {
            b = (b + 1) % nbr_noeuds; // Assurer que a et b sont différents
    }
        aretes[i][0] = a; // Valeur aléatoire pour le premier noeud
        aretes[i][1] = b; // Valeur aléatoire pour le second noeud
    }
    genenerer_fichier_dot("exemple_graphe_aléatoire.dot");
}

void genenerer_fichier_dot(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier DOT\n");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "graph G {\n");

    // Afficher tous les noeuds
    for (int i = 0; i < nombre_noeuds; i++) {
        fprintf(f, "    %d;\n", i);
    }

    // Afficher les arêtes
    for (int i = 0; i < nombre_noeuds; i++) {
        if (aretes[i][0] != -1 && aretes[i][1] != -1) {
            fprintf(f, "    %d -- %d;\n", aretes[i][0], aretes[i][1]);
        }
    }

    fprintf(f, "}\n");
    fclose(f);
}

void extraire_composantes_connexes_noeud_arete() {
    init_partition_forest(nombre_noeuds);
    for (int i = 0; i < nombre_noeuds; i++) {
        if (aretes[i][0] != -1 && aretes[i][1] != -1) {
            int x = recuperer_classe_forest(aretes[i][0]);
            int y = recuperer_classe_forest(aretes[i][1]);
            if (x != y) {
                fusion_forest(x, y);
            }
        }
    }
}

int nombre_classe_noeud_arete() {
    int count = 0;
    for (int i = 0; i < nombre_noeuds; i++) {
        if (parent[i] == i) { // Seuls les représentants de classe pointent vers eux-mêmes
            count++;
        }
    }
    return count;
}

void creer_graph_partition_noeud_arrete(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier DOT\n");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "graph G {\n");

    // Afficher les clusters pour chaque partition
    // On suppose que la partition a déjà été calculée (parent[] rempli)
    int classes[NOMBRE_NOEUDS_MAX];
    int nb_classes = 0;

    // Trouver tous les représentants de classe
    for (int i = 0; i < nombre_noeuds; i++) {
        int rep = recuperer_classe_forest(i);
        int existe = 0;
        for (int j = 0; j < nb_classes; j++) {
            if (classes[j] == rep) {
                existe = 1;
                break;
            }
        }
        if (!existe) {
            classes[nb_classes++] = rep;
        }
    }

    // Pour chaque classe, créer un sous-graphe (cluster)
    for (int c = 0; c < nb_classes; c++) {
        fprintf(f, "    subgraph cluster_%d {\n", c);
        fprintf(f, "        label = \"Classe %d\";\n", c);
        for (int i = 0; i < nombre_noeuds; i++) {
            if (recuperer_classe_forest(i) == classes[c]) {
                fprintf(f, "        %d;\n", i);
            }
        }
        fprintf(f, "    }\n");
    }

    // Afficher les arêtes
    for (int i = 0; i < nombre_noeuds; i++) {
        if (aretes[i][0] != -1 && aretes[i][1] != -1) {
            fprintf(f, "    %d -- %d;\n", aretes[i][0], aretes[i][1]);
        }
    }

    fprintf(f, "}\n");
    fclose(f);
}
