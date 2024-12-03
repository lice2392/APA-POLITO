#ifndef SERVIZI_H_INCLUDED
#define SERVIZI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "sedi.h"

typedef struct ass *Servizi;

Servizi SERVIZIinit(int N);
void SERVIZIassegna(Servizi s, int prontoS, int citta);
void SERVIZIprint(Servizi sv, Sedi s, FILE *f, Elenco e);
void SERVIZIfree(Servizi s);

#endif // SERVIZI_H_INCLUDED
