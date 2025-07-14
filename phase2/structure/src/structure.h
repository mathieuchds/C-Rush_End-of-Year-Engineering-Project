#include <stdio.h>

// TAS BINAIRE ---------------------------------------------------------------
typedef struct tas_b {
    int capacite;
    int taille;
    int ** data; 
} tas_b;


// primitives de tas
tas_b * create_tas (int n);
void free_tas (tas_b * tas);
void realloc_tas (tas_b * tas);
int ajout_tas (tas_b * tas,int indice, int value);
int suppression_tas (tas_b * tas);
int extraire_min_tas(tas_b * tas, int * indice, int * value);
int tas_vide (tas_b * tas);



// FILE ---------------------------------------------------------------

typedef struct file {
    int * data; //faire en 2D
    int capacite; //capacité
    int taille;
    int deb;
    int fin;
}file;

//primitive de file
file *  create_file(int n);
void free_file(file * F);
void realloc_file (file * F);
int enfiler (file * F, int value);
int defiler (file * F);
int file_vide(file * tas);
int get_taille_file(file * tas);


// ARBRE BINAIRE DE RECHERCHE ----------------------------------------------
typedef struct abr {
    int value;
    struct abr *fils_gauche;
    struct abr *fils_droit;
} abr;
// Structure pour contenir un tableau d'entiers et sa taille
typedef struct {
    int *data;
    int taille;
} tableau_int;

//primitives des arbres binaires
abr * abrCreateNoeud(int key);
abr * abrInsert(abr * root, int key);
abr *abrSearch(abr *root, int key);
abr * abrMinValue(abr * root);
abr * abrDelete(abr * root, int key);
void abrFree(abr * root);
tableau_int abrToArray(abr *root);
int abrCount(abr *root);
void abrToArrayRec(abr *root, int *arr, int *index);
