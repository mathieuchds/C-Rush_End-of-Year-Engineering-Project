#include "partition.h"

int test_partition() {
    // Test de la partition avec marqueurs
    printf("Test de la partition avec marqueurs\n");
    init_partition_marqueurs(11);
  
    // Génération de la partition souhaitée
    // Indices: 0 1 2 3 4 5 6 7 8 9 10
    // Valeurs: 0 0 3 3 5 5 5 5 5 5 3
    fusion_marqueurs( 0, 1);

    fusion_marqueurs(3, 2);
    fusion_marqueurs(3, 10);


    fusion_marqueurs(5, 4);
    fusion_marqueurs(5, 6);
    fusion_marqueurs(6, 7);
    fusion_marqueurs(7, 8);
    fusion_marqueurs(8, 9);
    list ** classes = lister_partition_marqueurs();
    for(int i = 0; i < taille_partition; i++){
        printf("Classe %d: ", i);
        listDisplay(classes[i]);
        printf("\n");
        free(classes[i]); // Libération de la mémoire allouée pour chaque liste
    }
    printf("test de la partition avec marqueurs terminé\n");
    init_partition_forest(11);
    // Génération de la partition souhaitée
    fusion_forest(0, 1);
    fusion_forest(2, 3);
    fusion_forest(10, 3);
    fusion_forest(5, 9);
    fusion_forest(4, 6);
    fusion_forest(8, 7);
    fusion_forest(9, 7);
    fusion_forest(6, 8);
    classes = lister_partition_forest();
    for(int i = 0; i < taille_partition_forest; i++){
        printf("Classe %d: ", i);
        listDisplay(classes[i]);
        printf("\n");
        free(classes[i]); // Libération de la mémoire allouée pour chaque liste
    }
    free(classes); // Libération de la mémoire allouée pour le tableau de listes
  
    
    return 0;
}