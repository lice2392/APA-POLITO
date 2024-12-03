#ifndef KOALAS_H_INCLUDED
#define KOALAS_H_INCLUDED
#include <string.h>
#include "koala.h"

typedef struct koalas *Koalas;

Koalas KOALASinit(int N);
Koalas KOALASread(FILE *f, int N, int T);
int KOALASsearch(Koalas k, char *nome);
Koala *KOALASgetKoalaByIndex(Koalas k, int index);
void KOALASfree(Koalas k);

#endif // KOALAS_H_INCLUDED
