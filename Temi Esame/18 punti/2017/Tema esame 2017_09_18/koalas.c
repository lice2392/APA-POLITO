#include "koalas.h"

struct koalas{
    Koala *vettKoala;
    int dim;
};


Koalas KOALASinit(int N){
    Koalas k;

    k=(Koalas)malloc(sizeof(struct koalas));
    if(k==NULL) exit(EXIT_FAILURE);

    k->dim=N;

    k->vettKoala=(Koala*)malloc(N*sizeof(Koala));
    if(k->vettKoala==NULL) exit(EXIT_FAILURE);

    return k;
}




Koalas KOALASread(FILE *f, int N, int T){
    Koalas k;
    int i;

    k=KOALASinit(N);

    for(i=0; i<N; i++){
        k->vettKoala[i]=KOALAread(f, T);
    }
    return k;
}




int KOALASsearch(Koalas k, char *nome){
    int i;

    for(i=0; i<k->dim; i++){
        if(strcmp(k->vettKoala[i].nome, nome)==0){
            return i;
        }
    }
    return -1;
}




Koala *KOALASgetKoalaByIndex(Koalas k, int index){
    return &k->vettKoala[index];
}




void KOALASfree(Koalas k){
    int i;

    if(k!=NULL){
        if(k->vettKoala!=NULL){
            for(i=0; i<k->dim; i++){
                KOALAclear(&k->vettKoala[i]);
            }
            free(k->vettKoala);
        }
        free(k);
    }
    return;
}
