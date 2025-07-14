
#include "calcul_chemin.h"






S* init_S(int nombre_noeuds) {
    S* s = (S*)malloc(sizeof(S));
    s->deja_vu = (int*)malloc(nombre_noeuds * sizeof(int));
    for (int i = 0; i < nombre_noeuds; i++) s->deja_vu[i] = -1;
    return s;
}


S* BFS(labyrinthe* lab, int origine) {
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    file* F = create_file(nombre_noeuds);
    S* s = init_S(nombre_noeuds);

    enfiler(F, origine);
    s->deja_vu[origine] = 0; // distance 0 
    while (! file_vide(F)) {
        int noeud = defiler(F);
        int dist = s->deja_vu[noeud];

        // EST
        if (!(lab->construction[noeud] & EST)) {
            int voisin = noeud + 1;
            if ((voisin % lab->nb_colonne != 0) && s->deja_vu[voisin] == -1) {
                s->deja_vu[voisin] = dist + 1;
                enfiler(F, voisin);
            }
        }
        // OUEST
        if (!(lab->construction[noeud] & OUEST)) {
            int voisin = noeud - 1;
            if ((noeud % lab->nb_colonne != 0) && s->deja_vu[voisin] == -1) {
                s->deja_vu[voisin] = dist + 1;
                enfiler(F, voisin);
            }
        }
        // NORD
        if (!(lab->construction[noeud] & NORD)) {
            int voisin = noeud - lab->nb_colonne;
            if (voisin >= 0 && s->deja_vu[voisin] == -1) {
                s->deja_vu[voisin] = dist + 1;
                enfiler(F, voisin);
            }
        }
        // SUD
        if (!(lab->construction[noeud] & SUD)) {
            int voisin = noeud + lab->nb_colonne;
            if (voisin < nombre_noeuds && s->deja_vu[voisin] == -1) {
                s->deja_vu[voisin] = dist + 1;
                enfiler(F, voisin);
            }
        }
    }
    free_file(F);
    return s;
}

// Fonction pour retrouver le plus court chemin depuis l'arrivée jusqu'à l'origine
// Retourne un tableau dynamique contenant les noeuds du chemin (de origine à arrive), et place la taille dans *taille_chemin
// Dernière case à -1
chemin_plus_court * chemin_plus_court_bfs(labyrinthe* lab, int origine, int arrive) {
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    S* s = BFS(lab, origine);
    int taille_chemin;
    int distance = s->deja_vu[arrive];
    if (distance == -1) {
        free(s->deja_vu);
        free(s);
        taille_chemin = 0;
        return NULL;
    }

    int* chemin = (int*)malloc((distance + 2) * sizeof(int)); // +1 pour le -1 final
    int courant = arrive;
    int i = distance;
    while (i > 0) {
        chemin[i] = courant;

        // EST
        int voisin = courant + 1;
        if (!(lab->construction[courant] & EST) && (voisin % lab->nb_colonne != 0) && s->deja_vu[voisin] == s->deja_vu[courant] - 1) {
            courant = voisin;
        }
        // OUEST
        else if (!(lab->construction[courant] & OUEST) && (courant % lab->nb_colonne != 0) && (voisin = courant - 1) >= 0 && s->deja_vu[voisin] == s->deja_vu[courant] - 1) {
            courant = voisin;
        }
        // NORD
        else if (!(lab->construction[courant] & NORD) && (voisin = courant - lab->nb_colonne) >= 0 && s->deja_vu[voisin] == s->deja_vu[courant] - 1) {
            courant = voisin;
        }
        // SUD
        else if (!(lab->construction[courant] & SUD) && (voisin = courant + lab->nb_colonne) < nombre_noeuds && s->deja_vu[voisin] == s->deja_vu[courant] - 1) {
            courant = voisin;
        }
        i--;
    }
    chemin[i] = courant;

    chemin[distance + 1] = -1; // Ajoute le -1 à la fin
    taille_chemin = distance + 1;

    // Création du tableau des noeuds visités
    int* noeuds_visites = (int*)calloc(nombre_noeuds, sizeof(int));
    for (int j = 0; j < nombre_noeuds; j++) {
        if (s->deja_vu[j] != -1) noeuds_visites[j] = 1;
    }

    free(s->deja_vu);
    free(s);
    chemin_plus_court * c = malloc(sizeof(chemin_plus_court));
    c->chemin = chemin;
    c->taille_chemin = taille_chemin;
    c->labyrinthe = lab;
    c->noeuds_visites = noeuds_visites;
    c->arrive=arrive;
    c->depart=origine;
    return c;
}

// Fonction pour libérer la mémoire allouée à chemin_plus_court
void free_chemin_plus_court(chemin_plus_court* c) {
    if (c) {
        if (c->chemin) free(c->chemin);
        if (c->noeuds_visites) free(c->noeuds_visites);
        free(c);
    }
}



chemin_plus_court* chemin_plus_court_dijkstra(labyrinthe* lab, int origine, int arrive) {
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    int* dist = (int*)malloc(nombre_noeuds * sizeof(int));
    int* visite = (int*)calloc(nombre_noeuds, sizeof(int));
    int* predecesseur = (int*)malloc(nombre_noeuds * sizeof(int));
    for (int i = 0; i < nombre_noeuds; i++) {
        dist[i] = -1;
        predecesseur[i] = -1;
    }
    dist[origine] = 0;

    tas_b* tas = create_tas(nombre_noeuds);
    ajout_tas(tas, origine, 0);

    int chemin_trouve = 0;
    while (!tas_vide(tas) && !chemin_trouve) {
        int noeud, valeur;
        int poids_arete;
        extraire_min_tas(tas, &noeud, &valeur);
        if (!visite[noeud]) {
            visite[noeud] = 1;
            if (noeud == arrive) {
                chemin_trouve = 1;
            } else {
                // EST
                if (!(lab->construction[noeud] & EST)) {
                    int voisin = noeud + 1;
                    if ((voisin % lab->nb_colonne != 0) && voisin >= 0 && voisin < nombre_noeuds && !visite[voisin]) {
                        poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                        if (dist[voisin] == -1 || dist[noeud] + poids_arete < dist[voisin]) {
                            dist[voisin] = dist[noeud] + poids_arete;
                            predecesseur[voisin] = noeud;
                            ajout_tas(tas, voisin, dist[voisin]);
                        }
                    }
                }
                // OUEST
                if (!(lab->construction[noeud] & OUEST)) {
                    int voisin = noeud - 1;
                    if ((noeud % lab->nb_colonne != 0) && voisin >= 0 && voisin < nombre_noeuds && !visite[voisin]) {
                        poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                        if (dist[voisin] == -1 || dist[noeud] + poids_arete < dist[voisin]) {
                            dist[voisin] = dist[noeud] + poids_arete;
                            predecesseur[voisin] = noeud;
                            ajout_tas(tas, voisin, dist[voisin]);
                        }
                    }
                }
                // NORD
                if (!(lab->construction[noeud] & NORD)) {
                    int voisin = noeud - lab->nb_colonne;
                    if (voisin >= 0 && voisin < nombre_noeuds && !visite[voisin]) {
                        poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                        if (dist[voisin] == -1 || dist[noeud] + poids_arete < dist[voisin]) {
                            dist[voisin] = dist[noeud] + poids_arete;
                            predecesseur[voisin] = noeud;
                            ajout_tas(tas, voisin, dist[voisin]);
                        }
                    }
                }
                // SUD
                if (!(lab->construction[noeud] & SUD)) {
                    int voisin = noeud + lab->nb_colonne;
                    if (voisin >= 0 && voisin < nombre_noeuds && !visite[voisin]) {
                        poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                        if (dist[voisin] == -1 || dist[noeud] + poids_arete < dist[voisin]) {
                            dist[voisin] = dist[noeud] + poids_arete;
                            predecesseur[voisin] = noeud;
                            ajout_tas(tas, voisin, dist[voisin]);
                        }
                    }
                }
            }
        }
    }
    free_tas(tas);

    // Construction du chemin le plus court
    if (!chemin_trouve || dist[arrive] == -1) {
        free(dist);
        free(visite);
        free(predecesseur);
        return NULL;
    }

    // On reconstruit le chemin à partir de l'arrivée jusqu'à l'origine
    // On ne connaît pas la longueur exacte, donc on compte d'abord
    int longueur = 0;
    int courant = arrive;
    while (courant != -1) {
        longueur++;
        courant = predecesseur[courant];
    }

    int* chemin = (int*)malloc((longueur + 1) * sizeof(int)); // +1 pour le -1 final
    courant = arrive;
    for (int i = longueur - 1; i >= 0; i--) {
        chemin[i] = courant;
        courant = predecesseur[courant];
    }
    chemin[longueur] = -1; // Fin du chemin

    chemin_plus_court* c = malloc(sizeof(chemin_plus_court));
    c->chemin = chemin;
    c->taille_chemin = longueur;
    c->labyrinthe = lab;
    c->noeuds_visites = visite; 
    c->depart = origine;
    c->arrive = arrive;

    free(dist);
    free(predecesseur);

    return c;
}

