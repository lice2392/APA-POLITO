#include "famiglia.h"

Famiglia FAMIGLIAread(Koalas k, FILE *f, int N, int S, int idFamiglia){
    Famiglia fa;
    int i, idK;
    char koala[MAXC];
    Koala *ko;

    fscanf(f, "%s %d", fa.nome, &fa.nKoalas);

    fa.totFamiglie=S;

    fa.totK=N;

    fa.koalas=(int *)calloc(N, sizeof(int));
    if(fa.koalas==NULL) exit(EXIT_FAILURE);

    fa.nemici=(int *)calloc(S, sizeof(int));
    if(fa.nemici==NULL) exit(EXIT_FAILURE);

    fa.nNemici=0;

    for(i=0; i<fa.nKoalas; i++){
        fscanf(f, "%s", koala);
        idK=KOALASsearch(k, koala);
        fa.koalas[idK]=1;
        ko=KOALASgetKoalaByIndex(k, idK);
        KOALAaddFamiglia(ko, idFamiglia);
    }

    return fa;
}




void FAMIGLIAaddNemico(Famiglia *f, int nemico){
    f->nemici[nemico]=1;
    (f->nNemici)++;
    return;
}




void FAMIGLIAclear(Famiglia *f){
    if(f->koalas!=NULL){
        free(f->koalas);
    }
    if(f->nemici!=NULL){
        free(f->nemici);
    }
    return;
}
