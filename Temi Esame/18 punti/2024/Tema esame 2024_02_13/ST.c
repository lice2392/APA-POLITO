#include "ST.h"

struct table{
    Vertice *vertici;
    int maxEl, dim;
};


ST STinit(int N){
    ST st;

    st=(ST)malloc(sizeof(struct table));
    if(st==NULL) exit(EXIT_FAILURE);

    st->dim=0;
    st->maxEl=N;

    st->vertici=(Vertice*)malloc(N*sizeof(Vertice));
    if(st->vertici==NULL) exit(EXIT_FAILURE);

    return st;
}




void STinsert(ST st, Vertice v){
    if(st->maxEl==st->dim){
        st->maxEl=2*st->maxEl;
        st->vertici=realloc(st->vertici, st->maxEl*sizeof(Vertice));
        if(st->vertici==NULL) exit(EXIT_FAILURE);
    }
    st->vertici[st->dim]=v;
    (st->dim)++;
    return;
}




int STsearch(ST st, char *nome, int val){
    int i;

    for(i=0; i<st->dim; i++){
        if(strcmp(nome, st->vertici[i].nome)==0 && st->vertici[i].val==val){
            return i;
        }
    }
    return -1;
}




Vertice STgetByIndex(ST st, int index){
    return st->vertici[index];
}




void STfree(ST st){
    if(st!=NULL){
        if(st->vertici!=NULL){
            free(st->vertici);
        }
        free(st);
    }
    return;
}
