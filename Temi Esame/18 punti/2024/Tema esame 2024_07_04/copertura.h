#ifndef COPERTURA_H_INCLUDED
#define COPERTURA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "bool.h"
#define COPERTO 1
#define SCOPERTO 0

typedef struct cop *Copertura;

Copertura COPERTURAinit(int nV);
void COPERTURAmarca(Copertura c, int vertice);
void COPERTURAsmarca(Copertura c, int vertice);
Boolean COPERTURAhaIntersezione(Copertura c1, Copertura c2);
Copertura COPERTURAgetUnione(Copertura *vett, int dim, int escluso);
int COPERTURAgetNumVertici(Copertura c);
void COPERTURAfree(Copertura c);

#endif // COPERTURA_H_INCLUDED
