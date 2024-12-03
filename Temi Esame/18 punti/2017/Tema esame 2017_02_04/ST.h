#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include "vertice.h"

typedef struct tabella *ST;

ST STinit(int maxN);
void STinsert(ST st, Vertice v);
Vertice STgetByIndex(ST st, int index);
int STsearch(ST st, char *nome);
void STfree(ST st);

#endif // ST_H_INCLUDED
