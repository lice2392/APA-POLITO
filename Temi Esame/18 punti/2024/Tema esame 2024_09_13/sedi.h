#ifndef SEDI_H_INCLUDED
#define SEDI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "elenco.h"

typedef struct pronto *Sedi;

Sedi SEDIinit(int M);
Sedi SEDIread(char *nomeFile, Elenco e);
void SEDIprint(Sedi s, FILE *f, Elenco e);
int SEDIgetSede(Sedi s, int index);
int SEDIgetNumSedi(Sedi s);
void SEDIfree(Sedi s);

#endif // SEDI_H_INCLUDED