chemin_plus_court* chemin_plus_court_A_etoiles(labyrinthe* lab, int origine, int arrive, int (*heuristique)(int, int, labyrinthe*)) {
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    int* dist = (int*)malloc(nombre_noeuds * sizeof(int));
    int* visite = (int*)calloc(nombre_noeuds, sizeof(int));
    int* predecesseur = (int*)malloc(nombre_noeuds * sizeof(int));
    for (int i = 0; i < nombre_noeuds; i++) {
        dist[i] = -1;
        predecesseur[i] = -1;
    }
    dist[origine] = 0;

    tas_b* tas = create_tas(nombre_noeuds);
    ajout_tas(tas, origine, heuristique(origine, arrive, lab));

    int chemin_trouve = 0;
    while (!tas_vide(tas) && !chemin_trouve) {
        int noeud, valeur;
        extraire_min_tas(tas, &noeud, &valeur);
        if (!visite[noeud]) {
            visite[noeud] = 1;
            if (noeud == arrive) {
                chemin_trouve = 1;
            } else {
                // EST
                if (!(lab->construction[noeud] & EST)) {
                    int voisin = noeud + 1;
                    if ((voisin % lab->nb_colonne != 0) && voisin >= 0 && voisin < nombre_noeuds && !visite[voisin]) {
                        int poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                        int valeur_possible = dist[noeud] + poids_arete;
                        if (dist[voisin] == -1 || valeur_possible < dist[voisin]) {
                            dist[voisin] = valeur_possible;
                            predecesseur[voisin] = noeud;
                            int f = valeur_possible + heuristique(voisin, arrive, lab);
                            ajout_tas(tas, voisin, f);
                        }
                    }
                }
                // OUEST
                if (!(lab->construction[noeud] & OUEST)) {
                    int voisin = noeud - 1;
                    if ((noeud % lab->nb_colonne != 0) && voisin >= 0 && voisin < nombre_noeuds && !visite[voisin]) {
                        int poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                        int valeur_possible = dist[noeud] + poids_arete;
                        if (dist[voisin] == -1 || valeur_possible < dist[voisin]) {
                            dist[voisin] = valeur_possible;
                            predecesseur[voisin] = noeud;
                            int f = valeur_possible + heuristique(voisin, arrive, lab);
                            ajout_tas(tas, voisin, f);
                        }
                    }
                }
                // NORD
                if (!(lab->construction[noeud] & NORD)) {
                    int voisin = noeud - lab->nb_colonne;
                    if (voisin >= 0 && voisin < nombre_noeuds && !visite[voisin]) {
                        int poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                        int valeur_possible = dist[noeud] + poids_arete;
                        if (dist[voisin] == -1 || valeur_possible < dist[voisin]) {
                            dist[voisin] = valeur_possible;
                            predecesseur[voisin] = noeud;
                            int f = valeur_possible + heuristique(voisin, arrive, lab);
                            ajout_tas(tas, voisin, f);
                        }
                    }
                }
                // SUD
                if (!(lab->construction[noeud] & SUD)) {
                    int voisin = noeud + lab->nb_colonne;
                    if (voisin >= 0 && voisin < nombre_noeuds && !visite[voisin]) {
                        int poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                        int valeur_possible = dist[noeud] + poids_arete;
                        if (dist[voisin] == -1 || valeur_possible < dist[voisin]) {
                            dist[voisin] = valeur_possible;
                            predecesseur[voisin] = noeud;
                            int f = valeur_possible + heuristique(voisin, arrive, lab);
                            ajout_tas(tas, voisin, f);
                        }
                    }
                }
            }
        }
    }
    free_tas(tas);

    // Construction du chemin le plus court
    if (!chemin_trouve || dist[arrive] == -1) {
        free(dist);
        free(visite);
        free(predecesseur);
        return NULL;
    }

    // On reconstruit le chemin à partir de l'arrivée jusqu'à l'origine
    int longueur = 0;
    int courant = arrive;
    while (courant != -1) {
        longueur++;
        courant = predecesseur[courant];
    }

    int* chemin = (int*)malloc((longueur + 1) * sizeof(int)); // +1 pour le -1 final
    courant = arrive;
    for (int i = longueur - 1; i >= 0; i--) {
        chemin[i] = courant;
        courant = predecesseur[courant];
    }
    chemin[longueur] = -1; // Fin du chemin

    chemin_plus_court* c = malloc(sizeof(chemin_plus_court));
    c->chemin = chemin;
    c->taille_chemin = longueur;
    c->labyrinthe = lab;
    c->noeuds_visites = visite;
    c->depart = origine;
    c->arrive = arrive;

    free(dist);
    free(predecesseur);

    return c;
}

int heuristique_euclidienne(int noeud, int arrive, labyrinthe* lab) {
    int x1 = noeud % lab->nb_colonne;
    int y1 = noeud / lab->nb_colonne;
    int x2 = arrive % lab->nb_colonne;
    int y2 = arrive / lab->nb_colonne;
    double dx = x1 - x2;
    double dy = y1 - y2;
    return (int)(sqrt(dx * dx + dy * dy) + 0.5); // arrondi à l'entier le plus proche
}
int heuristique_manhattan(int noeud, int arrive, labyrinthe* lab) {
    int x1 = noeud % lab->nb_colonne;
    int y1 = noeud / lab->nb_colonne;
    int x2 = arrive % lab->nb_colonne;
    int y2 = arrive / lab->nb_colonne;
    return abs(x1 - x2) + abs(y1 - y2);
}

int heuristique_tchebychev(int noeud, int arrive, labyrinthe* lab) {
    int x1 = noeud % lab->nb_colonne;
    int y1 = noeud / lab->nb_colonne;
    int x2 = arrive % lab->nb_colonne;
    int y2 = arrive / lab->nb_colonne;
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    if (dx > dy) {
        return dx;
    }
    return dy;
}


// Fonction d'affichage du labyrinthe avec le chemin le plus court (BFS)
void afficher_labyrinthe_avec_chemin(chemin_plus_court* c) {
    labyrinthe* lab = c->labyrinthe;
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    // Création d'un tableau pour marquer les cases du chemin
    char* affichage = (char*)malloc(nombre_noeuds * sizeof(char));
    for (int i = 0; i < nombre_noeuds; i++) affichage[i] = ' ';

    // Marquer le chemin
    for (int i = 0; i < c->taille_chemin; i++) {
        if (c->chemin[i] == c->depart)
            affichage[c->chemin[i]] = 'D'; // Départ
        else if (c->chemin[i] == c->arrive)
            affichage[c->chemin[i]] = 'A'; // Arrivée
        else
            affichage[c->chemin[i]] = '*'; // Chemin
    }

    // Affichage ligne par ligne
    for (int y = 0; y < lab->nb_ligne; y++) {
        // Affichage du haut des cases
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            printf("+");
            if (lab->construction[idx] & NORD)
                printf("---");
            else
                printf("   ");
        }
        printf("+\n");
        // Affichage du contenu des cases et des murs verticaux
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            if (lab->construction[idx] & OUEST)
                printf("|");
            else
                printf(" ");
            printf(" %c ", affichage[idx]);
        }
        // Mur de droite
        printf("|\n");
    }
    // Affichage du bas du labyrinthe
    for (int x = 0; x < lab->nb_colonne; x++) {
        printf("+---");
    }
    printf("+\n");
    free(affichage);
    
    // Calcul et affichage du nombre de noeuds visités
    int nb_visites = 0;
    for (int i = 0; i < nombre_noeuds; i++) {
        if (c->noeuds_visites && c->noeuds_visites[i]) nb_visites++;
    }
    printf("Nombre de noeuds visites : %d\n", nb_visites);
    
}

