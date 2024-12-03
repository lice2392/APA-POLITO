#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "ST.h"

typedef enum{VERO, FALSO}Boolean;

typedef struct grafo *Grafo;

Grafo GRAFOinit();
Grafo GRAFOload(FILE *f);
Boolean GRAFOcheck(Grafo g, FILE *f);
void GRAFOsearch(Grafo g);
void GRAFOfree(Grafo g);

#endif // GRAFO_H_INCLUDED
