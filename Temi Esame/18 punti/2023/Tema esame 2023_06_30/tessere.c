#include "tessere.h"

struct tessere{
    Tessera *tessere;
    int nTessere, maxEl;
};




Tessere TESSEREinit(int N){
    Tessere t;

    t=(Tessere)malloc(sizeof(struct tessere));
    if(t==NULL) exit(EXIT_FAILURE);

    t->maxEl=N;
    t->nTessere=0;

    t->tessere=(Tessera*)malloc(N*sizeof(Tessera));
    if(t->tessere==NULL) exit(EXIT_FAILURE);

    return t;
}




void TESSEREaddTessera(Tessere t, Tessera te){
    if(t->maxEl==t->nTessere){
        t->maxEl=2*t->maxEl;
        t->tessere=realloc(t->tessere, t->maxEl*sizeof(Tessera));
        if(t->tessere==NULL) exit(EXIT_FAILURE);
    }
    t->tessere[t->nTessere]=te;
    t->nTessere++;
    return;
}




void TESSEREprint(Tessere t, FILE *f){
    int i;
    for(i=0; i<t->nTessere; i++){
        TESSERAprint(t->tessere[i], f);
        fprintf(f, "\n");
    }
    return;
}




Tessera TESSEREgetTessera(Tessere t, int index){
    return t->tessere[index];
}




int TESSEREgetNumTessere(Tessere t){
    return t->nTessere;
}




int TESSEREsearchTessera(Tessere t, Tessera te){
    int i;
    for(i=0; i<t->nTessere; i++){
        if(TESSERAcompare(te, t->tessere[i])==UGUALE)
            return i;
    }
    return -1;
}




void TESSEREfree(Tessere t){
    if(t!=NULL){
        if(t->tessere!=NULL){
            free(t->tessere);
        }
        free(t->tessere);
    }
    return;
}
