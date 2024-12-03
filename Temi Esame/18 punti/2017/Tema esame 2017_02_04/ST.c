#include "ST.h"

struct tabella{
    Vertice *vertici;
    int dim, maxEl;
};


ST STinit(int maxN){
    ST st;

    st=(ST)malloc(sizeof(struct tabella));
    if(st==NULL) exit(EXIT_FAILURE);

    st->maxEl=maxN;
    st->dim=0;

    st->vertici=(Vertice*)malloc(maxN*sizeof(Vertice));
    if(st->vertici==NULL) exit(EXIT_FAILURE);

    return st;
}




void STinsert(ST st, Vertice v){
    if(st->dim==st->maxEl){
        st->maxEl=2*st->maxEl;
        st->vertici=realloc(st->vertici, st->maxEl*sizeof(Vertice));
        if(st->vertici==NULL) exit(EXIT_FAILURE);
    }
    st->vertici[st->dim]=v;
    (st->dim)++;
    return;
}




Vertice STgetByIndex(ST st, int index){
    return st->vertici[index];
}




int STsearch(ST st, char *nome){
    int i;

    for(i=0; i<st->dim; i++){
        if(strcmp(st->vertici[i].nome, nome)==0)
            return i;
    }
    return -1;
}




void STfree(ST st){
    if(st!=NULL){
        if(st->vertici!=NULL){
            free(st->vertici);
        }
        free(st);
    }
}
