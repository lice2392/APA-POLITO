#ifndef TESSERE_H_INCLUDED
#define TESSERE_H_INCLUDED
#include "tessera.h"

typedef struct tessere *Tessere;

Tessere TESSEREinit(int N);
void TESSEREaddTessera(Tessere t, Tessera te);
void TESSEREprint(Tessere t, FILE *f);
Tessera TESSEREgetTessera(Tessere t, int index);
int TESSEREgetNumTessere(Tessere t);
int TESSEREsearchTessera(Tessere t, Tessera te);
void TESSEREfree(Tessere t);

#endif // TESSERE_H_INCLUDED
