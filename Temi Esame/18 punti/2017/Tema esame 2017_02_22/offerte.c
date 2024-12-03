#include "offerte.h"

struct offs{
    Offerta *offerte;
    int dim;
};


Offerte OFFERTEinit(int dim){
    Offerte p;

    p=(Offerte)malloc(sizeof(struct offs));
    if(p==NULL) exit(EXIT_FAILURE);

    p->dim=dim;

    p->offerte=(Offerta*)malloc(dim*sizeof(Offerta));
    if(p->offerte==NULL) exit(EXIT_FAILURE);

    return p;
}




Offerte OFFERTEread(Prodotti p, FILE *f, int nOfferte, int nProdotti){
    Offerte o;
    int i;

    o=OFFERTEinit(nOfferte);

    for(i=0; i<nOfferte; i++){
        o->offerte[i]=OFFERTAread(p, f, i, nProdotti);
    }
    return o;
}




int OFFERTEsearch(Offerte o, char *nome){
    int i;

    for(i=0; i<o->dim; i++){
        if(strcmp(o->offerte[i].nome, nome)==0){
            return i;
        }
    }
    return -1;
}




Offerta *OFFERTEgetOffertaByIndex(Offerte o, int index){
    return &o->offerte[index];
}




int OFFERTEgetDim(Offerte o){
    return o->dim;
}




int *OFFERTEgetProdottiComuniOfferte(Offerte o, char *offerta1, char *offerta2){
    int idO1, idO2;

    idO1=OFFERTEsearch(o, offerta1);
    idO2=OFFERTEsearch(o, offerta2);
    if(idO1==-1 || idO2==-1){
        return NULL;
    }
    return OFFERTAgetProdottiComuni(o->offerte[idO1], o->offerte[idO2]);
}




void OFFERTEfree(Offerte o){
    int i;

    if(o!=NULL){
        if(o->offerte!=NULL){
            for(i=0; i<o->dim; i++){
                OFFERTAclear(&o->offerte[i]);
            }
            free(o->offerte);
        }
        free(o);
    }
    return;
}
