#include "koala.h"


Koala KOALAread(FILE *f, int T){
    Koala k;
    int i, idE;

    fscanf(f, "%s %d%*c", k.nome, &k.nEucalipti);

    k.totE=T;

    k.eucalipti=(int*)calloc(T, sizeof(int));
    if(k.eucalipti==NULL) exit(EXIT_FAILURE);

    for(i=0; i<k.nEucalipti; i++){
        fscanf(f, "%d%*c", &idE);
        k.eucalipti[idE]=1;
    }
    return k;
}




void KOALAaddFamiglia(Koala *k, int famiglia){
    k->famiglia=famiglia;
    return;
}




void KOALAclear(Koala *k){
    if(k->eucalipti!=NULL){
        free(k->eucalipti);
    }
    return;
}
