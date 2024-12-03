#ifndef AZIENDE_H_INCLUDED
#define AZIENDE_H_INCLUDED
#include "azienda.h"

typedef struct aziende *Aziende;

Aziende AZIENDEinit(int dim);
Aziende AZIENDEread(FILE *f, int N);
void AZIENDEprint(Aziende a, FILE *f);
int AZIENDEsearch(Aziende a, Azienda az);
void AZIENDEfree(Aziende a);

#endif // AZIENDE_H_INCLUDED
