#ifndef REGIONE_H_INCLUDED
#define REGIONE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

typedef struct{
    int riga, colonna, base, altezza;
}Regione;

Regione REGIONEcrea(int riga, int colonna, int base, int altezza);
Regione REGIONEsetNull();
Regione REGIONEread(FILE *f);
Boolean REGIONEisNull(Regione r);
void REGIONEprint(Regione r, FILE *f);

#endif // REGIONE_H_INCLUDED
