#include "aziende.h"

struct aziende{
    Azienda *aziende;
    int maxEl, dim;
};




Aziende AZIENDEinit(int dim){
    Aziende a;

    a=(Aziende)malloc(sizeof(struct aziende));
    if(a==NULL) exit(EXIT_FAILURE);

    a->maxEl=dim;

    a->dim=0;

    a->aziende=(Azienda*)malloc(dim*sizeof(Azienda));
    if(a->aziende==NULL) exit(EXIT_FAILURE);

    return a;
}




Aziende AZIENDEread(FILE *f, int N){
    Aziende a;
    int i, j;

    a=AZIENDEinit(N);

    for(i=0; i<N; i++){
        a->aziende[i]=AZIENDAread(f);
        a->dim++;
        for(j=0; j<N; j++){
            fscanf(f, "%*s");
        }
    }
    return a;
}




void AZIENDEprint(Aziende a, FILE *f){
    int i;

    for(i=0; i<a->dim; i++){
        AZIENDAprint(a->aziende[i], f);
        fprintf(f, "\n");
    }
    return;
}




int AZIENDEsearch(Aziende a, Azienda az){
    int i;

    for(i=0; i<a->dim; i++){
        if(strcmp(az.nome, a->aziende[i].nome)==0)
            return i;
    }
    return -1;
}




void AZIENDEfree(Aziende a){
    if(a!=NULL){
        if(a->aziende!=NULL){
            free(a->aziende);
        }
        free(a);
    }
    return;
}
