#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

typedef enum{VERO, FALSO}Boolean;

typedef struct{
    char id[MAX];
    int giornoArrivo;
    int giorniPernottamento;
}Cliente;

Cliente CLIENTEread(FILE *f);
void CLIENTEprint(Cliente c, FILE *f);
Cliente CLIENTEsetNull();
Boolean CLIENTEisNull(Cliente c);

#endif // CLIENTE_H_INCLUDED
