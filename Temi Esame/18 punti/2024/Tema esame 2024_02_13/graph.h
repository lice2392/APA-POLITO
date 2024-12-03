#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <ctype.h>
#include "ST.h"
#include "nomi.h"

typedef enum{VERO, FALSO}Boolean;

typedef struct grafo *Graph;

Graph GRAPHinit(int V);
Graph GRAPHload(FILE *f);
Boolean GRAPHcheckString(Graph g, char *stringa);
void GRAPHbestPath(Graph g, int M);
void GRAPHfree(Graph g);

#endif // GRAPH_H_INCLUDED