void afficher_labyrinthe_avec_chemin_dijkstra(chemin_plus_court* c) {
    labyrinthe* lab = c->labyrinthe;
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    char* affichage = (char*)malloc(nombre_noeuds * sizeof(char));
    for (int i = 0; i < nombre_noeuds; i++) affichage[i] = ' ';
 
    for (int i = 0; i < c->taille_chemin; i++) {
       
        if (c->chemin[i] == c->depart)
            affichage[c->chemin[i]] = 'D';
        else if (c->chemin[i] == c->arrive)
            affichage[c->chemin[i]] = 'A';
        else
            affichage[c->chemin[i]] = '*';
    }
    
    for (int y = 0; y < lab->nb_ligne; y++) {
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            printf("+");
            if (lab->construction[idx] & NORD)
                printf("---");
            else
                printf("   ");
        }
        printf("+\n");
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            if (lab->construction[idx] & OUEST)
                printf("|");
            else
                printf(" ");
            printf(" %c ", affichage[idx]);
        }
        printf("|\n");
    }
    for (int x = 0; x < lab->nb_colonne; x++) {
        printf("+---");
    }
    printf("+\n");
    free(affichage);
    
    int nb_visites = 0;
    for (int i = 0; i < nombre_noeuds; i++) {
        if (c->noeuds_visites && c->noeuds_visites[i]) nb_visites++;
    }
    printf("Nombre de noeuds visites (Dijkstra) : %d\n", nb_visites);
    
}

void afficher_labyrinthe_avec_chemin_A_etoiles(chemin_plus_court* c) {
    labyrinthe* lab = c->labyrinthe;
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    char* affichage = (char*)malloc(nombre_noeuds * sizeof(char));
    for (int i = 0; i < nombre_noeuds; i++) affichage[i] = ' ';

    for (int i = 0; i < c->taille_chemin; i++) {
        if (c->chemin[i] == c->depart)
            affichage[c->chemin[i]] = 'D';
        else if (c->chemin[i] == c->arrive)
            affichage[c->chemin[i]] = 'A';
        else
            affichage[c->chemin[i]] = '*';
    }

    for (int y = 0; y < lab->nb_ligne; y++) {
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            printf("+");
            if (lab->construction[idx] & NORD)
                printf("---");
            else
                printf("   ");
        }
        printf("+\n");
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            if (lab->construction[idx] & OUEST)
                printf("|");
            else
                printf(" ");
            printf(" %c ", affichage[idx]);
        }
        printf("|\n");
    }
    for (int x = 0; x < lab->nb_colonne; x++) {
        printf("+---");
    }
    printf("+\n");
    free(affichage);

    int nb_visites = 0;
    for (int i = 0; i < nombre_noeuds; i++) {
        if (c->noeuds_visites && c->noeuds_visites[i]) nb_visites++;
    }
    printf("Nombre de noeuds visites (A*) : %d\n", nb_visites);
}


// Calcule la distance minimale de la destination à tous les noeuds avec Dijkstra
// Retourne un tableau dynamique de taille nb_ligne*nb_colonne contenant la distance minimale depuis 'arrive' vers chaque noeud
// On suppose que PARTITION_MAX_LIGNE et PARTITION_MAX_COLONNE sont définis dans partition.h
// et représentent les tailles maximales du labyrinthe


#define MAX_NOEUDS (P_MAX* N_MAX) // P_MAX et N_MAX sont définis dans partition.h

int* dijkstra_distances_depuis_arrivee_multiple(labyrinthe* lab, int* arrivees, int nb_arrivees) {
    static int dist[MAX_NOEUDS];
    static int visite[MAX_NOEUDS];
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;

    // Initialisation des tableaux statiques
    for (int i = 0; i < nombre_noeuds; i++) {
        dist[i] = -1;
        visite[i] = 0;
    }

    tas_b* tas = create_tas(nombre_noeuds);

    // Initialisation : toutes les arrivées sont à distance 0 et dans le tas
    for (int i = 0; i < nb_arrivees; i++) {
        int arr = arrivees[i];
        if (arr >= 0 && arr < nombre_noeuds) {
            dist[arr] = 0;
            ajout_tas(tas, arr, 0);
        }
    }

    while (!tas_vide(tas)) {
        int noeud, valeur;
        extraire_min_tas(tas, &noeud, &valeur);
        if (visite[noeud]) continue;
        visite[noeud] = 1;
        if (lab->construction[noeud] != -1) {
            // EST
            if (!(lab->construction[noeud] & EST)) {
                int voisin = noeud + 1;
                if ((voisin % lab->nb_colonne != 0) && voisin >= 0 && voisin < nombre_noeuds) {
                    int poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                    if (dist[voisin] == -1 || dist[noeud] + poids_arete < dist[voisin]) {
                        dist[voisin] = dist[noeud] + poids_arete;
                        ajout_tas(tas, voisin, dist[voisin]);
                    }
                }
            }
            // OUEST
            if (!(lab->construction[noeud] & OUEST)) {
                int voisin = noeud - 1;
                if ((noeud % lab->nb_colonne != 0) && voisin >= 0 && voisin < nombre_noeuds) {
                    int poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                    if (dist[voisin] == -1 || dist[noeud] + poids_arete < dist[voisin]) {
                        dist[voisin] = dist[noeud] + poids_arete;
                        ajout_tas(tas, voisin, dist[voisin]);
                    }
                }
            }
            // NORD
            if (!(lab->construction[noeud] & NORD)) {
                int voisin = noeud - lab->nb_colonne;
                if (voisin >= 0 && voisin < nombre_noeuds) {
                    int poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                    if (dist[voisin] == -1 || dist[noeud] + poids_arete < dist[voisin]) {
                        dist[voisin] = dist[noeud] + poids_arete;
                        ajout_tas(tas, voisin, dist[voisin]);
                    }
                }
            }
            // SUD
            if (!(lab->construction[noeud] & SUD)) {
                int voisin = noeud + lab->nb_colonne;
                if (voisin >= 0 && voisin < nombre_noeuds) {
                    int poids_arete = lab->poids_cases[noeud] + lab->poids_cases[voisin];
                    if (dist[voisin] == -1 || dist[noeud] + poids_arete < dist[voisin]) {
                        dist[voisin] = dist[noeud] + poids_arete;
                        ajout_tas(tas, voisin, dist[voisin]);
                    }
                }
            }
        }
    }
    free_tas(tas);

    // On retourne le tableau statique (attention : non réentrant, non thread-safe)
    return dist;
}

void affiche_distance(labyrinthe *lab, int* arrives, int nb_arrivees) {
    int* dist = dijkstra_distances_depuis_arrivee_multiple(lab, arrives, nb_arrivees);

    for (int y = 0; y < lab->nb_ligne; y++) {
        // Affichage du haut des cases (murs nord)
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            printf("+");
            if ((lab->construction[idx] & NORD)) {
                printf("---");
            } else {
                printf("   ");
            }
        }
        printf("+\n");
        // Affichage du contenu des cases et des murs verticaux
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            // Mur OUEST de la case courante
            if ((lab->construction[idx] & OUEST)) {
                printf("|");
            } else {
                printf(" ");
            }
            if (dist[idx] == -1)
                printf(" XX");
            else
                printf(" %2d", dist[idx]);
        }
        // Mur EST de la dernière case de la ligne
        int idx_last = y * lab->nb_colonne + (lab->nb_colonne - 1);
        if ((lab->construction[idx_last] & EST)) {
            printf("|");
        } else {
            printf(" ");
        }
        printf("\n");
    }
    // Affichage du bas du labyrinthe (murs sud)
    for (int x = 0; x < lab->nb_colonne; x++) {
        int idx = (lab->nb_ligne - 1) * lab->nb_colonne + x;
        printf("+");
        if ((lab->construction[idx] & SUD)) {
            printf("---");
        } else {
            printf("   ");
        }
    }
    printf("+\n");

}


