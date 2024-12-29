#ifndef COPERTURA_H_INCLUDED
#define COPERTURA_H_INCLUDED
#include "griglia.h"
#include "regione.h"

typedef struct copertura *Copertura;

Copertura COPERTURAinit(int maxD);
Copertura COPERTURAread(FILE *f);
void COPERTURAinsert(Copertura c, Regione r);
void COPERTURAdelete(Copertura c);
Boolean COPERTURAcheck(Copertura c, Griglia g, int *nRegioni, int areaBianco);
void COPERTURAsolve(Griglia g);
void COPERTURAprint(Copertura c, FILE *f);
void COPERTURAfree(Copertura c);

#endif // COPERTURA_H_INCLUDED
