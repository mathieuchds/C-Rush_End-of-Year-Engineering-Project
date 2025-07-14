#include "Moteur_labyrinthe.h"

// Initialise les points d'intérêt : spawn_player, spawn_monster, exit
// Aucun ne doit être sur un bouton, et spawn_player/monster doivent être à une distance suffisante
void init_points_interet(labyrinthe *laby, point_interet *pi) {
    int n = laby->nb_ligne * laby->nb_colonne;
    int pos_player = -1, pos_monster = -1, pos_exit = -1;
    int essais = 0, max_essais = 1000;
    int trouve = 0;

    // Choix d'une distance minimale en fonction de la taille du labyrinthe
    int min_distance = (laby->nb_ligne + laby->nb_colonne) / 2;
    if (min_distance < 3) min_distance = 3;

    while (essais < max_essais && !trouve) {
        essais++;
        int i_player = rand() % n;
        int i_monster = rand() % n;
        int i_exit = rand() % n;

        // Vérifie que les cases ne sont pas sur un bouton et sont différentes
        if (laby->boutons[i_player] == 0 &&
            laby->boutons[i_monster] == 0 &&
            laby->boutons[i_exit] == 0 &&
            i_player != i_monster &&
            i_player != i_exit &&
            i_monster != i_exit) {

            int pi_player = i_player / laby->nb_colonne;
            int pj_player = i_player % laby->nb_colonne;
            int pi_monster = i_monster / laby->nb_colonne;
            int pj_monster = i_monster % laby->nb_colonne;
            int dist = abs(pi_player - pi_monster) + abs(pj_player - pj_monster);

            if (dist >= min_distance) {
                pos_player = i_player;
                pos_monster = i_monster;
                pos_exit = i_exit;
                trouve = 1;
            }
        }
    }

    if (!trouve) {
        pi->spawn_player = pi->spawn_monster = pi->exit = -1;
    } else {
        pi->spawn_player = pos_player;
        pi->spawn_monster = pos_monster;
        pi->exit = pos_exit;
    }
}

vision_monstre * init_vision_monstre(labyrinthe *lab) {
    vision_monstre *vm = malloc(sizeof(vision_monstre));
    vm->lab = lab;
    vm->memoire = malloc(lab->nb_ligne * lab->nb_colonne * sizeof(long));
    for (size_t i = 0; i < (size_t)(lab->nb_ligne * lab->nb_colonne); i++) {
        vm->memoire[i] = -1; // Initialisation de la mémoire à -1
    }
    return vm;
}

#define MEMOIRE_EXPIRATION 40// Nombre de frames avant expiration

void update_case_memoire(vision_monstre *vm, int case_index, long unsigned int valeur) {
    vm->memoire[case_index] = valeur; // Met à jour la mémoire avec la valeur actuelle //
}

void verifie_case_memoire(vision_monstre *vm, int case_index, long unsigned int valeur) {
    if (vm->memoire[case_index] != -1 && (valeur - vm->memoire[case_index]) > MEMOIRE_EXPIRATION) {
        vm->lab->construction[case_index] = 0;
        vm->lab->poids_cases[case_index] = 0;
        vm->memoire[case_index] = -1;
    }
    // Sinon, ne rien faire
}
void free_vision_monstre(vision_monstre *vm) {
    if (vm) {
        if (vm->memoire) free(vm->memoire);
        free(vm);
    }
}

