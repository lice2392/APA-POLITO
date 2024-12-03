#ifndef FAMIGLIA_H_INCLUDED
#define FAMIGLIA_H_INCLUDED
#include "koalas.h"

typedef struct{
    char nome[MAXC];
    int *koalas;
    int nKoalas, totK;
    int *nemici;
    int totFamiglie, nNemici;
}Famiglia;

Famiglia FAMIGLIAread(Koalas k, FILE *f, int N, int S, int idFamiglia);
void FAMIGLIAaddNemico(Famiglia *f, int nemico);
void FAMIGLIAclear(Famiglia *f);

#endif // FAMIGLIA_H_INCLUDED
