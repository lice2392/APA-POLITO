#include "offerta.h"

Offerta OFFERTAread(Prodotti p, FILE *f, int idO, int totProdotti){
    Offerta o;
    char prod[MAXC];
    int i, idP, qta;

    fscanf(f, "%s %d %d", o.nome, &o.prezzo, &o.nProdotti);

    o.maxProdotti=totProdotti;

    o.prodotti=(int*)malloc(totProdotti*sizeof(int));
    if(o.prodotti==NULL) exit(EXIT_FAILURE);

    o.quantita=(int*)malloc(totProdotti*sizeof(int));
    if(o.quantita==NULL) exit(EXIT_FAILURE);

    for(i=0; i<totProdotti; i++){
        o.prodotti[i]=-1;
        o.quantita[i]=-1;
    }

    for(i=0; i<o.nProdotti; i++){
        fscanf(f, "%s %d", prod, &qta);
        idP=PRODOTTIsearch(p, prod);
        o.prodotti[idP]=1;
        o.quantita[idP]=qta;
        PRODOTTOaddOfferta(PRODOTTIgetProdottoByIndex(p, idP), idO);
    }
    return o;
}




int *OFFERTAgetProdottiComuni(Offerta o1, Offerta o2){
    int *prodottiComuni, i;

    prodottiComuni=(int*)malloc(o1.maxProdotti*sizeof(int));
    if(prodottiComuni==NULL) exit(EXIT_FAILURE);

    for(i=0; i<o1.maxProdotti; i++){
        prodottiComuni[i]=-1;
    }

    for(i=0; i<o1.maxProdotti; i++){
        if(o1.prodotti[i]==1 && o2.prodotti[i]==1){
            prodottiComuni[i]=1;
        }
    }
    return prodottiComuni;
}




void OFFERTAclear(Offerta *o){
    if(o->prodotti!=NULL){
        free(o->prodotti);
    }
    if(o->quantita!=NULL){
        free(o->quantita);
    }
    return;
}
