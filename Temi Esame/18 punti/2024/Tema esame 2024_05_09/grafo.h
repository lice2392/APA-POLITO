#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "st.h"
#include "vertexSeq.h"

typedef struct grafo *Graph;

Graph GRAPHinit(int V);
Graph GRAPHload(FILE *f);
void GRAPHinsertEdge(Graph g, int id1, int id2, int wt);
int checkCommonPath(Graph g, vertexSeq p1, vertexSeq p2, int min);
void bestPath(Graph g, vertexSeq S1, vertexSeq S2);
void GRAPHfree(Graph g);

#endif // GRAFO_H_INCLUDED
