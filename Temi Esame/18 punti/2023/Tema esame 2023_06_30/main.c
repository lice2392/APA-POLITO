#include <stdio.h>
#include <stdlib.h>
#include "scacchiera.h"

int main()
{
    Scacchiera s;
    Tessere t;
    FILE *fs, *fm;
    Mosse m;
    int M=10;
    char messaggio[256];

    fs=fopen("file/scacchiera.txt", "r");
    if(fs==NULL) exit(EXIT_FAILURE);

    s=SCACCHIERAread(fs, &t);

    printf("---SCACCHIERA INIZIALE---\n");
    SCACCHIERAprint(s, t, stdout);



    printf("\n\n\n---PROBLEMA DI VERIFICA---\n");
    fm=fopen("file/proposta_ok.txt", "r");
    if(fm==NULL) exit(EXIT_FAILURE);

    m=MOSSEread(fm);

    if(SCACCHIERAverificaMosse(s, t, m, M, messaggio)==FALSO){
        printf("Mosse non valide: %s", messaggio);
    }
    else{
        printf("Mosse valide.\n");
        if(SCACCHIERAverificaPuzzle(s, t)==VERO){
            printf("Le mosse proposte risolvono il puzzle.\n");
            printf("\n---MOSSE PROPOSTE---\n");
            MOSSEprint(m, stdout);
            printf("---SCACCHIERA FINALE---\n");
            SCACCHIERAprint(s, t, stdout);
        }
        else{
            printf("Le mosse proposte non risolvono il puzzle.\n");
        }
    }
    SCACCHIERAreset(s, m);


    printf("\n\n\n---PROBLEMA DI RICERCA:---\n");
    SCACCHIERAsearch(s, t, M);


    fclose(fm);
    fclose(fs);
    SCACCHIERAfree(s);
    MOSSEfree(m);
    return 0;
}
