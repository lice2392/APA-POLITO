#ifndef PRODOTTO_H_INCLUDED
#define PRODOTTO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAXC 21

typedef struct{
    char nome[MAXC];
    int prezzo;
    int *offerte;
    int nOfferte, maxOfferte;
}Prodotto;

Prodotto PRODOTTOread(FILE *f, int totOfferte);
void PRODOTTOaddOfferta(Prodotto *p, int offerta);
int *PRODOTTOgetOfferte(Prodotto p);
void PRODOTTOclear(Prodotto *p);

#endif // PRODOTTO_H_INCLUDED
