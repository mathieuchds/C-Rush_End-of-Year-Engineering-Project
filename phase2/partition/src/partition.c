#include "partition.h"

int ensemble[NOMBRE_ELEM_MAX];
int taille_partition;

int parent[NOMBRE_ELEM_MAX];
int hauteur[NOMBRE_ELEM_MAX];
int taille_partition_forest;


void init_partition_marqueurs(int taille) {
    if (taille <= 0 || taille > NOMBRE_ELEM_MAX) {
        fprintf(stderr, "Taille de partition invalide\n");
        exit(EXIT_FAILURE);
    }
    taille_partition = taille;
    for (int i = 0; i < taille; i++) {
        ensemble[i] = i; // Chaque élément est son propre représentant
    }
}



int recuperer_classe_marqueurs(int x) {
    if (x < 0 || x >= taille_partition) {
        fprintf(stderr, "Index hors limites\n");
        exit(EXIT_FAILURE);
    }
    return ensemble[x];
}

void fusion_marqueurs(int x, int y) {
    if (x < 0 || x >= taille_partition || y < 0 || y >= taille_partition) {
        fprintf(stderr, "Index hors limites\n");
        exit(EXIT_FAILURE);
    }
    int racine_x = recuperer_classe_marqueurs(x);
    int racine_y = recuperer_classe_marqueurs(y);
    for (int i = 0; i < taille_partition; i++) {
        if (ensemble[i] == racine_y) {
            ensemble[i] = racine_x;
        }
    }
}

list * lister_classe_marqueurs(int classe) {
    if (classe < 0 || classe >= taille_partition) {
        fprintf(stderr, "Index hors limites\n");
        exit(EXIT_FAILURE);
    }
    list * l = listCreate();
    for (int i = 0; i < taille_partition; i++) {
        if (recuperer_classe_marqueurs(i) == classe) {
            l = listAdd(l, i);
        }
    }
    return l;
}

list ** lister_partition_marqueurs() {
    list ** l_classes = (list **)malloc(taille_partition * sizeof(list *));
    if (l_classes == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille_partition; i++) {
        l_classes[i] = NULL;
    }
    for (int i = 0; i < taille_partition; i++) {
        int classe = recuperer_classe_marqueurs(i);
        if (l_classes[classe] == NULL) {
            l_classes[classe] = listCreate();
        }
        l_classes[classe] = listAdd(l_classes[classe], i);
    }
    return l_classes;
}



/* implémentation partition arborescence*/

void init_partition_forest(int taille) {
    if (taille <= 0 || taille > NOMBRE_ELEM_MAX) {
        fprintf(stderr, "Taille de partition invalide\n");
        exit(EXIT_FAILURE);
    }
    taille_partition_forest = taille;
    for (int i = 0; i < taille; i++) {
        parent[i] = i; // Chaque élément est son propre parent
        hauteur[i] = 0; // Initialisation des hauteurs à 0
    }
}

int recuperer_classe_forest(int x) {
  
    if (x < 0 || x >= taille_partition_forest) {
        fprintf(stderr, "Index classe hors limites : %d\n",x);
        exit(EXIT_FAILURE);
    }
  
    while (parent[x] != x) {
        x = parent[x];
    }
    return x;

}

void fusion_forest(int x, int y) {
    if (x < 0 || x >= taille_partition_forest || y < 0 || y >= taille_partition_forest) {
        fprintf(stderr, "Index fusion hors limites\n");
        exit(EXIT_FAILURE);
    }
    int racine_x = recuperer_classe_forest(x);
    int racine_y = recuperer_classe_forest(y);

    if (racine_x == racine_y) {
        return; // déjà dans la même classe
    }

    if (hauteur[racine_x] > hauteur[racine_y]) {
        parent[racine_y] = racine_x;
        hauteur[racine_y] = 0;
    } else if (hauteur[racine_x] < hauteur[racine_y]) {
        parent[racine_x] = racine_y;
        hauteur[racine_x] = 0;
    } else {
        parent[racine_y] = racine_x;
        hauteur[racine_x]++;

    }
    return;
}

list * lister_classe_forest(int classe) {
    if (classe < 0 || classe >= taille_partition_forest) {
        fprintf(stderr, "Index hors limites\n");
        exit(EXIT_FAILURE);
    }
    list * l = listCreate();
    for (int i = 0; i < taille_partition_forest; i++) {
        if (hauteur[i] != 0) {     //Plus tard regarder si on a le temps (tableau dynamique de tableau dynamique qui poinente vers la fin ?)
            l = listAdd(l, i);
        }
    } 
    return l;
}


list ** lister_partition_forest() {
    list ** l_classes = (list **)malloc(taille_partition_forest * sizeof(list *));
    if (l_classes == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille_partition_forest; i++) {
        l_classes[i] = NULL;
    }
    for (int i = 0; i < taille_partition_forest; i++) {
        int classe = recuperer_classe_forest(i);
        if (l_classes[classe] == NULL) {
            l_classes[classe] = listCreate();
        }
        l_classes[classe] = listAdd(l_classes[classe], i);
    }
    return l_classes;
}



