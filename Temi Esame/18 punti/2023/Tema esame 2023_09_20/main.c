#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    Grafo g;
    FILE *f;
    int k=2;

    f=fopen("grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAFOread(f);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(GRAFOverifica("proposta.txt", g, k)==VERO){
        printf("Soluzione valida.\n\n");
    }
    else
        printf("Soluzione non valida.\n\n");

    printf("---PROBLEMA DI RICERCA---\n");
    GRAFOsolve(g, k);
    return 0;
}
