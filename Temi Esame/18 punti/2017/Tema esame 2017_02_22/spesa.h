#ifndef SPESA_H_INCLUDED
#define SPESA_H_INCLUDED
#include "prodotti.h"

typedef struct{
    int nProdotti, maxProdotti;
    int *prodotti, *quantita;
}Spesa;

Spesa SPESAread(Prodotti p, FILE *f, int totProdotti);
void SPESAprint(Prodotti p, Spesa s, FILE *f);
void SPESAclear(Spesa *s);

#endif // SPESA_H_INCLUDED
