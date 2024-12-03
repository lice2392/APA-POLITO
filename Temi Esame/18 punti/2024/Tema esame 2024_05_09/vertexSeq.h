#ifndef VERTEXSEQ_H_INCLUDED
#define VERTEXSEQ_H_INCLUDED
#include "vertice.h"

typedef struct sequenza *vertexSeq;

vertexSeq VERTEXSEQinit();
vertexSeq VERTEXSEQread(FILE *fp);
void VERTEXSEQinsert(vertexSeq vs, Vertice v);
int VERTEXSEQsearch(vertexSeq vs, Vertice v);
Vertice VERTEXSEQgetByIndex(vertexSeq vs, int index);
int VERTEXSEQgetSize(vertexSeq vs);
void VERTEXSEQprint(vertexSeq vs, FILE *f);
void VERTEXSEQfree(vertexSeq vs);

#endif // VERTEXSEQ_H_INCLUDED