labyrinthe *init_labyrinthe( int nb_ligne,int nb_colonne,int nb_boutons) {
    labyrinthe *laby = malloc(sizeof(labyrinthe));
    laby->nb_colonne = nb_colonne;
    laby->nb_ligne = nb_ligne;
    laby->nb_boutons = nb_boutons;
    laby->construction = malloc(nb_colonne * nb_ligne * sizeof(int));
    for (int i = 0; i < nb_colonne * nb_ligne; i++) {
        laby->construction[i] = 15;
    }
    laby->poids_cases= malloc(nb_colonne * nb_ligne * sizeof(int));
    for (int i = 0; i < nb_colonne * nb_ligne; i++) {
        laby->poids_cases[i]=1;
    }
    laby->boutons = malloc(nb_colonne*nb_ligne * sizeof(int));
    for (int i = 0; i < nb_colonne*nb_ligne; i++) {
        laby->boutons[i] = 0;
    }
    return laby;
}
// Génère des positions de boutons relativement écartées sur la carte du labyrinthe.
// Les boutons sont placés de façon à ce que la distance de Manhattan entre eux soit suffisante.
// Met à 1 la case correspondante dans laby->boutons si un bouton est présent.
void generer_boutons_ecartes(labyrinthe *laby) {
    if (!laby || laby->nb_boutons <= 0) return;
    int max_essais = 1000; // Nombre maximal d'essais pour placer chaque bouton
    int essais = 0;
    int min_dist = (laby->nb_ligne + laby->nb_colonne) / 3;
    if (min_dist < 2) min_dist = 2;

    // Remet à zéro le tableau des boutons
    for (int i = 0; i < laby->nb_ligne * laby->nb_colonne; i++) {
        laby->boutons[i] = 0;
    }

    int *positions = malloc(laby->nb_boutons * sizeof(int)); // Pour vérifier les distances

    for (int b = 0; b < laby->nb_boutons; b++) {
        int ok = 0;
        while (!ok && essais < max_essais) {
            essais++;
            int i = rand() % laby->nb_ligne;
            int j = rand() % laby->nb_colonne;
            int pos = i * laby->nb_colonne + j;
            ok = 1;
            // Vérifie la distance avec tous les boutons déjà placés
            for (int k = 0; k < b; k++) {
                int pi = positions[k] / laby->nb_colonne;
                int pj = positions[k] % laby->nb_colonne;
                int dist = abs(i - pi) + abs(j - pj);
                if (dist < min_dist) {
                    ok = 0;
                    break;
                }
            }
            if (ok && laby->boutons[pos] == 0) {
                positions[b] = pos;
                laby->boutons[pos] = 1;
            }
        }
        if (essais >= max_essais) {
            // Si trop d'essais, place le bouton aléatoirement sans doublon
            int unique = 0;
            int pos;
            while (!unique) {
                int i = rand() % laby->nb_ligne;
                int j = rand() % laby->nb_colonne;
                pos = i * laby->nb_colonne + j;
                unique = (laby->boutons[pos] == 0);
            }
            positions[b] = pos;
            laby->boutons[pos] = 1;
        }
    }
    free(positions);
}
void affiche_boutons(labyrinthe *laby) {
    if (!laby || !laby->boutons) return;
    printf("Positions des boutons dans le labyrinthe :\n");
    int bouton_num = 1;
    for (int i = 0; i < laby->nb_ligne; i++) {
        for (int j = 0; j < laby->nb_colonne; j++) {
            int idx = i * laby->nb_colonne + j;
            if (laby->boutons[idx]) {
                printf("  Bouton %d : ligne %d, colonne %d\n", bouton_num, i, j);
                bouton_num++;
                if (bouton_num > laby->nb_boutons) return;
            }
        }
    }
}



void poids_aleatoire(labyrinthe * lab){
    srand(time(NULL));
    for (int i = 0; i < lab->nb_ligne * lab->nb_colonne; i++) {
        lab->poids_cases[i] = 1 + rand() % 10; // Poids aléatoire entre 1 et 10
    }
}

//A implémenter, création de "biome " passage d'un biome à un autre avec une probabilité
// il y a 5 valeurs de poids possibles, 1,2,4,6,8 
// Probas de passage entre biomes (somme pour chaque biome = 1.0)
// Biomes : Glace(1), Eau(2), Classique(4), Buisson(6), SablesMouvants(8)
// Proba de rester dans le biome = 1 - somme des probas de passage vers autres biomes
// Définition des biomes et de leurs poids
#define BIOME_GLACE      1
#define BIOME_EAU        2
#define BIOME_CLASSIQUE  4
#define BIOME_BUISSON    6
#define BIOME_SABLES     8

static int biomes[] = {BIOME_GLACE, BIOME_EAU, BIOME_CLASSIQUE, BIOME_BUISSON, BIOME_SABLES};
static int nb_biomes = 5;




void poids_classique(labyrinthe *lab) {
    // Remplit le tableau des poids avec le biome classique
    for (int i = 0; i < lab->nb_ligne * lab->nb_colonne; i++) {
        lab->poids_cases[i] = BIOME_CLASSIQUE;
    }
}

