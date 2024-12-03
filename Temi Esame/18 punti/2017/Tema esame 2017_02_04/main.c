#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    FILE *fg, *fp;
    Grafo g;

    fg=fopen("grafo.txt", "r");
    if(fg==NULL) exit(EXIT_FAILURE);

    g=GRAFOload(fg);

    fp=fopen("proposta_ok.txt", "r");
    if(fp==NULL) exit(EXIT_FAILURE);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(GRAFOcheck(g, fp)==VERO){
        printf("La soluzione proposta e' una cricca massimale.\n\n");
    }
    else{
       printf("La soluzione proposta non e' una cricca massimale.\n\n");
    }

    printf("---PROBLEMA DI RICERCA---\n");
    GRAFOsearch(g);

    fclose(fg);
    fclose(fp);
    GRAFOfree(g);
    return 0;
}
