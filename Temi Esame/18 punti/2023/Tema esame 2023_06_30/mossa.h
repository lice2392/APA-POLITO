#ifndef MOSSA_H_INCLUDED
#define MOSSA_H_INCLUDED
#include "cella.h"
#include <string.h>
#include <ctype.h>

typedef enum{NORD, SUD, OVEST, EST}Direzione;

typedef struct{
    Cella *tessereMosse;
    int nTessereMosse;
    Direzione direzione;
}Mossa;

Mossa MOSSAcrea(Direzione dir, Cella *tessere, int nTessereMosse);
Mossa MOSSAread(FILE *f);
void MOSSAprint(Mossa m, FILE *f);
void MOSSAclear(Mossa *m);

#endif // MOSSA_H_INCLUDED
