#ifndef CLIENTI_H_INCLUDED
#define CLIENTI_H_INCLUDED
#include "cliente.h"

typedef struct clienti *Clienti;

Clienti CLIENTIinit();
Clienti CLIENTIread(FILE *f);
Cliente CLIENTIgetCliente(Clienti c, int index);
int CLIENTIsearch(Clienti c, char *id);
int CLIENTIgetNumClienti(Clienti c);
void CLIENTIprint(Clienti c, FILE *f);
void CLIENTIinsertCliente(Clienti c, Cliente cl);
void CLIENTIfree(Clienti c);

#endif // CLIENTI_H_INCLUDED
