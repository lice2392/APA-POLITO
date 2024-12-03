#include "attivita.h"

Attivita ATTIVITAread(FILE *f){
    Attivita a;

    fscanf(f, "%s %d %d %d%*c", a.nome, &a.tempoInizio, &a.durata, &a.profitto);

    a.tempoFine=a.tempoInizio+a.durata;

    a.nPrecedenze=0;

    a.requisitoPrecedenza=FALSO;
    return a;
}




void ATTIVITAaddPrecedenza(Attivita *a, int attivita){
    a->precedenze[a->nPrecedenze]=attivita;
    (a->nPrecedenze)++;
    return;
}
