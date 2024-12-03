#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#include "bool.h"

typedef enum{UGUALE, DIVERSO}Simbolo;

typedef struct{
    char nome[MAX];
}Vertice;

Vertice VERTICEread(FILE *f);
Vertice VERTICEcrea(char *nome);
Vertice VERTICEsetNull();
Boolean VERTICEisNull(Vertice v);
Simbolo VERTICEcompare(Vertice v1, Vertice v2);
void VERTICEprint(Vertice v, FILE *f);

#endif // VERTICE_H_INCLUDED
