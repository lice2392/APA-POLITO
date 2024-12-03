#ifndef PERSONE_H_INCLUDED
#define PERSONE_H_INCLUDED
#include "persona.h"

typedef struct persone *Persone;

Persone PERSONEinit(int dim);
Persone PERSONEread(FILE *f, int N);
void PERSONEprint(Persone p, FILE *f);
int PERSONEsearch(Persone p, Persona pe);
void PERSONEfree(Persone p);

#endif // PERSONE_H_INCLUDED
