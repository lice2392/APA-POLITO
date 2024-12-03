#ifndef SCACCHIERA_H_INCLUDED
#define SCACCHIERA_H_INCLUDED
#include "tessere.h"
#include "mosse.h"

typedef struct scacchiera *Scacchiera;

Scacchiera SCACCHIERAinit(int dim);
Scacchiera SCACCHIERAread(FILE *f, Tessere *t);
void SCACCHIERAprint(Scacchiera s, Tessere t, FILE *f);
Boolean SCACCHIERAverificaMosse(Scacchiera s, Tessere t, Mosse m, int M, char *messaggio);
void SCACCHIERAmuoviTessere(Scacchiera s, Mossa m);
Boolean SCACCHIERAverificaPuzzle(Scacchiera s, Tessere t);
void SCACCHIERAsearch(Scacchiera s, Tessere t, int M);
void SCACCHIERAreset(Scacchiera s, Mosse m);
void SCACCHIERAfree(Scacchiera s);

#endif // SCACCHIERA_H_INCLUDED