//Ne fonctionne pas vraiment, triche et regarde les cases adjacentes sans les ajouter.
//Fonction inutile dans le cadre de notre jeu.
parcours_chemin* destination_minisante_destination_connue2(labyrinthe * lab, labyrinthe * lab_connu, int origine, int * arrivees,int nb_arrivees) {
    if (!lab || !lab_connu) return NULL;
    lab_connu->nb_ligne = lab->nb_ligne;
    lab_connu->nb_colonne = lab->nb_colonne;
    lab_connu->construction = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
    lab_connu->poids_cases = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
    lab_connu->construction[origine] = lab->construction[origine];
    lab_connu->poids_cases[origine] = lab->poids_cases[origine];
    for (int y = 0; y < lab->nb_ligne; y++) {
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            lab_connu->construction[idx] = 0;
            lab_connu->poids_cases[idx] = 1;
           // if (y == 0) lab_connu->construction[idx] |= NORD;      // Bordure du haut
            //if (y == lab->nb_ligne - 1) lab_connu->construction[idx] |= SUD;    // Bordure du bas
           // if (x == 0) lab_connu->construction[idx] |= OUEST;     // Bordure de gauche
            //if (x == lab->nb_colonne - 1) lab_connu->construction[idx] |= EST;  // Bordure de droite
        }
    }
    lab_connu->construction[origine] = lab->construction[origine];
    lab_connu->poids_cases[origine] = lab->poids_cases[origine];

    int * ordre_cases = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
    int index = 0;
   

    int* dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);

    int curr=origine;
    int taille_max_ordre_cases = lab_connu->nb_ligne * lab_connu->nb_colonne;
    int a_transite=0;
    while (curr!=arrivees[0]){
        a_transite=0;
        while(!a_transite){
            int min_dist = -1;
            int next_noeud = -1;
            // Parcours des voisins accessibles depuis curr
            // EST
            int n;
             dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);
             affiche_distance(lab_connu, arrivees, nb_arrivees);
             scanf("%d", &n);
            if (!(lab_connu->construction[curr] & EST)) {
                int voisin = curr + 1;
                if ((voisin % lab_connu->nb_colonne != 0) && dist[voisin] != -1) {
                    if (min_dist == -1 || dist[voisin] < min_dist) {
                        min_dist = dist[voisin];
                        next_noeud = voisin;
                    }
                }
            }
            // OUEST
            if (!(lab_connu->construction[curr] & OUEST)) {
                int voisin = curr - 1;
                if ((curr % lab_connu->nb_colonne != 0) && dist[voisin] != -1) {
                    if (min_dist == -1 || dist[voisin] < min_dist) {
                        min_dist = dist[voisin];
                        next_noeud = voisin;
                    }
                }
            }
            // NORD
            if (!(lab_connu->construction[curr] & NORD)) {
                int voisin = curr - lab_connu->nb_colonne;
                if (voisin >= 0 && dist[voisin] != -1) {
                    if (min_dist == -1 || dist[voisin] < min_dist) {
                        min_dist = dist[voisin];
                        next_noeud = voisin;
                    }
                }
            }
            // SUD
            if (!(lab_connu->construction[curr] & SUD)) {
                int voisin = curr + lab_connu->nb_colonne;
                if (voisin < lab_connu->nb_ligne * lab_connu->nb_colonne && dist[voisin] != -1) {
                    if (min_dist == -1 || dist[voisin] < min_dist) {
                        min_dist = dist[voisin];
                        next_noeud = voisin;
                    }
                }
            }
        
            int noeud_prometteur = -1;
            if  (next_noeud != -1) {
                // Si on a trouvé un voisin prometteur
             noeud_prometteur = next_noeud;
              curr = noeud_prometteur;
                    ordre_cases[index]=curr;
                    index++;
                    if(index >= taille_max_ordre_cases) {
                        taille_max_ordre_cases *= 2;
                        ordre_cases = (int*)realloc(ordre_cases, taille_max_ordre_cases * sizeof(int));
                    }
                if(lab_connu->construction[noeud_prometteur]==lab->construction[noeud_prometteur]&& lab->poids_cases[noeud_prometteur]==lab_connu->poids_cases[noeud_prometteur]){
                   
                    a_transite=1;
                } else {
                    // Si le noeud prommetteur n'est pas en accord avec le vrai labyrinthe.
                    lab_connu->construction[noeud_prometteur] = lab->construction[noeud_prometteur];
                    lab_connu->poids_cases[noeud_prometteur] = lab->poids_cases[noeud_prometteur];
                    //Recalculer les distances depuis l'arrivée
                
                    dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);
                    
                }

            }else {
                    // Si aucun voisin n'est prometteur, on ne peut pas avancer
                    printf("Aucun voisin prometteur trouvé depuis le noeud %d\n", curr);
                    a_transite = 1; // On sort de la boucle pour éviter une boucle infinie
            }

        }
    }
    // Ajout du noeud d'arrivée
    parcours_chemin* pc = (parcours_chemin*)malloc(sizeof(parcours_chemin));
    pc->chemin = ordre_cases;
    pc->taille_chemin = index;
    pc->distance_connue = dist;
    pc->exploration = (int*)malloc(taille_max_ordre_cases * sizeof(int));
    pc->taille_exploration = index;
    pc->labyrinthe = lab_connu;
    for (int i = 0; i < index; i++) {
        pc->exploration[i] = ordre_cases[i];
    }
    pc->exploration[index] = -1; // Marque la fin du chemin

    return pc;

}


//Ne fonctionne pas vraiment, triche et regarde les cases adjacentes sans les ajouter.
//Fonction inutile dans le cadre de notre jeu.
//Il faut utiliser prochaine_case_destination_connue pour obtenir la prochaine case à visiter.
parcours_chemin* destination_minisante_destination_connue(labyrinthe * lab, labyrinthe * lab_connu, int origine, int * arrivees, int nb_arrivees) {
    if (!lab || !lab_connu) return NULL;
    // Initialisation du labyrinthe connu si besoin
    if (lab_connu->construction == NULL || lab_connu->poids_cases == NULL) {
        lab_connu->nb_ligne = lab->nb_ligne;
        lab_connu->nb_colonne = lab->nb_colonne;
        lab_connu->construction = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        lab_connu->poids_cases = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        for (int y = 0; y < lab->nb_ligne; y++) {
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            lab_connu->construction[idx] = 0;
            lab_connu->poids_cases[idx] = 1;
        }
    }
     
    }
    //lab_connu->construction[origine] = lab->construction[origine];
    //lab_connu->poids_cases[origine] = lab->poids_cases[origine];

    int taille_max_ordre_cases = lab_connu->nb_ligne * lab_connu->nb_colonne;
    int *ordre_cases = (int*)malloc(taille_max_ordre_cases * sizeof(int));
    int index = 0;
    ordre_cases[0] = origine;
    index++;


    int* dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);
    int curr = origine;

    while (curr != arrivees[0]) {
        // Chercher le prochain noeud prometteur avec A*
        chemin_plus_court *c = chemin_plus_court_A_etoiles(lab_connu, curr, arrivees[0], heuristique_manhattan);
        int noeud_prometteur = -1;
        if (c != NULL && c->taille_chemin > 1) {
            noeud_prometteur = c->chemin[1];
        }
        if (c) free_chemin_plus_court(c);

        if (noeud_prometteur == -1) {
            // Aucun chemin trouvé, on arrête
            break;
        }

        // Si le noeud prometteur est déjà connu (structure et poids identiques)
        if (lab_connu->construction[noeud_prometteur] == lab->construction[noeud_prometteur] &&
            lab_connu->poids_cases[noeud_prometteur] == lab->poids_cases[noeud_prometteur]) {
            curr = noeud_prometteur;
            ordre_cases[index++] = curr;
            if (index >= taille_max_ordre_cases) {
                taille_max_ordre_cases *= 2;
                ordre_cases = (int*)realloc(ordre_cases, taille_max_ordre_cases * sizeof(int));
            }
        } else {
            // Découverte du vrai noeud, mise à jour du labyrinthe connu
            lab_connu->construction[noeud_prometteur] = lab->construction[noeud_prometteur];
            lab_connu->poids_cases[noeud_prometteur] = lab->poids_cases[noeud_prometteur];
            // Recalculer les distances depuis l'arrivée
            dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);
            // On ne change pas curr ici, on va relancer la boucle avec le même curr
        }
    }

    ordre_cases[index] = -1; // Marque la fin du chemin

    parcours_chemin* pc = (parcours_chemin*)malloc(sizeof(parcours_chemin));
    pc->chemin = ordre_cases;
    pc->taille_chemin = index;
    pc->distance_connue = dist;
    pc->taille_exploration = index;
    pc->labyrinthe = lab_connu;
    pc->exploration = (int*)malloc((index + 1) * sizeof(int));
    for (int i = 0; i <= index; i++) {
        pc->exploration[i] = ordre_cases[i];
    }
    return pc;
}