// Version centrée : pas de malloc, propagation simple à partir de sources fixes
void poids_logique_centrique(labyrinthe *lab) {
    // Tout classique au départ
    for (int i = 0; i < lab->nb_ligne * lab->nb_colonne; i++)
        lab->poids_cases[i] = BIOME_CLASSIQUE;

    srand(time(NULL));
    int nb_sources = 4 + rand() % 4; // entre 4 et 8 sources
    int *src_i = malloc(nb_sources * sizeof(int));
    int *src_j = malloc(nb_sources * sizeof(int));
    int *src_biome = malloc(nb_sources * sizeof(int));

    for (int s = 0; s < nb_sources; s++) {
        int i, j, biome;
        int unique;
        do {
            i = rand() % lab->nb_ligne;
            j = rand() % lab->nb_colonne;
            biome = biomes[rand() % nb_biomes];
            unique = 1;
            if (biome == BIOME_CLASSIQUE) { unique = 0; continue; }
            for (int k = 0; k < s; k++)
                if (src_i[k] == i && src_j[k] == j) unique = 0;
        } while (!unique);
        src_i[s] = i;
        src_j[s] = j;
        src_biome[s] = biome;
        lab->poids_cases[i * lab->nb_colonne + j] = biome;
    }

    // Propagation : BFS pour chaque biome source, avec une taille de "zone" aléatoire (plus petite)
    int *visited = calloc(lab->nb_ligne * lab->nb_colonne, sizeof(int));
    for (int s = 0; s < nb_sources; s++) {
        int zone_size = (lab->nb_ligne * lab->nb_colonne) / (nb_sources * 3) + rand() % (lab->nb_ligne * lab->nb_colonne / (nb_sources * 2));
        int *queue_i = malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        int *queue_j = malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        int front = 0, back = 0;
        queue_i[back] = src_i[s];
        queue_j[back] = src_j[s];
        back++;
        visited[src_i[s] * lab->nb_colonne + src_j[s]] = 1;
        int count = 1;

        while (front < back && count < zone_size) {
            int ci = queue_i[front];
            int cj = queue_j[front];
            front++;
            int idx = ci * lab->nb_colonne + cj;
            // Voisins accessibles sans mur
            int directions[4][3] = {
                { -1, 0, NORD }, // nord
                { 1, 0, SUD },   // sud
                { 0, -1, OUEST },// ouest
                { 0, 1, EST }    // est
            };
            for (int v = 0; v < 4; v++) {
                int ni = ci + directions[v][0];
                int nj = cj + directions[v][1];
                int dir_mask = directions[v][2];
                if (ni >= 0 && ni < lab->nb_ligne && nj >= 0 && nj < lab->nb_colonne) {
                    int nidx = ni * lab->nb_colonne + nj;
                    // Vérifie qu'il n'y a pas de mur entre (ci,cj) et (ni,nj)
                    if (!(lab->construction[idx] & dir_mask)) {
                        if (!visited[nidx] && lab->poids_cases[nidx] == BIOME_CLASSIQUE) {
                            // Augmente la probabilité de propagation (par exemple 0.9 au lieu de 0.6)
                            if ((double)rand() / RAND_MAX < 0.9) {
                                // Vérifier si un voisin non-classique existe déjà (autre biome)
                                int contact_autre_biome = 0;
                                for (int vv = 0; vv < 4; vv++) {
                                    int nni = ni + directions[vv][0];
                                    int nnj = nj + directions[vv][1];
                                    if (nni >= 0 && nni < lab->nb_ligne && nnj >= 0 && nnj < lab->nb_colonne) {
                                        int nnidx = nni * lab->nb_colonne + nnj;
                                        int val = lab->poids_cases[nnidx];
                                        if (val != BIOME_CLASSIQUE && val != src_biome[s]) {
                                            contact_autre_biome = 1;
                                            break;
                                        }
                                    }
                                }
                                if (contact_autre_biome) {
                                    lab->poids_cases[nidx] = BIOME_CLASSIQUE;
                                } else {
                                    lab->poids_cases[nidx] = src_biome[s];
                                    queue_i[back] = ni;
                                    queue_j[back] = nj;
                                    back++;
                                    count++;
                                }
                                visited[nidx] = 1;
                                if (count >= zone_size) break;
                            }
                        }
                    }
                }
            }
        }
        free(queue_i);
        free(queue_j);
    }
    free(visited);
    free(src_i);
    free(src_j);
    free(src_biome);

    // Parcours final pour éviter les cases isolées
    for (int i = 0; i < lab->nb_ligne; i++) {
        for (int j = 0; j < lab->nb_colonne; j++) {
            int biome = lab->poids_cases[i * lab->nb_colonne + j];
            if (biome == BIOME_CLASSIQUE)
                continue;
            int voisin_meme_biome = 0;
            int directions[4][3] = {
                { -1, 0, NORD }, // nord
                { 1, 0, SUD },   // sud
                { 0, -1, OUEST },// ouest
                { 0, 1, EST }    // est
            };
            for (int v = 0; v < 4; v++) {
                int ni = i + directions[v][0];
                int nj = j + directions[v][1];
                int dir_mask = directions[v][2];
                if (ni >= 0 && ni < lab->nb_ligne && nj >= 0 && nj < lab->nb_colonne) {
                    int idx = i * lab->nb_colonne + j;
                    int nidx = ni * lab->nb_colonne + nj;
                    // Vérifie qu'il n'y a pas de mur entre (i,j) et (ni,nj)
                    if (!(lab->construction[idx] & dir_mask)) {
                        if (lab->poids_cases[nidx] == biome) {
                            voisin_meme_biome = 1;
                            break;
                        }
                    }
                }
            }
            if (!voisin_meme_biome)
                lab->poids_cases[i * lab->nb_colonne + j] = BIOME_CLASSIQUE;
        }
    }
}
void free_labyrinthe(labyrinthe *laby) {
    if (laby) {
        free(laby->construction);
        free(laby->poids_cases);
        free(laby);
    }
}


