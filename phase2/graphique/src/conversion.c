
#include "conversion.h"


void generer_fichier_maze2(const char *nom_fichier, int *construction_mur, int nb_ligne, int nb_colonne) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "%d\n", nb_ligne);
    fprintf(f, "%d\n", nb_colonne);

    // Écriture de la structure construction_mur ligne par ligne
    for (int i = 0; i < nb_ligne; i++) {
        for (int j = 0; j < nb_colonne; j++) {
            fprintf(f, "%d", construction_mur[i * nb_colonne + j]);
            if (j < nb_colonne - 1)
                fprintf(f, " ");
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

int* lire_fichier_maze2(const char *nom_fichier, int *nb_ligne, int *nb_colonne) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if (fscanf(f, "%d", nb_ligne) != 1 || fscanf(f, "%d", nb_colonne) != 1) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    int taille = (*nb_ligne) * (*nb_colonne);
    int *construction_mur = (int*)malloc(taille * sizeof(int));
    if (!construction_mur) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *nb_ligne; i++) {
        for (int j = 0; j < *nb_colonne; j++) {
            if (fscanf(f, "%d", &construction_mur[i * (*nb_colonne) + j]) != 1) {
                fprintf(stderr, "Erreur lors de la lecture du fichier maze\n");
                free(construction_mur);
                fclose(f);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(f);
    return construction_mur;
}
