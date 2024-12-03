#include "persone.h"

struct persone{
    Persona *persone;
    int maxEl, dim;
};




Persone PERSONEinit(int dim){
    Persone p;

    p=(Persone)malloc(sizeof(struct persone));
    if(p==NULL) exit(EXIT_FAILURE);

    p->maxEl=dim;

    p->dim=0;

    p->persone=(Persona*)malloc(dim*sizeof(Persona));
    if(p->persone==NULL) exit(EXIT_FAILURE);

    return p;
}




Persone PERSONEread(FILE *f, int N){
    Persone p;
    int i, j;

    p=PERSONEinit(N);

    for(i=0; i<N; i++){
        p->persone[i]=PERSONAread(f);
        p->dim++;
        for(j=0; j<N; j++){
            fscanf(f, "%*s");
        }
    }
    return p;
}




void PERSONEprint(Persone p, FILE *f){
    int i;

    for(i=0; i<p->dim; i++){
        PERSONAprint(p->persone[i], f);
        fprintf(f, "\n");
    }
    return;
}




int PERSONEsearch(Persone p, Persona pe){
    int i;

    for(i=0; i<p->dim; i++){
        if(strcmp(pe.nome, p->persone[i].nome)==0)
            return i;
    }
    return -1;
}




void PERSONEfree(Persone p){
    if(p!=NULL){
        if(p->persone!=NULL){
            free(p->persone);
        }
        free(p);
    }
    return;
}
