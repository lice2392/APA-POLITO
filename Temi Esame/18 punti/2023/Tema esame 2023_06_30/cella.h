#ifndef CELLA_H_INCLUDED
#define CELLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int riga, colonna;
}Cella;

Cella CELLAread(FILE *f);
void CELLAprint(Cella c, FILE *f);
Cella CELLAcreate(int riga, int colonna);

#endif // CELLA_H_INCLUDED
