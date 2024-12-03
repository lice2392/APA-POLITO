#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include "vertice.h"

typedef struct table *ST;

ST STinit(int maxEl);
void STinsert(ST s, Vertice v);
int STsearch(ST s, Vertice v);
Vertice STgetByIndex(ST s, int index);
void STfree(ST s);

#endif // ST_H_INCLUDED
