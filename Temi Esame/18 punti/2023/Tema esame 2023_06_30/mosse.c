#include "mosse.h"

struct mosse{
    Mossa *mosse;
    int maxEl, dim;
};




Mosse MOSSEinit(int dim){
    Mosse m;

    m=(Mosse)malloc(sizeof(struct mosse));
    if(m==NULL) exit(EXIT_FAILURE);

    m->maxEl=dim;
    m->dim=0;

    m->mosse=(Mossa*)malloc(dim*sizeof(Mossa));
    if(m->mosse==NULL) exit(EXIT_FAILURE);
    return m;
}




Mosse MOSSEread(FILE *f){
    Mosse m;
    int nMosse, i;

    fscanf(f, "%d", &nMosse);
    m=MOSSEinit(nMosse);

    m->dim=nMosse;

    for(i=0; i<nMosse; i++){
        m->mosse[i]=MOSSAread(f);
    }
    return m;
}




void MOSSEprint(Mosse m, FILE *f){
    int i;

    for(i=0; i<m->dim; i++){
        MOSSAprint(m->mosse[i], f);
        fprintf(f, "\n\n");
    }
    return;
}




Mossa MOSSEgetMossa(Mosse m, int index){
    return m->mosse[index];
}




int MOSSEgetNumMosse(Mosse m){
    return m->dim;
}




void MOSSEaddMossa(Mosse m, Mossa mo){
    if(m->dim==m->maxEl){
        m->maxEl=2*m->maxEl;
        m=realloc(m->mosse, m->maxEl*sizeof(Mossa));
        if(m->mosse==NULL) exit(EXIT_FAILURE);
    }
    m->mosse[m->dim]=mo;
    m->dim++;
    return;
}




void MOSSEeliminaMossa(Mosse m){
    MOSSAclear(&m->mosse[m->dim-1]);
    m->dim--;
    return;
}




void MOSSEfree(Mosse m){
    int i;
    if(m!=NULL){
        for(i=0; i<m->dim; i++){
            MOSSAclear(&m->mosse[i]);
        }
        free(m);
    }
    return;
}
