#ifndef FAMIGLIE_H_INCLUDED
#define FAMIGLIE_H_INCLUDED
#include "famiglia.h"

typedef struct famiglie *Famiglie;

Famiglie FAMIGLIEinit(int S);
Famiglie FAMIGLIEread(Koalas k, FILE *f, int N, int S);
void FAMIGLIEreadNemici(Famiglie fa, FILE *f);
int FAMIGLIEsearch(Famiglie f, char *nome);
Famiglia *FAMIGLIEgetFamigliaByIndex(Famiglie f, int index);
void FAMIGLIEfree(Famiglie f);

#endif // FAMIGLIE_H_INCLUDED
