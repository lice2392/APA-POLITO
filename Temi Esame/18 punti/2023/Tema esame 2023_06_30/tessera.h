#ifndef TESSERA_H_INCLUDED
#define TESSERA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef enum{VERO, FALSO}Boolean;
typedef enum{UGUALE, DIVERSO}Simboli;

typedef struct{
    int nord, sud, ovest, est;
}Tessera;

Tessera TESSERAread(FILE *f);
void TESSERAprint(Tessera t, FILE *f);
Boolean TESSERAisSorgenteODestinazione(Tessera t);
Boolean TESSERAisBuco(Tessera t);
Simboli TESSERAcompare(Tessera t1, Tessera t2);

#endif // TESSERA_H_INCLUDED