// Renvoie la prochaine case à visiter (indice du noeud) selon la logique A* sur lab_connu, ou -1 si bloqué
int prochaine_case_destination_connue(labyrinthe *lab, labyrinthe *lab_connu, int origine, int *arrivees, int nb_arrivees) {
    if (!lab || !lab_connu || !arrivees || nb_arrivees <= 0) return -1;

    // Initialisation du labyrinthe connu si besoin
    if (lab_connu->construction == NULL || lab_connu->poids_cases == NULL) {
        lab_connu->nb_ligne = lab->nb_ligne;
        lab_connu->nb_colonne = lab->nb_colonne;
        lab_connu->construction = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        lab_connu->poids_cases = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        for (int i = 0; i < lab->nb_ligne * lab->nb_colonne; i++) {
            lab_connu->construction[i] = 0;
            lab_connu->poids_cases[i] = 1;
        }
    }

    // On rend l'origine connue
    lab_connu->construction[origine] = lab->construction[origine];
    lab_connu->poids_cases[origine] = lab->poids_cases[origine];

    // Synchronisation des murs sur les cases voisines (bordures incluses)
    int nb_col = lab->nb_colonne;
    int nb_lig = lab->nb_ligne;
    int x = origine % nb_col;
    int y = origine / nb_col;

    // EST (droite)
    if (x < nb_col - 1) {
        int voisin = origine + 1;
        if (lab_connu->construction[origine] & EST)
            lab_connu->construction[voisin] |= OUEST;
        else
            lab_connu->construction[voisin] &= ~OUEST;
    }
    // OUEST (gauche)
    if (x > 0) {
        int voisin = origine - 1;
        if (lab_connu->construction[origine] & OUEST)
            lab_connu->construction[voisin] |= EST;
        else
            lab_connu->construction[voisin] &= ~EST;
    }
    // SUD (bas)
    if (y < nb_lig - 1) {
        int voisin = origine + nb_col;
        if (lab_connu->construction[origine] & SUD)
            lab_connu->construction[voisin] |= NORD;
        else
            lab_connu->construction[voisin] &= ~NORD;
    }
    // NORD (haut)
    if (y > 0) {
        int voisin = origine - nb_col;
        if (lab_connu->construction[origine] & NORD)
            lab_connu->construction[voisin] |= SUD;
        else
            lab_connu->construction[voisin] &= ~SUD;
    }

    int* dist = NULL;
    int noeud_prometteur = -1;
    int retry = 0;

    do {
        dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);

        // Cherche la destination la plus proche atteignable
        int closest_dest = -1;
        int min_dist = -1;
        for (int i = 0; i < nb_arrivees; i++) {
            if (arrivees[i] >= 0 && arrivees[i] < lab->nb_ligne * lab->nb_colonne) {
                if (dist[arrivees[i]] != -1 && (min_dist == -1 || dist[arrivees[i]] < min_dist)) {
                    min_dist = dist[arrivees[i]];
                    closest_dest = arrivees[i];
                }
            }
        }


        // Cherche le prochain noeud prometteur avec A*
        chemin_plus_court* c = chemin_plus_court_A_etoiles(lab_connu, origine, closest_dest, heuristique_manhattan);
        noeud_prometteur = -1;
        if (c != NULL && c->taille_chemin > 1) {
            noeud_prometteur = c->chemin[1];
        }
        if (c) free_chemin_plus_court(c);

        // Vérifie si le déplacement est réalisable dans le vrai labyrinthe
        int realisable = 0;
        if (noeud_prometteur != -1) {
            // Teste si le déplacement origine -> noeud_prometteur est possible dans lab
            int dx = noeud_prometteur % lab->nb_colonne - origine % lab->nb_colonne;
            int dy = noeud_prometteur / lab->nb_colonne - origine / lab->nb_colonne;
            if (dx == 1 && !(lab->construction[origine] & EST)) realisable = 1;
            else if (dx == -1 && !(lab->construction[origine] & OUEST)) realisable = 1;
            else if (dy == 1 && !(lab->construction[origine] & SUD)) realisable = 1;
            else if (dy == -1 && !(lab->construction[origine] & NORD)) realisable = 1;
        }

        if (noeud_prometteur != -1 && !realisable) {
            // Découvre le vrai noeud et relance
            lab_connu->construction[noeud_prometteur] = lab->construction[noeud_prometteur];
            lab_connu->poids_cases[noeud_prometteur] = lab->poids_cases[noeud_prometteur];
            retry = 1;
        } else {
            retry = 0;
        }
    } while (retry);

    // Découvre le noeud si ce n'est pas déjà fait
    if (noeud_prometteur != -1 &&
        (lab_connu->construction[noeud_prometteur] != lab->construction[noeud_prometteur] ||
         lab_connu->poids_cases[noeud_prometteur] != lab->poids_cases[noeud_prometteur])) {
        lab_connu->construction[noeud_prometteur] = lab->construction[noeud_prometteur];
        lab_connu->poids_cases[noeud_prometteur] = lab->poids_cases[noeud_prometteur];
    }

    return noeud_prometteur;
}

// Version avec vision_monstre et update_case_memoire
int prochaine_case_destination_connue_vm(labyrinthe *lab, vision_monstre *vm, int origine, int *arrivees, int nb_arrivees, unsigned long int valeur) {
    if (!lab || !vm || !arrivees || nb_arrivees <= 0) return -1;
    labyrinthe *lab_connu = vm->lab;

    // Initialisation du labyrinthe connu si besoin
    if (lab_connu->construction == NULL || lab_connu->poids_cases == NULL) {
        lab_connu->nb_ligne = lab->nb_ligne;
        lab_connu->nb_colonne = lab->nb_colonne;
        lab_connu->construction = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        lab_connu->poids_cases = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        for (int i = 0; i < lab->nb_ligne * lab->nb_colonne; i++) {
            lab_connu->construction[i] = 0;
            lab_connu->poids_cases[i] = 1;
        }
    }

    // On rend l'origine connue et update la mémoire
    lab_connu->construction[origine] = lab->construction[origine];
    lab_connu->poids_cases[origine] = lab->poids_cases[origine];
    update_case_memoire(vm, origine, valeur);

    int* dist = NULL;
    int noeud_prometteur = -1;
    int retry = 0;

    do {
        dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);

        // Cherche la destination la plus proche atteignable
        int closest_dest = -1;
        int min_dist = -1;
        for (int i = 0; i < nb_arrivees; i++) {
            if (arrivees[i] >= 0 && arrivees[i] < lab->nb_ligne * lab->nb_colonne) {
                if (dist[arrivees[i]] != -1 && (min_dist == -1 || dist[arrivees[i]] < min_dist)) {
                    min_dist = dist[arrivees[i]];
                    closest_dest = arrivees[i];
                }
            }
        }

        // Cherche le prochain noeud prometteur avec A*
        chemin_plus_court* c = chemin_plus_court_A_etoiles(lab_connu, origine, closest_dest, heuristique_manhattan);
        noeud_prometteur = -1;
        if (c != NULL && c->taille_chemin > 1) {
            noeud_prometteur = c->chemin[1];
        }
        if (c) free_chemin_plus_court(c);

        // Avant de regarder la valeur dans lab_connu, on update la mémoire

        // Vérifie si le déplacement est réalisable dans le vrai labyrinthe
        int realisable = 0;
        if (noeud_prometteur != -1) {
            verifie_case_memoire(vm,origine, valeur);
            int dx = noeud_prometteur % lab->nb_colonne - origine % lab->nb_colonne;
            int dy = noeud_prometteur / lab->nb_colonne - origine / lab->nb_colonne;
            if (dx == 1 && !(lab->construction[origine] & EST)) realisable = 1;
            else if (dx == -1 && !(lab->construction[origine] & OUEST)) realisable = 1;
            else if (dy == 1 && !(lab->construction[origine] & SUD)) realisable = 1;
            else if (dy == -1 && !(lab->construction[origine] & NORD)) realisable = 1;
        }

        if (noeud_prometteur != -1 && !realisable) {
            // Découvre le vrai noeud et relance
            lab_connu->construction[noeud_prometteur] = lab->construction[noeud_prometteur];
            lab_connu->poids_cases[noeud_prometteur] = lab->poids_cases[noeud_prometteur];
            update_case_memoire(vm, noeud_prometteur, valeur);
            retry = 1;
        } else {
            retry = 0;
        }
    } while (retry);

    // Découvre le noeud si ce n'est pas déjà fait et update mémoire
    if (noeud_prometteur != -1 &&
        (lab_connu->construction[noeud_prometteur] != lab->construction[noeud_prometteur] ||
         lab_connu->poids_cases[noeud_prometteur] != lab->poids_cases[noeud_prometteur])) {
        lab_connu->construction[noeud_prometteur] = lab->construction[noeud_prometteur];
        lab_connu->poids_cases[noeud_prometteur] = lab->poids_cases[noeud_prometteur];
        update_case_memoire(vm, noeud_prometteur, valeur);
    }

    return noeud_prometteur;
}

