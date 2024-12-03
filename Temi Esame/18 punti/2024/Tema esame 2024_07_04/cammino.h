#ifndef CAMMINO_H_INCLUDED
#define CAMMINO_H_INCLUDED
#include "copertura.h"
#include "grafo.h"

typedef struct cammino *GraphPath;

GraphPath GRAPHPATHinit(int nV);
GraphPath GRAPHPATHread(Graph g, FILE *f);
void GRAPHPATHaddVertice(GraphPath p, int vertice);
Copertura GRAPHPATHgetCopertura(GraphPath p);
int GRAPHPATHgetFirst(GraphPath p);
int GRAPHPATHgetLast(GraphPath p);
Boolean GRAPHPATHisEmpty(GraphPath p);
void GRAPHPATHprint(GraphPath p, Graph g, FILE *f);
Boolean GRAPHPATHisCamminoSemplice(GraphPath p);
int GRAPHPATHgetPeso(GraphPath p);
int GRAPHPATHgetNumVertici(GraphPath p);
Boolean GRAPHPATHisCiclo(GraphPath p);
void GRAPHPATHfree(GraphPath p);

#endif // CAMMINO_H_INCLUDED
