#include "elenco.h"

struct cities{
    Citta *citta;
    int N;
};


Elenco ELENCOinit(int N){
    Elenco e;

    e=(Elenco)malloc(sizeof(struct cities));
    if(e==NULL){
        exit(EXIT_FAILURE);
    }

    e->N=N;

    e->citta=(Citta*)malloc(N*sizeof(Citta));
    if(e->citta==NULL){
        exit(EXIT_FAILURE);
    }
    return e;
}




Elenco ELENCOread(FILE *f, int N){
    Elenco e;
    int i;

    e=ELENCOinit(N);

    for(i=0; i<N; i++){
        e->citta[i]=CITTAread(f);
    }
    return e;
}




Citta ELENCOgetCittaByIndex(Elenco e, int index){
    return e->citta[index];
}




int ELENCOsearch(Elenco e, Citta c){
    for(int i=0; i<e->N; i++){
        if(strcmp(e->citta[i].nome, c.nome)==0)
            return i;
    }
    return -1;
}




int ELENCOgetNumCitta(Elenco e){
    return e->N;
}




void ELENCOprint(Elenco e, FILE *f){
    for(int i=0; i<e->N; i++){
        CITTAprint(e->citta[i], f);
        fprintf(f, "%s", (i==e->N-1)?"\n":", ");
    }
    return;
}




void ELENCOfree(Elenco e){
    if(e!=NULL){
        if(e->citta!=NULL){
            for(int i=0; i<e->N; i++){
                CITTAclear(e->citta[i]);
            }
            free(e);
        }
        free(e);
    }
}
