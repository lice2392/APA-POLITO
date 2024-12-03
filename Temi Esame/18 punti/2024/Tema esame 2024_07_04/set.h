#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
#include "cammino.h"

typedef struct set *GraphPathSet;

GraphPathSet GRAPHPATHSETinit();
GraphPathSet GRAPHPATHSETread(Graph g, FILE *f);
void GRAPHPATHSETprint(GraphPathSet ps, Graph g, FILE *f);
void GRAPHPATHSETaddCammino(GraphPathSet ps, GraphPath p);
Boolean GRAPHPATHSETcheck(GraphPathSet ps);
void GRAPHPATHSETbestPath(GraphPathSet ps, Graph g);
void GRAPHPATHSETfree(GraphPathSet ps);

#endif // SET_H_INCLUDED
