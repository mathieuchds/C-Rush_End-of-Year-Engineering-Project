#include "matrice_adjacence.h"

matrice_adjacence creer_matrice_adjacence(int taille) {
    matrice_adjacence m;
    m.taille = taille;
    srand( time( NULL ) );
    m.matrice = (int **)malloc(taille * sizeof(int *));
    if (m.matrice == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la matrice\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille; i++) {
        m.matrice[i] = (int *)calloc(taille, sizeof(int));
        if (m.matrice[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la ligne %d de la matrice\n", i);
            exit(EXIT_FAILURE);
        }
    }
    // Initialisation de la matrice avec moins de liens (probabilité plus faible)
    for (int i = 0; i < taille; i++) {
        for (int j = i+1; j < taille; j++) {
            if (i != j) { // Pas d'arête sur la diagonale
                if ((rand() % 100) < 20) { // 20% de chance d'avoir un lien
                    m.matrice[i][j] = 1;
                    m.matrice[j][i] = 1;
                }
            } 
        }
    }
    return m;
}

//Fonction pour affichage de la matrice d'adjacence avec graphviz
void generer_fichier_dot_m(matrice_adjacence m, const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier DOT\n");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "graph G {\n");

    // Afficher tous les sommets, même isolés
    for (int i = 0; i < m.taille; i++) {
        fprintf(f, "    %d;\n", i);
    }

    // Afficher les arêtes
    for (int i = 0; i < m.taille; i++) {
        for (int j = i + 1; j < m.taille; j++) { // i < j pour éviter les doublons
            if (m.matrice[i][j]) {
                fprintf(f, "    %d -- %d;\n", i, j); // "--" pour graphe non orienté
            }
        }
    }

    fprintf(f, "}\n");
    fclose(f);
}

void extraire_composantes_connexes(matrice_adjacence m){
    init_partition_forest(m.taille);
    for (int i = 0; i < m.taille; i++) {
        for (int j = i + 1; j < m.taille; j++){
            if (m.matrice[i][j]) {
                if (recuperer_classe_forest(i) != recuperer_classe_forest(j)) {
                    // Fusion des classes
                    fusion_forest(i, j);
                }
            }
        }   
    }
}

int nombre_classe() {
    int count = 0;
    for (int i = 0; i < taille_partition_forest; i++) {
        if (parent[i] == i) { // Seuls les représentants de classe pointent vers eux-mêmes
            count++;
        }
    }
    return count;
}
void creer_graph_partition(const char *nom_fichier, matrice_adjacence m) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier DOT\n");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "graph G {\n");

    // On crée un cluster (sous-graphe) pour chaque classe
    int *classe_de_sommet = malloc(taille_partition_forest * sizeof(int));
    int nb_classes = 0;

    // Associer chaque sommet à sa classe et compter les classes distinctes
    for (int i = 0; i < taille_partition_forest; i++) {
        classe_de_sommet[i] = recuperer_classe_forest(i);
    }

    // Trouver toutes les classes distinctes
    int *classes_uniques = malloc(taille_partition_forest * sizeof(int));
    for (int i = 0; i < taille_partition_forest; i++) {
        int deja_vu = 0;
        for (int j = 0; j < nb_classes; j++) {
            if (classes_uniques[j] == classe_de_sommet[i]) {
                deja_vu = 1;
                break;
            }
        }
        if (!deja_vu) {
            classes_uniques[nb_classes++] = classe_de_sommet[i];
        }
    }

    // Créer un cluster pour chaque classe
    for (int c = 0; c < nb_classes; c++) {
        fprintf(f, "    subgraph cluster_%d {\n", c);
        fprintf(f, "        label = \"Classe %d\";\n", c);
        for (int i = 0; i < taille_partition_forest; i++) {
            if (classe_de_sommet[i] == classes_uniques[c]) {
                fprintf(f, "        %d;\n", i);
            }
        }
        fprintf(f, "    }\n");
    }

    // Afficher toutes les arêtes de la matrice
    for (int i = 0; i < m.taille; i++) {
        for (int j = i + 1; j < m.taille; j++) {
            if (m.matrice[i][j]) {
                fprintf(f, "    %d -- %d;\n", i, j);
            }
        }
    }

    fprintf(f, "}\n");
    fclose(f);
    free(classe_de_sommet);
    free(classes_uniques);
}


