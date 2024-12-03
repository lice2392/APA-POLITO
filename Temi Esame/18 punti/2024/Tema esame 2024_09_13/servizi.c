#include "servizi.h"

struct ass{
    int *assegnazione;
    int N;
};


Servizi SERVIZIinit(int N){
    Servizi s;

    s=(Servizi)malloc(sizeof(struct ass));
    if(s==NULL){
        exit(EXIT_FAILURE);
    }
    s->N=N;
    s->assegnazione=(int*)malloc(N*sizeof(int));
    if(s->assegnazione==NULL){
        exit(EXIT_FAILURE);
    }
    return s;
}




void SERVIZIassegna(Servizi s, int prontoS, int citta){
    s->assegnazione[citta]=prontoS;
    return;
}




void SERVIZIprint(Servizi sv, Sedi s, FILE *f, Elenco e){
    int citta, prontoS, nSedi, sede;

    nSedi=SEDIgetNumSedi(s);

    for(sede=0; sede<nSedi; sede++){
        prontoS=SEDIgetSede(s, sede);
        fprintf(f, "Sede ");
        CITTAprint(ELENCOgetCittaByIndex(e, prontoS), f);
        fprintf(f, ": { ");
        for(citta=0; citta<sv->N; citta++){
            if(sv->assegnazione[citta]==prontoS && citta!=prontoS){
                CITTAprint(ELENCOgetCittaByIndex(e, citta), f);
                fprintf(f, " ");
            }
        }
        fprintf(f, "}\n");
    }
    return;
}




void SERVIZIfree(Servizi s){
    if(s!=NULL){
        if(s->assegnazione!=NULL)
            free(s->assegnazione);
        free(s);
    }
    return;
}
