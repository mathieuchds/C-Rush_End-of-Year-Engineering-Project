#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

// ===================== TAS BINAIRE MINIMAL =========================


tas_b *create_tas(int n) {
    tas_b *tas = malloc(sizeof(tas_b));
    tas->data = malloc(2 * sizeof(int *));
    tas->data[0] = malloc(n * sizeof(int)); // indices
    tas->data[1] = malloc(n * sizeof(int)); // valeurs
    tas->taille = 0;
    tas->capacite = n;
    return tas;
}

void free_tas(tas_b *tas) {
    free(tas->data[0]);
    free(tas->data[1]);
    free(tas->data);
    free(tas);
}

void realloc_tas(tas_b *tas) {
    int new_c = tas->capacite + 10;
    tas->data[0] = realloc(tas->data[0], new_c * sizeof(int));
    tas->data[1] = realloc(tas->data[1], new_c * sizeof(int));
    tas->capacite = new_c;
}

// Ajoute (indice, value) dans le tas
int ajout_tas(tas_b *tas, int indice, int value) {
    if (tas->taille >= tas->capacite) {
        realloc_tas(tas);
    }
    int i = tas->taille;
    tas->data[0][i] = indice;
    tas->data[1][i] = value;
    tas->taille++;

    // Remonter pour maintenir la propriété de tas min
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (tas->data[1][i] < tas->data[1][parent]) {
            // swap valeur
            int tmp_val = tas->data[1][i];
            tas->data[1][i] = tas->data[1][parent];
            tas->data[1][parent] = tmp_val;
            // swap indice
            int tmp_idx = tas->data[0][i];
            tas->data[0][i] = tas->data[0][parent];
            tas->data[0][parent] = tmp_idx;
            i = parent;
        } else {
            break;
        }
    }
    return 0;
}

// Supprime la racine du tas (min), ne retourne rien
int suppression_tas(tas_b *tas) {
    if (tas->taille == 0) return -1;
    tas->data[0][0] = tas->data[0][tas->taille - 1];
    tas->data[1][0] = tas->data[1][tas->taille - 1];
    tas->taille--;

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < tas->taille && tas->data[1][left] < tas->data[1][smallest])
            smallest = left;
        if (right < tas->taille && tas->data[1][right] < tas->data[1][smallest])
            smallest = right;

        if (smallest != i) {
            // swap valeur
            int tmp_val = tas->data[1][i];
            tas->data[1][i] = tas->data[1][smallest];
            tas->data[1][smallest] = tmp_val;
            // swap indice
            int tmp_idx = tas->data[0][i];
            tas->data[0][i] = tas->data[0][smallest];
            tas->data[0][smallest] = tmp_idx;
            i = smallest;
        } else {
            break;
        }
    }
    return 0;
}

// Extrait le min (racine) du tas et le supprime
int extraire_min_tas(tas_b *tas, int *indice, int *value) {
    if (tas->taille == 0) return -1;
    *indice = tas->data[0][0];
    *value = tas->data[1][0];
    suppression_tas(tas);
    return 0;
}

int tas_vide(tas_b *tas) {
    return tas->taille == 0;
}

// ===================== FILE (QUEUE) =========================



file *create_file(int n) {
    file *F = malloc(sizeof(file));
    F->data = malloc(n * sizeof(int));
    F->taille = 0;
    F->capacite = n;
    F->deb = 0;
    F->fin = 0;
    return F;
}

void free_file(file *F) {
    free(F->data);
    free(F);
}

void realloc_file(file *F) {
    int new_c = F->capacite + 10;
    int *new_data = malloc(new_c * sizeof(int));
    for (int i = 0; i < F->taille; ++i) {
        new_data[i] = F->data[(F->deb + i) % F->capacite];
    }
    free(F->data);
    F->data = new_data;
    F->capacite = new_c;
    F->deb = 0;
    F->fin = F->taille;
}

int enfiler(file *F, int value) {
    if (F->taille == F->capacite) {
        realloc_file(F);
    }
    F->data[F->fin] = value;
    F->fin = (F->fin + 1) % F->capacite;
    F->taille++;
    return 1;
}

int defiler(file *F) {
    if (F->taille == 0) return -1;
    int val = F->data[F->deb];
    F->deb = (F->deb + 1) % F->capacite;
    F->taille--;
    return val;
}

int file_vide(file *F) {
    return F->taille == 0;
}

int get_taille_file(file *F) {
    return F->taille;
}

// ===================== ABR =========================


abr *abrCreateNoeud(int key) {
    abr *BST = malloc(sizeof(abr));
    BST->value = key;
    BST->fils_gauche = NULL;
    BST->fils_droit = NULL;
    return BST;
}

abr *abrInsert(abr *root, int key) {
    if (root == NULL) return abrCreateNoeud(key);
    if (key < root->value)
        root->fils_gauche = abrInsert(root->fils_gauche, key);
    else if (key > root->value)
        root->fils_droit = abrInsert(root->fils_droit, key);
    // Si key == root->value, on ne fait rien (pas de doublons)
    return root;
}

abr *abrSearch(abr *root, int key) {
    if (root == NULL || root->value == key)
        return root;
    if (key < root->value)
        return abrSearch(root->fils_gauche, key);
    else
        return abrSearch(root->fils_droit, key);
}


// Fonction récursive pour remplir le tableau à partir de l'ABR (infixe)
void abrToArrayRec(abr *root, int *arr, int *index) {
    if (root == NULL) return;
    abrToArrayRec(root->fils_gauche, arr, index);
    arr[(*index)++] = root->value;
    abrToArrayRec(root->fils_droit, arr, index);
}

int abrCount(abr *root) {
    if (root == NULL) return 0;
    return 1 + abrCount(root->fils_gauche) + abrCount(root->fils_droit);
}

// Renvoie une structure contenant le tableau trié et sa taille
tableau_int abrToArray(abr *root) {
    tableau_int result;
    result.taille = abrCount(root);
    result.data = malloc(result.taille * sizeof(int));
    int index = 0;
    abrToArrayRec(root, result.data, &index);
    return result;
}


abr *abrMinValue(abr *root) {
    abr *current = root;
    while (current && current->fils_gauche != NULL)
        current = current->fils_gauche;
    return current;
}

abr *abrDelete(abr *root, int key) {
    if (root == NULL) return NULL;
    if (key < root->value)
        root->fils_gauche = abrDelete(root->fils_gauche, key);
    else if (key > root->value)
        root->fils_droit = abrDelete(root->fils_droit, key);
    else {
        // Noeud à supprimer trouvé
        if (root->fils_gauche == NULL) {
            abr *temp = root->fils_droit;
            free(root);
            return temp;
        } else if (root->fils_droit == NULL) {
            abr *temp = root->fils_gauche;
            free(root);
            return temp;
        }
        // Deux enfants
        abr *temp = abrMinValue(root->fils_droit);
        root->value = temp->value;
        root->fils_droit = abrDelete(root->fils_droit, temp->value);
    }
    return root;
}

void abrFree(abr *root) {
    if (root) {
        abrFree(root->fils_gauche);
        abrFree(root->fils_droit);
        free(root);
    }
}
