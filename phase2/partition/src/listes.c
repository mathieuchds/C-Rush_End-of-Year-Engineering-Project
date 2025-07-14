#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listes.h"

list * listCreate() {
    return NULL;
}

list * listAdd(list * l,int n){
    list * plist=(list *) malloc(sizeof(list));
    if (plist==NULL) return NULL;

    plist->value=n;
    plist->next=l;
    return plist;
}



void listDisplay(list * l){
    if (l!=NULL){
        listDisplay(l->next);
        printf("%d-",l->value);
    }
    return;

}


void listInverseDisplay(list * l){
    if (l!=NULL){
        printf("%d-",l->value);
        listInverseDisplay(l->next);
    }
    return;
}
     

int listSearch(list * plist, int n){
    if (plist==NULL){
        return 0;
    }
    if (plist->value==n){
        return 1;
    }
    return listSearch(plist->next,n);
}



list * listMap(list* l , int (*f)(int)){
    if (l==NULL){
        return NULL;
    }
    l->value=f(l->value);
    l->next=listMap(l->next,f);
    return l;


}

list * listFilter(list* l , int (*p)(int)){
    list * li2=listCreate();
    if (l==NULL){
        return NULL;
    }
    if (p(l->value)){
        li2=listAdd(listFilter(l->next,p),l->value);
    }
    else{
        li2=listFilter(l->next,p);
    }
    return li2;

}

int listFold(list* l , int (*op)(int,int),int base){
    if (l==NULL){
        return base;
    }
    else{
        return op(l->value,listFold(l->next,op,base));
    }
    
}


// TO DO  question 7
// Fonction opSum
// .....
int opSum(int x ,int y){
    return x+y;
}

int listSum(list* l ){
    return listFold(l,&opSum,0);
}

// TO DO  question 7
// Fonction opProd
// .....

int opProd(int x, int y){
    return x*y;
}
int listProd(list* l ){
    return listFold(l,&opProd,1);
}

// TO DO  question 7
// Fonction opLen
// .....
/*
int oplen(int x,int y){
    return 1+y;
}

int listLen(list* l ){
    return listFold(l,&oplen,0);
}
*/
// concatene à l1 l'inverse de l2
list * ajouteInverse(list * l1,list * l2){
    if (l2==NULL){
        return l1;
    }
    return ajouteInverse(listAdd(l1,l2->value),l2->next);
} 

list* listInverse(list *l){
    list * l2=listCreate();
    l2=ajouteInverse(l2,l);
    return l2;
}



void listFree(list * plist){
    if (plist!=NULL){
        listFree(plist->next);
        free(plist);
    }
}