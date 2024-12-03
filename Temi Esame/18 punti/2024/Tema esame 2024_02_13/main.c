#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    Graph g;
    FILE *f;
    char stringa[]="saleoriganopeperoncino";
    int M=2;

    f=fopen("grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAPHload(f);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(GRAPHcheckString(g, stringa)==VERO){
        printf("La stringa '%s' rappresenta la concatenazione dei nomi associati ai nodi su un cammino nel grafo.\n\n", stringa);
    }
    else{
        printf("La stringa '%s' non rappresenta la concatenazione dei nomi associati ai nodi su un cammino nel grafo.\n\n", stringa);
    }

    printf("---PROBLEMA DI RICERCA---\n");
    GRAPHbestPath(g, M);

    GRAPHfree(g);
    fclose(f);
    return 0;
}
