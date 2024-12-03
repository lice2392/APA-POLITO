#ifndef DISTANZE_H_INCLUDED
#define DISTANZE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct dist *Distanze;

Distanze DISTANZEinit(int N);
Distanze DISTANZEread(FILE *f, int N);
int DISTANZEgetDistanza(Distanze d, int riga, int colonna);
int DISTANZEgetNumCitta(Distanze d);
void DISTANZEprint(Distanze d, FILE *f);
void DISTANZEfree(Distanze d);

#endif // DISTANZE_H_INCLUDED
