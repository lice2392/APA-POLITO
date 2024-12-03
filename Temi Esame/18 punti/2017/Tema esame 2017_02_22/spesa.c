#include "spesa.h"

Spesa SPESAread(Prodotti p, FILE *f, int totProdotti){
    Spesa s;
    char prod[MAXC];
    int i, qta, idP;

    s.maxProdotti=totProdotti;
    fscanf(f, "%d", &s.nProdotti);

    s.prodotti=(int *)malloc(totProdotti*sizeof(int));
    if(s.prodotti==NULL) exit(EXIT_FAILURE);

    s.quantita=(int *)malloc(totProdotti*sizeof(int));
    if(s.quantita==NULL) exit(EXIT_FAILURE);

    for(i=0; i<totProdotti; i++){
        s.prodotti[i]=-1;
        s.quantita[i]=-1;
    }

    for(i=0; i<s.nProdotti; i++){
        fscanf(f, "%s %d", prod, &qta);
        idP=PRODOTTIsearch(p, prod);
        if(idP!=-1){
            s.prodotti[idP]=1;
            s.quantita[idP]=qta;
        }
    }
    return s;
}




void SPESAprint(Prodotti p, Spesa s, FILE *f){
    Prodotto *pr;
    int i;

    for(i=0; i<s.maxProdotti; i++){
        if(s.prodotti[i]==1){
            pr=PRODOTTIgetProdottoByIndex(p, i);
            fprintf(f, "%s %d\n", pr->nome, s.quantita[i]);
        }
    }
    return;
}




void SPESAclear(Spesa *s){
    if(s->prodotti!=NULL){
        free(s->prodotti);
    }
    if(s->quantita!=NULL){
        free(s->quantita);
    }
    return;
}
