#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include <string.h>
#include "vertice.h"

typedef struct table *ST;

ST STinit(int N);
void STinsert(ST st, Vertice v);
int STsearch(ST st, char *nome, int val);
Vertice STgetByIndex(ST st, int index);
void STfree(ST st);

#endif // ST_H_INCLUDED
