#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED
#define MAX 11
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[MAX];
}Persona;

Persona PERSONAread(FILE *f);
void PERSONAprint(Persona p, FILE *f);
Persona PERSONAcrea(char *nome);

#endif // PERSONA_H_INCLUDED
