#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAX 21

typedef struct{
    char nome[MAX];
    int val;
}Vertice;

Vertice VERTICEread(FILE *f);
void VERTICEprint(Vertice v, FILE *f);

#endif // VERTICE_H_INCLUDED
