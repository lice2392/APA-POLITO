#ifndef KOALA_H_INCLUDED
#define KOALA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAXC 21

typedef struct{
    char nome[MAXC];
    int nEucalipti, totE;
    int *eucalipti;
    int famiglia;
}Koala;

Koala KOALAread(FILE *f, int T);
void KOALAaddFamiglia(Koala *k, int famiglia);
void KOALAclear(Koala *k);

#endif // KOALA_H_INCLUDED
