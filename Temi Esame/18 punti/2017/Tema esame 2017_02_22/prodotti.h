#ifndef PRODOTTI_H_INCLUDED
#define PRODOTTI_H_INCLUDED
#include "prodotto.h"
#include <string.h>

typedef struct prods *Prodotti;

Prodotti PRODOTTIinit(int dim);
Prodotti PRODOTTIread(FILE *f, int nProdotti, int nOfferte);
int PRODOTTIsearch(Prodotti p, char *nome);
Prodotto *PRODOTTIgetProdottoByIndex(Prodotti p, int index);
int *PRODOTTIgetOfferteProdotto(Prodotti p, char *prodotto);
int PRODOTTIgetDim(Prodotti p);
void PRODOTTIfree(Prodotti p);

#endif // PRODOTTI_H_INCLUDED
