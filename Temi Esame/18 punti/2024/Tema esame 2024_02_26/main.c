#include <stdio.h>
#include <stdlib.h>
#include "activities.h"

char **readProposta(char *nomeFile, int *dim);
void free2D(char **mat, int nr);

int main()
{
    ACT a;
    FILE *f;
    int nAtt, profittoMax, i, dimProposta;
    char **best, **proposta;

    f=fopen("input.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    a=ACTIVITIESread(f);

    printf("---PROBLEMA DI VERIFICA---\n");
    proposta=readProposta("proposta_ok.txt", &dimProposta);
    if(ACTIVITIEScheckSelection(a, proposta, dimProposta)==VERO){
        printf("Soluzione valida.\n\n");
    }
    else{
        printf("Soluzione non valida.\n\n");
    }

    printf("---PROBLEMA DI RICERCA---\n");
    best=ACTIVITIESbestSelection(a, &nAtt, &profittoMax);
    printf("Best solution:\n");
    printf("Profitto massimo: %d\n", profittoMax);
    printf("Attivita': ");
    for(i=0; i<nAtt; i++){
        printf("%s ", best[i]);
    }
    printf("\n");

    ACTIVITIESfree(a);
    free2D(best, nAtt);
    free2D(proposta, dimProposta);
    return 0;
}



char **readProposta(char *nomeFile, int *dim){
    FILE *f;
    char **proposta;
    char nome[MAXC];
    int i;

    f=fopen(nomeFile, "r");
    if(f==NULL) exit(EXIT_FAILURE);

    fscanf(f, "%d", dim);

    proposta=(char**)malloc((*dim)*sizeof(char*));
    if(proposta==NULL) exit(EXIT_FAILURE);

    for(i=0; i<(*dim); i++){
        fscanf(f, "%s", nome);
        proposta[i]=strdup(nome);
    }
    return proposta;
}




void free2D(char **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL){
                free(mat[i]);
            }
        }
        free(mat);
    }
}
