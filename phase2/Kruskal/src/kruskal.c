#include "noeud_arrete.h"
#include "partition.h"
#include "kruskal.h"

int aretes_A[(P_MAX-1)*N_MAX+P_MAX*(N_MAX-1)][2]; // Tableau pour stocker les arêtes
int nb_aretes_A = 0;



void algorithme_kruskal(int nbr_ligne_local,int nbr_colonne_local) {
    srand(time(NULL));
    init_noeud_arrete();
    remplir_graphe_labyrinthe(nbr_ligne_local,nbr_colonne_local);
    melange_Fisher_Yates(nombre_aretes);
 
    init_partition_forest(nombre_noeuds);

    nb_aretes_A = 0;
    for (int i = 0; i < nombre_aretes ; i++) {
        int u = aretes[i][0];
        int v = aretes[i][1];
       
        int x = recuperer_classe_forest(u);
        int y = recuperer_classe_forest(v);
        if (x != y) {
            fusion_forest(u, v);
            aretes_A[nb_aretes_A][0] = u;
            aretes_A[nb_aretes_A][1] = v;
            nb_aretes_A++;
        }
    }
  
}
void algorithme_kruskal_densite( int nbr_ligne_local,int nbr_colonne_local,int p) {
    srand(time(NULL));
    init_noeud_arrete();

    remplir_graphe_labyrinthe(nbr_ligne_local,nbr_colonne_local);
  
    melange_Fisher_Yates(nombre_aretes);
   
    init_partition_forest(nombre_noeuds);

    nb_aretes_A = 0;
    for (int i = 0; i < nombre_aretes ; i++) {
        int u = aretes[i][0];
        int v = aretes[i][1];
        
        int x = recuperer_classe_forest(u);
        int y = recuperer_classe_forest(v);
        if (x != y) {
            fusion_forest(u, v);
            aretes_A[nb_aretes_A][0] = u;
            aretes_A[nb_aretes_A][1] = v;
            nb_aretes_A++;
        }
        else if (rand() % 100 < p) { // Ajout d'une arête avec une probabilité p
            aretes_A[nb_aretes_A][0] = u;
            aretes_A[nb_aretes_A][1] = v;
            nb_aretes_A++;
        }
        
    }
    generer_fichier_dot_A("test.dot");

   
}

void melange_Fisher_Yates(int nombre_aretes) {
    for (int i = nombre_aretes - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp[2];
        temp[0] = aretes[i][0];
        temp[1] = aretes[i][1];
        aretes[i][0] = aretes[j][0];
        aretes[i][1] = aretes[j][1];
        aretes[j][0] = temp[0];
        aretes[j][1] = temp[1];
    
    }
}
void generer_fichier_dot_A(const char *nom_fichier) {
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

    // Afficher les arêtes de l'arbre couvrant
    for (int i = 0; i < nb_aretes_A; i++) {
        if (aretes_A[i][0] != -1 && aretes_A[i][1] != -1) {
            fprintf(f, "    %d -- %d;\n", aretes_A[i][0], aretes_A[i][1]);
        }
    }

    fprintf(f, "}\n");
    fclose(f);
}
/*
void generer_fichier_maze(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "%d\n", nombre_noeuds);
    fprintf(f, "%d\n", nb_aretes_A );
    fprintf(f,"%d\n",nb_ligne);
    fprintf(f,"%d\n",nb_colonne);
    // Afficher les arêtes de l'arbre couvrant
    for (int i = 0; i < nb_aretes_A; i++) {
        if (aretes_A[i][0] != -1 && aretes_A[i][1] != -1) {
            fprintf(f, "%d %d\n", aretes_A[i][0], aretes_A[i][1]); 
        }
    }
    fprintf(f, "F\n");
    fclose(f);
}
    */