void calcul_construction(labyrinthe *laby) {
    int depart, arrive;

    for (int i = 0; i < nb_aretes_A; i++) {
        depart = aretes_A[i][0];
        arrive = aretes_A[i][1];
        if (depart == arrive - 1) {
            laby->construction[depart] -= 4;
            laby->construction[arrive] -= 1;
        }
        if (depart == arrive - laby->nb_colonne) {
            laby->construction[depart] -= 8;
            laby->construction[arrive] -= 2;
        }
    }
}

void generer_fichier_maze(char *nom_fichier, labyrinthe *laby) {
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    fprintf(f, "%d\n", laby->nb_ligne);
    fprintf(f, "%d\n", laby->nb_colonne);
    for (int i = 0; i < laby->nb_ligne; i++) {
        for (int j = 0; j < laby->nb_colonne; j++) {
            fprintf(f, "%d", laby->construction[i * laby->nb_colonne + j]);
            if (j < laby->nb_colonne - 1)
                fprintf(f, " ");
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

labyrinthe *lire_fichier_maze(char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    int nb_ligne, nb_colonne;
    if (fscanf(f, "%d", &nb_ligne) != 1 || fscanf(f, "%d", &nb_colonne) != 1) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    labyrinthe *laby = init_labyrinthe( nb_ligne,nb_colonne,4);
    for (int i = 0; i < nb_ligne; i++) {
        for (int j = 0; j < nb_colonne; j++) {
            if (fscanf(f, "%d", &laby->construction[i * nb_colonne + j]) != 1) {
                fprintf(stderr, "Erreur lors de la lecture du fichier maze\n");
                free_labyrinthe(laby);
                fclose(f);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(f);
    return laby;
}

void affiche_tab_construction(labyrinthe *laby) {
    for (int i = 0; i < laby->nb_ligne; i++) {
        for (int j = 0; j < laby->nb_colonne; j++) {
            printf("%d ", laby->construction[i * laby->nb_colonne + j]);
        }
        printf("\n");
    }
}
void affiche_tab_poids(labyrinthe *laby) {
    for (int i = 0; i < laby->nb_ligne; i++) {
        for (int j = 0; j < laby->nb_colonne; j++) {
            printf("%d ", laby->poids_cases[i * laby->nb_colonne + j]);
        }
        printf("\n");
    }
}

void labyrinthe_textuel(labyrinthe *laby) {
    // Affichage de la première ligne (murs du haut)
    printf("+");
    for (int j = 0; j < laby->nb_colonne; j++) {
        if (laby->construction[j] & NORD)
            printf("---+");
        else
            printf("   +");
    }
    printf("\n");

    for (int i = 0; i < laby->nb_ligne; i++) {
        // Affichage des murs de gauche et des cases
        for (int j = 0; j < laby->nb_colonne; j++) {
            if (laby->construction[j + i * laby->nb_colonne] & OUEST)
                printf("|");
            else
                printf(" ");
            printf("   ");
        }
        // Mur de droite de la dernière case de la ligne
        if (laby->construction[(i + 1) * laby->nb_colonne - 1] & EST)
            printf("|");
        else
            printf(" ");
        printf("\n");

        // Affichage des murs du bas
        printf("+");
        for (int j = 0; j < laby->nb_colonne; j++) {
            if (laby->construction[j + i * laby->nb_colonne] & SUD)
                printf("---+");
            else
                printf("   +");
        }
        printf("\n");
    }
}

