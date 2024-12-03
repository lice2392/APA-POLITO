#ifndef AZIENDA_H_INCLUDED
#define AZIENDA_H_INCLUDED
#define MAX 11
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[MAX];
}Azienda;

Azienda AZIENDAread(FILE *f);
void AZIENDAprint(Azienda a, FILE *f);
Azienda AZIENDAcrea(char *nome);

#endif // AZIENDA_H_INCLUDED
