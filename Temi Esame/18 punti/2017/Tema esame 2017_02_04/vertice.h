#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

typedef struct{
    char nome[MAX];
}Vertice;

Vertice VERTICEcrea(char *nome);
void VERTICEprint(Vertice v, FILE *f);
Vertice VERTICEsetNull();

#endif // VERTICE_H_INCLUDED
