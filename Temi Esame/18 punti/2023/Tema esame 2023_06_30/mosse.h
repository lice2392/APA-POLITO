#ifndef MOSSE_H_INCLUDED
#define MOSSE_H_INCLUDED
#include "mossa.h"

typedef struct mosse *Mosse;

Mosse MOSSEinit(int dim);
Mosse MOSSEread(FILE *f);
void MOSSEprint(Mosse m, FILE *f);
Mossa MOSSEgetMossa(Mosse m, int index);
int MOSSEgetNumMosse(Mosse m);
void MOSSEaddMossa(Mosse m, Mossa mo);
void MOSSEeliminaMossa(Mosse m);
void MOSSEfree(Mosse m);


#endif // MOSSE_H_INCLUDED
