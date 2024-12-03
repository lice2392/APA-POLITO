#include "copertura.h"

struct cop{
    int *vertici;
    int nV;
};


Copertura COPERTURAinit(int nV){
    Copertura c;

    c=(Copertura)malloc(sizeof(struct cop));
    if(c==NULL){
        exit(EXIT_FAILURE);
    }

    c->nV=nV;
    c->vertici=(int*)calloc(nV, sizeof(int));
    if(c->vertici==NULL){
        exit(EXIT_FAILURE);
    }
    return c;
}




void COPERTURAmarca(Copertura c, int vertice){
    if(vertice>=0 && vertice<c->nV)
        c->vertici[vertice]=COPERTO;
    return;
}




void COPERTURAsmarca(Copertura c, int vertice){
    if(vertice>=0 && vertice<c->nV)
        c->vertici[vertice]=SCOPERTO;
    return;
}




Boolean COPERTURAhaIntersezione(Copertura c1, Copertura c2){
    int i, nV;

    nV=c1->nV;
    for(i=0; i<nV; i++){
        if(c1->vertici[i]==COPERTO && c2->vertici[i]==COPERTO)
            return VERO;
    }
    return FALSO;
}




Copertura COPERTURAgetUnione(Copertura *vett, int dim, int escluso){
    Copertura unione;
    int i, vertice, nV;

    if(dim==0 || vett==NULL)
        return NULL;

    nV=vett[0]->nV;
    unione=COPERTURAinit(nV);

    for(vertice=0; vertice<nV; vertice++){
        for(i=0; i<dim; i++){
            if(i==escluso){
                continue;
            }
            if(vett[i]->vertici[vertice]==COPERTO){
                unione->vertici[vertice]=COPERTO;
                break;
            }
        }
    }
    return unione;
}




int COPERTURAgetNumVertici(Copertura c){
    return c->nV;
}




void COPERTURAfree(Copertura c){
    if(c!=NULL){
        if(c->vertici!=NULL){
            free(c->vertici);
        }
        free(c);
    }
    return;
}
