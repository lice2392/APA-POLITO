#ifndef CITTA_H_INCLUDED
#define CITTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *nome;
}Citta;

Citta CITTAread(FILE *f);
void CITTAprint(Citta c, FILE *f);
void CITTAclear(Citta c);

#endif // CITTA_H_INCLUDED
