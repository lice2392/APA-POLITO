#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef enum{VERO, FALSO}Boolean;

typedef struct grafo *Grafo;

Grafo GRAFOinit(int V);
Grafo GRAFOread(FILE *f);
void GRAFOinsertE(Grafo g, int id1, int id2, int w);
Boolean GRAFOverifica(char *nomeFile, Grafo g, int k);
void GRAFOsolve(Grafo g, int k);
void GRAFOfree(Grafo g);


#endif // GRAFO_H_INCLUDED
