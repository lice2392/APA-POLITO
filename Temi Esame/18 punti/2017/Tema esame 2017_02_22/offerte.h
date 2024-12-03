#ifndef OFFERTE_H_INCLUDED
#define OFFERTE_H_INCLUDED
#include "offerta.h"

typedef struct offs *Offerte;

Offerte OFFERTEinit(int dim);
Offerte OFFERTEread(Prodotti p, FILE *f, int nOfferte, int nProdotti);
int OFFERTEsearch(Offerte o, char *nome);
Offerta *OFFERTEgetOffertaByIndex(Offerte o, int index);
int OFFERTEgetDim(Offerte o);
int *OFFERTEgetProdottiComuniOfferte(Offerte o, char *offerta1, char *offerta2);
void OFFERTEfree(Offerte o);

#endif // OFFERTE_H_INCLUDED
