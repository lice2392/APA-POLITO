#include "prodotti.h"

struct prods{
    Prodotto *prodotti;
    int dim;
};


Prodotti PRODOTTIinit(int dim){
    Prodotti p;

    p=(Prodotti)malloc(sizeof(struct prods));
    if(p==NULL) exit(EXIT_FAILURE);

    p->dim=dim;

    p->prodotti=(Prodotto*)malloc(dim*sizeof(Prodotto));
    if(p->prodotti==NULL) exit(EXIT_FAILURE);

    return p;
}




Prodotti PRODOTTIread(FILE *f, int nProdotti, int nOfferte){
    Prodotti p;
    int i;

    p=PRODOTTIinit(nProdotti);

    for(i=0; i<nProdotti; i++){
        p->prodotti[i]=PRODOTTOread(f, nOfferte);
    }
    return p;
}




int PRODOTTIsearch(Prodotti p, char *nome){
    int i;

    for(i=0; i<p->dim; i++){
        if(strcmp(p->prodotti[i].nome, nome)==0){
            return i;
        }
    }
    return -1;
}




Prodotto *PRODOTTIgetProdottoByIndex(Prodotti p, int index){
    return &p->prodotti[index];
}




int *PRODOTTIgetOfferteProdotto(Prodotti p, char *prodotto){
    int idP=PRODOTTIsearch(p, prodotto);
    if(idP==-1){
        return NULL;
    }
    return PRODOTTOgetOfferte(p->prodotti[idP]);
}




int PRODOTTIgetDim(Prodotti p){
    return p->dim;
}




void PRODOTTIfree(Prodotti p){
    int i;

    if(p!=NULL){
        if(p->prodotti!=NULL){
            for(i=0; i<p->dim; i++){
                PRODOTTOclear(&p->prodotti[i]);
            }
            free(p->prodotti);
        }
        free(p);
    }
    return;
}
