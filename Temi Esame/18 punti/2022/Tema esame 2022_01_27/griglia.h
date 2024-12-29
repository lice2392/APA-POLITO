#ifndef GRIGLIA_H_INCLUDED
#define GRIGLIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#define BIANCO 0
#define NERO 1

typedef struct griglia *Griglia;

Griglia GRIGLIAinit(int nr, int nc);
Griglia GRIGLIAread(FILE *f);
void GRIGLIAfillRegione(Griglia g, int rI, int cI, int base, int altezza, int value);
void GRIGLIAdeleteRegione(Griglia g, int rI, int cI, int base, int altezza);
Boolean GRIGLIAcheckRegione(Griglia g, int rI, int cI, int base, int altezza);
int GRIGLIAareaBianco(Griglia g);
void GRIGLIAreset(Griglia g);
int GRIGLIAgetMaxAreaBianco(Griglia g, int rI, int cI);
int GRIGLIAgetNumRighe(Griglia g);
int GRIGLIAgetNumColonne(Griglia g);
int GRIGLIAgetCella(Griglia g, int riga, int colonna);
void GRIGLIAprint(Griglia g, FILE *f);
void GRIGLIAcopia(Griglia g1, Griglia g2);
void GRIGLIAfree(Griglia g);

#endif // GRIGLIA_H_INCLUDED
