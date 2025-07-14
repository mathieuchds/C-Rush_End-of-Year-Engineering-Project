#ifndef LISTE_H
#define LISTE_H

// #define TAILLE_LISTE 10

typedef struct list {
    int value;
    struct list * next;
} list;


list * listCreate();

list * listAdd(list * , int ); 

void listDisplay(list * );

void listInverseDisplay(list * );

int listSearch(list * , int);

list * listMap(list* , int (*)(int));

list * listFilter(list*  , int (*)(int));

int listFold(list*  , int (*)(int,int),int);

int listSum(list* );
int listProd(list* );
int listLen(list* );

list* listInverse(list *l);

void listFree(list *);

#endif
