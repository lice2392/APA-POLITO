#include "nomi.h"

struct names{
    Nome *nomi;
    int maxEl, dim;
};


Nomi NOMIinit(){
    Nomi n;

    n=(Nomi)malloc(sizeof(struct names));
    if(n==NULL) exit(EXIT_FAILURE);

    n->dim=0;
    n->maxEl=1;

    n->nomi=(Nome*)malloc(n->maxEl*sizeof(Nome));
    if(n->nomi==NULL) exit(EXIT_FAILURE);

    return n;
}




void NOMIinsert(Nomi n, Nome nome){
    if(n->maxEl==n->dim){
        n->maxEl=2*n->maxEl;
        n->nomi=realloc(n->nomi, n->maxEl*sizeof(Nome));
        if(n->nomi==NULL) exit(EXIT_FAILURE);
    }
    n->nomi[n->dim]=nome;
    (n->dim)++;
    return;
}




int NOMIsearch(Nomi n, char *nome){
    int i;

    for(i=0; i<n->dim; i++){
        if(strcmp(nome, n->nomi[i].nome)==0){
            return i;
        }
    }
    return -1;
}




int NOMIgetCount(Nomi n){
    return n->dim;
}




void NOMIfree(Nomi n){
    if(n!=NULL){
        if(n->nomi!=NULL){
            free(n->nomi);
        }
        free(n);
    }
    return;
}