void boucle_affichage_prochaine_case(labyrinthe *lab, labyrinthe *lab_connu, int origine, int *arrivees, int nb_arrivees) {
    int curr = origine;
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    int taille_max = nombre_noeuds;
    int *chemin = malloc(taille_max * sizeof(int));
    int index = 0;
    int poids_total = lab->poids_cases[origine];
    chemin[index++] = curr;

    while (1) {
        if (curr == arrivees[0]) break;
        int next = prochaine_case_destination_connue(lab, lab_connu, curr, arrivees, nb_arrivees);
        if (next == -1) {
            printf("Aucun chemin trouvé ou bloqué.\n");
            break;
        }
        curr = next;
        chemin[index++] = curr;
        if (index >= taille_max) {
            taille_max *= 2;
            chemin = realloc(chemin, taille_max * sizeof(int));
        }
        poids_total += lab_connu->poids_cases[curr];
        if (curr == arrivees[0]) break;
    }
    chemin[index] = -1;

    printf("Chemin parcouru : ");
    for (int i = 0; i < index; i++) {
        printf("%d", chemin[i]);
        if (i < index - 1) printf(" -> ");
    }
    printf("\nPoids total du chemin : %d\n", poids_total);

    // Affichage graphique du chemin
    char *affichage = malloc(nombre_noeuds * sizeof(char));
    for (int i = 0; i < nombre_noeuds; i++) affichage[i] = ' ';
    for (int i = 0; i < index; i++) {
        if (chemin[i] == origine)
            affichage[chemin[i]] = 'D';
        else if (chemin[i] == arrivees[0])
            affichage[chemin[i]] = 'A';
        else
            affichage[chemin[i]] = '*';
    }
    for (int y = 0; y < lab->nb_ligne; y++) {
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            printf("+");
            if (lab_connu->construction[idx] & NORD)
                printf("---");
            else
                printf("   ");
        }
        printf("+\n");
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            if (lab_connu->construction[idx] & OUEST)
                printf("|");
            else
                printf(" ");
            printf(" %c ", affichage[idx]);
        }
        printf("|\n");
    }
    for (int x = 0; x < lab->nb_colonne; x++) {
        printf("+---");
    }
    printf("+\n");
    free(chemin);
    free(affichage);
}

void boucle_affichage_prochaine_case_vm(labyrinthe *lab, vision_monstre *vm, int origine, int *arrivees, int nb_arrivees, unsigned long int valeur) {
    int curr = origine;
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    int taille_max = nombre_noeuds;
    int *chemin = malloc(taille_max * sizeof(int));
    int index = 0;
    int poids_total = lab->poids_cases[origine];
    chemin[index++] = curr;

    unsigned long int valeur_courante = valeur;

    while (1) {
        if (curr == arrivees[0]) break;
        int next = prochaine_case_destination_connue_vm(lab, vm, curr, arrivees, nb_arrivees, valeur_courante);
        if (next == -1) {
            printf("Aucun chemin trouvé ou bloqué.\n");
            break;
        }
        curr = next;
        chemin[index++] = curr;
        if (index >= taille_max) {
            taille_max *= 2;
            chemin = realloc(chemin, taille_max * sizeof(int));
        }
        poids_total += vm->lab->poids_cases[curr];
        valeur_courante++; // Incrémenter la valeur à chaque nouveau noeud
        if (curr == arrivees[0]) break;
    }
    chemin[index] = -1;

    printf("Chemin parcouru : ");
    for (int i = 0; i < index; i++) {
        printf("%d", chemin[i]);
        if (i < index - 1) printf(" -> ");
    }
    printf("\nPoids total du chemin : %d\n", poids_total);

    // Affichage graphique du chemin avec vérification de la mémoire
    char *affichage = malloc(nombre_noeuds * sizeof(char));
    for (int i = 0; i < nombre_noeuds; i++) affichage[i] = ' ';
    valeur_courante = valeur;
    for (int i = 0; i < index; i++) {
        verifie_case_memoire(vm, chemin[i], valeur_courante);
        if (chemin[i] == origine)
            affichage[chemin[i]] = 'D';
        else if (chemin[i] == arrivees[0])
            affichage[chemin[i]] = 'A';
        else
            affichage[chemin[i]] = '*';
        valeur_courante++; // Incrémenter la valeur à chaque nouveau noeud
    }
    for (int y = 0; y < lab->nb_ligne; y++) {
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            printf("+");
            if (vm->lab->construction[idx] & NORD)
                printf("---");
            else
                printf("   ");
        }
        printf("+\n");
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            if (vm->lab->construction[idx] & OUEST)
                printf("|");
            else
                printf(" ");
            printf(" %c ", affichage[idx]);
        }
        printf("|\n");
    }
    for (int x = 0; x < lab->nb_colonne; x++) {
        printf("+---");
    }
    printf("+\n");
    free(chemin);
    free(affichage);
}

parcours_chemin* destination_minisante_multi_destinations(labyrinthe* lab, labyrinthe* lab_connu, int origine, int* arrivees, int nb_arrivees) {
    if (!lab || !lab_connu || nb_arrivees <= 0 || arrivees == NULL) return NULL;

    // Initialisation du labyrinthe connu si besoin
    if (lab_connu->construction == NULL || lab_connu->poids_cases == NULL) {
        lab_connu->nb_ligne = lab->nb_ligne;
        lab_connu->nb_colonne = lab->nb_colonne;
        lab_connu->construction = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        lab_connu->poids_cases = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        for (int i = 0; i < lab->nb_ligne * lab->nb_colonne; i++) {
            lab_connu->construction[i] = 0;
            lab_connu->poids_cases[i] = 1;
        }
    }

    // On rend l'origine connue
    lab_connu->construction[origine] = lab->construction[origine];
    lab_connu->poids_cases[origine] = lab->poids_cases[origine];

    int taille_max_ordre_cases = lab->nb_ligne * lab->nb_colonne;
    int* ordre_cases = (int*)malloc(taille_max_ordre_cases * sizeof(int));
    int index = 0;
    ordre_cases[index++] = origine;

    int* dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);
    int curr = origine;

    // Vérifie si on est déjà sur une destination
    int destination_atteinte = 0;
    for (int i = 0; i < nb_arrivees; i++) {
        if (curr == arrivees[i]) {
            destination_atteinte = 1;
            break;
        }
    }

    while (!destination_atteinte) {
        // Cherche la destination la plus proche atteignable
        int closest_dest = -1;
        int min_dist = -1;
        for (int i = 0; i < nb_arrivees; i++) {
            if (arrivees[i] >= 0 && arrivees[i] < lab->nb_ligne * lab->nb_colonne) {
                if (dist[arrivees[i]] != -1 && (min_dist == -1 || dist[arrivees[i]] < min_dist)) {
                    min_dist = dist[arrivees[i]];
                    closest_dest = arrivees[i];
                }
            }
        }
     

        // Cherche le prochain noeud prometteur avec A*
        chemin_plus_court* c = chemin_plus_court_A_etoiles(lab_connu, curr, closest_dest, heuristique_manhattan);
        int noeud_prometteur = -1;
        if (c != NULL && c->taille_chemin > 1) {
            noeud_prometteur = c->chemin[1];
        }
        if (c) free_chemin_plus_court(c);

        // Si le noeud prometteur est déjà connu (structure et poids identiques)
        if (lab_connu->construction[noeud_prometteur] == lab->construction[noeud_prometteur] &&
            lab_connu->poids_cases[noeud_prometteur] == lab->poids_cases[noeud_prometteur]) {
            curr = noeud_prometteur;
            ordre_cases[index++] = curr;
            if (index >= taille_max_ordre_cases) {
                taille_max_ordre_cases *= 2;
                ordre_cases = (int*)realloc(ordre_cases, taille_max_ordre_cases * sizeof(int));
            }
            // Vérifie si on a atteint une destination
            for (int i = 0; i < nb_arrivees; i++) {
                if (curr == arrivees[i]) {
                    destination_atteinte = 1;
                    break;
                }
            }
        } else {
            // Découverte du vrai noeud, mise à jour du labyrinthe connu
            lab_connu->construction[noeud_prometteur] = lab->construction[noeud_prometteur];
            lab_connu->poids_cases[noeud_prometteur] = lab->poids_cases[noeud_prometteur];
            // Recalculer les distances depuis les arrivées
            dist = dijkstra_distances_depuis_arrivee_multiple(lab_connu, arrivees, nb_arrivees);
            // On ne change pas curr ici, on relance la boucle avec le même curr
        }
    }

    // Redimensionne ordre_cases si nécessaire pour écrire le -1 final
    if (index >= taille_max_ordre_cases) {
        taille_max_ordre_cases *= 2;
        ordre_cases = (int*)realloc(ordre_cases, taille_max_ordre_cases * sizeof(int));
    }

    ordre_cases[index] = -1; // Marque la fin du chemin

    parcours_chemin* pc = (parcours_chemin*)malloc(sizeof(parcours_chemin));
    pc->chemin = ordre_cases;
    pc->taille_chemin = index;
    pc->distance_connue = dist;
    pc->exploration = (int*)malloc((index + 1) * sizeof(int));
    pc->taille_exploration = index;
    pc->labyrinthe = lab_connu;
    for (int i = 0; i <= index; i++) {
        pc->exploration[i] = ordre_cases[i];
    }
    return pc;
}


