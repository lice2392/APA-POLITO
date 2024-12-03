#ifndef NOMI_H_INCLUDED
#define NOMI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "nome.h"

typedef struct names *Nomi;

Nomi NOMIinit();
void NOMIinsert(Nomi n, Nome nome);
int NOMIsearch(Nomi n, char *nome);
int NOMIgetCount(Nomi n);
void NOMIfree(Nomi n);

#endif // NOMI_H_INCLUDED
