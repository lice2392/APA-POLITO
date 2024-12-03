#ifndef ATTIVITA_H_INCLUDED
#define ATTIVITA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAXC 21
#define MAXR 2

typedef enum{VERO, FALSO}Boolean;

typedef struct{
    int tempoInizio, tempoFine, durata, profitto;
    char nome[MAXC];
    int precedenze[MAXR];
    int nPrecedenze;
    Boolean requisitoPrecedenza;
}Attivita;


Attivita ATTIVITAread(FILE *f);
void ATTIVITAaddPrecedenza(Attivita *a, int val);

#endif // ATTIVITA_H_INCLUDED
