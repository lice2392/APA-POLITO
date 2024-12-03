#include "alberghi.h"
#include <limits.h>

struct alberghi{
    Albergo *alberghi;
    int N;
};




Alberghi ALBERGHIinit(int N){
    Alberghi a;

    a=(Alberghi)malloc(sizeof(struct alberghi));
    if(a==NULL) exit(EXIT_FAILURE);

    a->N=N;

    a->alberghi=(Albergo*)malloc(N*sizeof(Albergo));
    if(a->alberghi==NULL) exit(EXIT_FAILURE);

    return a;
}




Alberghi ALBERGHIcrea(int N, int X, int *M){
    Alberghi a;
    int i;

    a=ALBERGHIinit(N);

    for(i=0; i<N; i++){
        a->alberghi[i]=ALBERGOinit(M[i], X);
    }
    return a;
}




Albergo ALBERGHIgetAlbergo(Alberghi a, int index){
    return a->alberghi[index];
}




int ALBERGHIgetNumAlberghi(Alberghi a){
    return a->N;
}




void ALBERGHIreset(Alberghi a){
    int i;

    for(i=0; i<a->N; i++){
        ALBERGOreset(&a->alberghi[i]);
    }
    return;
}




float ALBERGHIcalcoloFunzioneUtilizzoStrutture(Alberghi al, int a, int b){
    int i;
    float r_i, somma, max, min, ret;

    max=0;
    min=INT_MAX;
    somma=0;

    for(i=0; i<al->N; i++){
        r_i=ALBERGOgetRiempimentoMedio(al->alberghi[i]);
        if(r_i>max){
            max=r_i;
        }
        if(r_i<min){
            min=r_i;
        }
        somma+=r_i;
    }

    ret= (a*somma) - (((max-min)/max)*b);
    return ret;
}




void ALBERGHIfree(Alberghi a){
    int i;
    if(a!=NULL){
        if(a->alberghi!=NULL){
            for(i=0; i<a->N; i++){
                ALBERGOclear(&a->alberghi[i]);
            }
            free(a->alberghi);
        }
        free(a);
    }
    return;
}
