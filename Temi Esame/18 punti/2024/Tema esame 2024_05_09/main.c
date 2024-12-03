#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

typedef enum{VERIFICA, RICERCA}Tipo;

int main()
{
    Graph g;
    FILE *f;
    Tipo problema;
    vertexSeq p1, p2, S1, S2;
    int min;

    f=fopen("file/grafo.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    g=GRAPHload(f);
    fclose(f);

    problema=VERIFICA;
    switch(problema){
        case VERIFICA:
            printf("---PROBLEMA DI VERIFICA---\n");

            f=fopen("file/check_corretto/cammino1.txt", "r");
            if(f==NULL) exit(EXIT_FAILURE);

            p1=VERTEXSEQread(f);
            fclose(f);

            f=fopen("file/check_corretto/cammino2.txt", "r");
            if(f==NULL) exit(EXIT_FAILURE);

            p2=VERTEXSEQread(f);
            fclose(f);

            printf("---P1---\n");
            VERTEXSEQprint(p1, stdout);
            printf("\n---P2---\n");
            VERTEXSEQprint(p2, stdout);

            min=2;
            if(checkCommonPath(g, p1, p2, min)==VERO){
                printf("\nI cammini sono corretti e hanno un sottocammino comune lungo almeno %d\n", min);
            }
            VERTEXSEQfree(p1);
            VERTEXSEQfree(p2);
            break;


        case RICERCA:
            printf("---PROBLEMA DI RICERCA---\n");

            f=fopen("file/ricerca/insieme1.txt", "r");
            if(f==NULL) exit(EXIT_FAILURE);

            S1=VERTEXSEQread(f);
            fclose(f);

            f=fopen("file/ricerca/insieme2.txt", "r");
            if(f==NULL) exit(EXIT_FAILURE);

            S2=VERTEXSEQread(f);
            fclose(f);

            printf("---S1---\n");
            VERTEXSEQprint(S1, stdout);
            printf("\n---S2---\n");
            VERTEXSEQprint(S2, stdout);

            bestPath(g, S1, S2);

            VERTEXSEQfree(S1);
            VERTEXSEQfree(S2);
            break;
    }

    GRAPHfree(g);
    return 0;
}