// Affiche l'ordre de passage des cases pour un parcours avec destinations multiples
void afficher_ordre_cases(labyrinthe* lab, parcours_chemin* pc) {
    if (!lab || !pc || !pc->chemin) {
        printf("Aucun parcours à afficher.\n");
        return;
    }
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    char* affichage = (char*)malloc(nombre_noeuds * sizeof(char));

    for (int i = 0; i < nombre_noeuds; i++) affichage[i] = ' ';
    
    // Marquer l'ordre de passage avec des chiffres ou des lettres
    for (int i = 0; i < pc->taille_chemin; i++) {
        int idx = pc->chemin[i];
        if (idx >= 0 && idx < nombre_noeuds) {
            if (i < 10)
                affichage[idx] = '0' + i;
            else if (i < 36)
                affichage[idx] = 'A' + (i - 10);
            else
                affichage[idx] = '*'; // Pour les indices > 35
        }
    }
        
    for (int y = 0; y < lab->nb_ligne; y++) {
        // Affichage du haut des cases
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            printf("+");
            if (lab->construction[idx] & NORD)
                printf("---");
            else
                printf("   ");
        }
        printf("+\n");
        // Affichage du contenu des cases et des murs verticaux
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            if (lab->construction[idx] & OUEST)
                printf("|");
            else
                printf(" ");
            printf(" %c ", affichage[idx]);
        }
        printf("|\n");
    }
    // Affichage du bas du labyrinthe
    for (int x = 0; x < lab->nb_colonne; x++) {
        printf("+---");
    }
    printf("+\n");
        
        printf("Ordre de passage des cases :\n");
        int i = 0;
        int poids_total = 0;
        while (pc->chemin[i] != -1) {
            printf("%d", pc->chemin[i]);
            if (i > 0) {
                poids_total += lab->poids_cases[pc->chemin[i]];
            }
            if (pc->chemin[i + 1] != -1) printf(" -> ");
            i++;
        }
        printf("\nPoids total du chemin parcouru : %d\n", poids_total);
    
    printf("\n");
    free(affichage);
}

// Version corrigée et améliorée de chemin_destination_inconnue
// Version améliorée : retourne un struct contenant le chemin et le nombre de passages par noeud


resultat_chemin_inconnu chemin_destination_inconnue(labyrinthe * lab, labyrinthe * G, int origine, int destination) {
    int nombre_noeuds = lab->nb_ligne * lab->nb_colonne;
    G->nb_ligne = lab->nb_ligne;
    G->nb_colonne = lab->nb_colonne;
    G->construction = (int*)malloc(nombre_noeuds * sizeof(int));
    G->poids_cases = (int*)malloc(nombre_noeuds * sizeof(int));
    for (int y = 0; y < lab->nb_ligne; y++) {
        for (int x = 0; x < lab->nb_colonne; x++) {
            int idx = y * lab->nb_colonne + x;
            G->construction[idx] = 0;
            G->poids_cases[idx] = 1;
        }
    }
    int noeud = origine;
    abr *F = NULL;  // Ensemble des visités
    abr *O = abrCreateNoeud(noeud); // Ensemble des découverts non visités

    int nb_max_parcours = nombre_noeuds;
    int *noeuds_visites = (int*)malloc(nb_max_parcours * sizeof(int));
    int *nb_passages = (int*)calloc(nombre_noeuds, sizeof(int));
    int index = 0;
    while (noeud != destination) {
        F = abrInsert(F, noeud); // Marquer comme visité
        O = abrDelete(O, noeud); // Retirer de l'ensemble des découverts
        G->construction[noeud] = lab->construction[noeud];
        G->poids_cases[noeud] = lab->poids_cases[noeud];

        noeuds_visites[index++] = noeud;
        nb_passages[noeud]++;
        if (index >= nb_max_parcours) {
            nb_max_parcours *= 2;
            noeuds_visites = realloc(noeuds_visites, nb_max_parcours * sizeof(int));
        }
        int suivant = -1;
        // Exploration des voisins
        for (int i = 0; i < 4; i++) {
            int voisin = -1;
            if (i == 0 && !(G->construction[noeud] & NORD)) { // NORD
                voisin = noeud - lab->nb_colonne;
            }
            if (i == 1 && !(G->construction[noeud] & SUD)) { // SUD
                voisin = noeud + lab->nb_colonne;
            }
            if (i == 2 && !(G->construction[noeud] & OUEST)) { // OUEST
                voisin = noeud - 1;
            }
            if (i == 3 && !(G->construction[noeud] & EST)) { // EST
                voisin = noeud + 1;
            }
            if (voisin >= 0 && voisin < nombre_noeuds) {
                if (!abrSearch(F, voisin)) { // Pas déjà visité
                    if (!abrSearch(O, voisin)) {
                        O = abrInsert(O, voisin);
                        if (suivant == -1) {
                            suivant = voisin;
                        }
                    }
                }
            }
        }
        if (suivant == -1) {
            // Tous les voisins accessibles ont déjà été visités
            // Chercher dans O le noeud à distance minimale de noeud
            tableau_int noeuds_decouverts = abrToArray(O);
            int *dist = dijkstra_distances_depuis_arrivee_multiple(G, &noeud, 1);

            int fils = -1;
            for (int i = 0; i < noeuds_decouverts.taille; i++) {
                int v = noeuds_decouverts.data[i];
                if (dist[v] != -1 && (fils == -1 || dist[v] < dist[fils])) {
                    fils = v;
                }
            }
            // Aller jusqu'à fils avec le plus court chemin dans G
            parcours_chemin *pc = destination_minisante_destination_connue(lab, G, noeud, &fils, 1);
            for (int i = 0; i < pc->taille_chemin-1; i++) {
                if (pc->chemin[i] != noeud) {
                    noeuds_visites[index++] = pc->chemin[i];
                    nb_passages[pc->chemin[i]]++;
                    G->construction[pc->chemin[i]] = lab->construction[pc->chemin[i]];
                    G->poids_cases[pc->chemin[i]] = lab->poids_cases[pc->chemin[i]];
                    if (index >= nb_max_parcours) {
                        nb_max_parcours *= 2;
                        noeuds_visites = realloc(noeuds_visites, nb_max_parcours * sizeof(int));
                    }
                }
            }
            suivant = fils;
        }
        noeud = suivant;
    }
    noeuds_visites[index] = -1; // Marque la fin

    resultat_chemin_inconnu res;
    res.noeuds_visites = noeuds_visites;
    res.nb_passages = nb_passages;
    return res;
}
// Version "vision monstre" : renvoie la prochaine case à visiter pour explorer le labyrinthe inconnu
// destination devient un tableau d'entiers (0 = pas destination, 2 = destination)
// Structures globales pour conserver l'état entre les appels
typedef struct {
    abr *F;
    abr *O;
    labyrinthe *G;
    int last_noeud;
    int initialised;
} etat_exploration_inconnue_vm;

