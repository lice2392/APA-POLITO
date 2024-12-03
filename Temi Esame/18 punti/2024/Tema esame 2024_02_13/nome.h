#ifndef NOME_H_INCLUDED
#define NOME_H_INCLUDED
#define NMAX 21
#include <string.h>

typedef struct{
    char nome[NMAX];
}Nome;

Nome NOMEcreate(char *nome);

#endif // NOME_H_INCLUDED
