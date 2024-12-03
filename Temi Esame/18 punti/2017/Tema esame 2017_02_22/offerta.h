#ifndef OFFERTA_H_INCLUDED
#define OFFERTA_H_INCLUDED
#include "prodotti.h"

typedef struct{
    char nome[MAXC];
    int prezzo;
    int *prodotti, *quantita;
    int nProdotti, maxProdotti;
}Offerta;

Offerta OFFERTAread(Prodotti p, FILE *f, int idO, int totProdotti);
int *OFFERTAgetProdottiComuni(Offerta o1, Offerta o2);
void OFFERTAclear(Offerta *o);

#endif // OFFERTA_H_INCLUDED