int prochaine_case_destination_inconnue_vm(labyrinthe *lab, vision_monstre *vm, int origine, int *destination, unsigned long int valeur) {
    static etat_exploration_inconnue_vm etat = {NULL, NULL, NULL, -1, 0};

    if (!lab || !vm || !destination) return -1;
    labyrinthe *G = vm->lab;

    // Initialisation du labyrinthe connu si besoin
    if (G->construction == NULL || G->poids_cases == NULL || G->nb_ligne != lab->nb_ligne || G->nb_colonne != lab->nb_colonne) {
        G->nb_ligne = lab->nb_ligne;
        G->nb_colonne = lab->nb_colonne;
        G->construction = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        G->poids_cases = (int*)malloc(lab->nb_ligne * lab->nb_colonne * sizeof(int));
        for (int i = 0; i < lab->nb_ligne * lab->nb_colonne; i++) {
            G->construction[i] = 0;
            G->poids_cases[i] = 1;
        }
        if (etat.F) abrFree(etat.F);
        if (etat.O) abrFree(etat.O);
        etat.F = NULL;
        etat.O = NULL;
        etat.last_noeud = origine;
        etat.initialised = 1;
    }

    // Initialisation des ensembles F et O si besoin
    if (etat.F == NULL && etat.O == NULL) {
        etat.F = NULL;
        etat.O = abrCreateNoeud(origine);
        etat.last_noeud = origine;
    }

    int noeud = etat.last_noeud;
    if (origine != noeud) {
        // Si on a changé d'origine (reset), on réinitialise tout
        if (etat.F) abrFree(etat.F);
        if (etat.O) abrFree(etat.O);
        etat.F = NULL;
        etat.O = abrCreateNoeud(origine);
        noeud = origine;
        etat.last_noeud = origine;
        // On ne reset pas G ici pour garder la mémoire du labyrinthe connu
    }

    // On s'arrête si on est sur une destination (destination[noeud] == 2)
    if (destination[noeud] == 2) {
        return -1;
    }

    etat.F = abrInsert(etat.F, noeud); // Marquer comme visité
    etat.O = abrDelete(etat.O, noeud); // Retirer de l'ensemble des découverts
    G->construction[noeud] = lab->construction[noeud];
    G->poids_cases[noeud] = lab->poids_cases[noeud];
   // update_case_memoire(vm, noeud, valeur);

    int suivant = -1;
    // Exploration des voisins
    for (int i = 0; i < 4; i++) {
        int voisin = -1;
        if (i == 0 && !(G->construction[noeud] & NORD)) { // NORD
            voisin = noeud - lab->nb_colonne;
        }
        if (i == 1 && !(G->construction[noeud] & SUD)) { // SUD
            voisin = noeud + lab->nb_colonne;
        }
        if (i == 2 && !(G->construction[noeud] & OUEST)) { // OUEST
            voisin = noeud - 1;
        }
        if (i == 3 && !(G->construction[noeud] & EST)) { // EST
            voisin = noeud + 1;
        }
        if (voisin >= 0 && voisin < lab->nb_ligne * lab->nb_colonne) {
            if (!abrSearch(etat.F, voisin)) { // Pas déjà visité
                if (!abrSearch(etat.O, voisin)) {
                    etat.O = abrInsert(etat.O, voisin);
                    if (suivant == -1) {
                        suivant = voisin;
                    }
                }
            }
        }
    }
    if (suivant == -1) {
        // Tous les voisins accessibles ont déjà été visités
        // Chercher dans O le noeud à distance minimale de noeud
        tableau_int noeuds_decouverts = abrToArray(etat.O);
        int *dist = dijkstra_distances_depuis_arrivee_multiple(G, &noeud, 1);

        int fils = -1;
        for (int i = 0; i < noeuds_decouverts.taille; i++) {
            int v = noeuds_decouverts.data[i];
            if (dist[v] != -1 && (fils == -1 || dist[v] < dist[fils])) {
                fils = v;
            }
        }
        // Aller jusqu'à fils avec le plus court chemin dans G
        int tmp_dest[1] = {fils};
        parcours_chemin *pc = destination_minisante_destination_connue(lab, G, noeud, tmp_dest, 1);
        int next = -1;
        if (pc && pc->taille_chemin > 1) {
            next = pc->chemin[1];
        }
        
        etat.last_noeud = next;
        return next;
    } else {
        etat.last_noeud = suivant;
        return suivant;
    }
}

void boucle_affichage_prochaine_case_inconnue_vm(labyrinthe *lab, vision_monstre *vm, int origine, int *destination, unsigned long int valeur) {
    int curr = origine;
    int nombre_noeuds = lab->nb_colonne * lab->nb_ligne;
    int taille_max = nombre_noeuds;
    int *chemin = malloc(taille_max * sizeof(int));
    int index = 0;
    int poids_total = lab->poids_cases[origine];
    chemin[index++] = curr;
    unsigned long int valeur_courante = valeur;

    while (1) {
        if (destination[curr] == 2) break;
        int next = prochaine_case_destination_inconnue_vm(lab, vm, curr, destination, valeur_courante);
        if (next == -1) {
            printf("Aucun chemin trouvé ou bloqué.\n");
            break;
        }
        curr = next;
        chemin[index++] = curr;
        if (index >= taille_max) {
            taille_max *= 2;
            chemin = realloc(chemin, taille_max * sizeof(int));
        }
        poids_total += vm->lab->poids_cases[curr];
        valeur_courante++;
        if (destination[curr] == 2) break;

        // Affichage graphique de l'étape courante
        char *affichage = malloc(nombre_noeuds * sizeof(char));
        for (int i = 0; i < nombre_noeuds; i++) affichage[i] = ' ';
        valeur_courante = valeur;
        for (int i = 0; i < index; i++) {
            verifie_case_memoire(vm, chemin[i], valeur_courante);
            if (chemin[i] == origine)
                affichage[chemin[i]] = 'D';
            else if (destination[chemin[i]] == 2)
                affichage[chemin[i]] = 'A';
            else
                affichage[chemin[i]] = '*';
            valeur_courante++;
        }
        for (int y = 0; y < lab->nb_ligne; y++) {
            for (int x = 0; x < lab->nb_colonne; x++) {
                int idx = y * lab->nb_colonne + x;
                printf("+");
                if (vm->lab->construction[idx] & NORD)
                    printf("---");
                else
                    printf("   ");
            }
            printf("+\n");
            for (int x = 0; x < lab->nb_colonne; x++) {
                int idx = y * lab->nb_colonne + x;
                if (vm->lab->construction[idx] & OUEST)
                    printf("|");
                else
                    printf(" ");
                printf(" %c ", affichage[idx]);
            }
            printf("|\n");
        }
        for (int x = 0; x < lab->nb_colonne; x++) {
            printf("+---");
        }
        printf("+\n");
        free(affichage);

        printf("Appuyez sur Entrée pour continuer...\n");
        getchar();
    }
    chemin[index] = -1;

    printf("Chemin parcouru : ");
    for (int i = 0; i < index; i++) {
        printf("%d", chemin[i]);
        if (i < index - 1) printf(" -> ");
    }
    printf("\nPoids total du chemin : %d\n", poids_total);

    free(chemin);
}

//Affiche noeuds_visites (-1 = fin du tableau)
void afficher_noeuds_visites(int* noeuds_visites) {
    if (noeuds_visites == NULL) {
        printf("Aucun noeud visité.\n");
        return;
    }
    printf("Noeuds visités : ");
    for (int i = 0; noeuds_visites[i] != -1; i++) {
        printf("%d ", noeuds_visites[i]);
    }
    printf("\n");
}