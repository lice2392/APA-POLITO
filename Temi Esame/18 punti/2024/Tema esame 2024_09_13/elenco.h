#ifndef ELENCO_H_INCLUDED
#define ELENCO_H_INCLUDED
#include "citta.h"

typedef struct cities *Elenco;

Elenco ELENCOinit(int N);
Elenco ELENCOread(FILE *f, int N);
Citta ELENCOgetCittaByIndex(Elenco e, int index);
int ELENCOsearch(Elenco e, Citta c);
int ELENCOgetNumCitta(Elenco e);
void ELENCOprint(Elenco e, FILE *f);
void ELENCOfree(Elenco e);

#endif // ELENCO_H_INCLUDED
