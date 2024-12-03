#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "st.h"

typedef struct grafo *Graph;

Graph GRAPHinit(int V);
Graph GRAPHload(FILE *f);
void GRAPHinsertEdge(Graph g, int id1, int id2, int wt);
void GRAPHprint(Graph g, FILE *f);
int GRAPHgetNumVertici(Graph g);
int GRAPHgetIndexVertice(Graph g, Vertice v);
Vertice GRAPHgetVertice(Graph g, int index);
int GRAPHgetPesoArco(Graph g, int v, int w);
void GRAPHfree(Graph g);

#endif // GRAFO_H_INCLUDED
