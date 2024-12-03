#include "prodotto.h"

Prodotto PRODOTTOread(FILE *f, int totOfferte){
    Prodotto p;
    int i;

    fscanf(f, "%s %d", p.nome, &p.prezzo);

    p.maxOfferte=totOfferte;

    p.offerte=(int *)malloc(totOfferte*sizeof(int));
    if(p.offerte==NULL) exit(EXIT_FAILURE);

    for(i=0; i<totOfferte; i++){
        p.offerte[i]=-1;
    }

    p.nOfferte=0;
    return p;
}




void PRODOTTOaddOfferta(Prodotto *p, int offerta){
    p->offerte[offerta]=1;
    (p->nOfferte)++;
    return;
}




int *PRODOTTOgetOfferte(Prodotto p){
    return p.offerte;
}




void PRODOTTOclear(Prodotto *p){
    if(p->offerte!=NULL){
        free(p->offerte);
    }
    return;
}
