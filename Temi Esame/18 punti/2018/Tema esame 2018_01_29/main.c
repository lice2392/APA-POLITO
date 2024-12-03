#include <stdio.h>
#include <stdlib.h>
#include "persone.h"
#include "aziende.h"

typedef enum{VERO, FALSO}Boolean;

typedef struct{
    int **mat;
}Preferenze;

void leggiPrefereze(Persone p, Aziende a, FILE *fa, FILE *fp, Preferenze *pPersone, Preferenze *pAziende, int N);
int **malloc2D(int nr, int nc);
void free2D(int **mat, int nr);
void stampaPreferenza(Preferenze pr, int N);
int *leggiProposta(Persone p, Aziende a, int N, char *nomeFile);
void stampaAssegnazione(int *proposta, int N);
Boolean verifica(int *proposta, int N, Preferenze pPersone, Preferenze pAziende);
int getOrdinePreferenza(int **mat, int riga, int search, int N);
void search(Preferenze pPersone, Preferenze pAziende, int N);
Boolean searchR(Preferenze pPersone, Preferenze pAziende, int *sol, int N, int *markAziende, int pos);


int main()
{
    Preferenze pPersone, pAziende;
    Persone persone;
    Aziende aziende;
    FILE *fp, *fa;
    int N=4;
    int *proposta;

    fp=fopen("persone.txt", "r");
    if(fp==NULL) exit(EXIT_FAILURE);

    persone=PERSONEread(fp, N);

    rewind(fp);

    fa=fopen("aziende.txt", "r");
    if(fa==NULL) exit(EXIT_FAILURE);

    aziende=AZIENDEread(fa, N);

    rewind(fa);

    leggiPrefereze(persone, aziende, fa, fp, &pPersone, &pAziende, N);

    printf("---PREFERENZE PERSONE---\n");
    stampaPreferenza(pPersone, N);

    printf("\n---PREFERENZE AZIENDE---\n");
    stampaPreferenza(pAziende, N);

    printf("\n\n\n---PROBLEMA DI VERIFICA---\n");
    proposta=leggiProposta(persone, aziende, N, "proposta_ok2.txt");
    printf("\n---PROPOSTA---\n");
    stampaAssegnazione(proposta, N);
    if(verifica(proposta, N, pPersone, pAziende)==VERO){
        printf("\n\nSoluzione valida.\n");
    }
    else{
        printf("\n\nSoluzione non valida.\n");
    }

    printf("\n\n\n---PROBLEMA DI RICERCA---\n");
    search(pPersone, pAziende, N);

    fclose(fp);
    fclose(fa);
    free2D(pAziende.mat, N);
    free2D(pPersone.mat, N);
    PERSONEfree(persone);
    AZIENDEfree(aziende);
    return 0;
}




void leggiPrefereze(Persone p, Aziende a, FILE *fa, FILE *fp, Preferenze *pPersone, Preferenze *pAziende, int N){
    int persona, azienda;
    char nomeP[MAX], nomeA[MAX];
    int indexPersona, indexAzienda;

    pPersone->mat=malloc2D(N, N);

    pAziende->mat=malloc2D(N, N);

    //Leggo le preferenze delle persone
    for(persona=0; persona<N; persona++){
        fscanf(fp, "%*s");
        for(azienda=0; azienda<N; azienda++){
            fscanf(fp, "%s", nomeA);
            indexAzienda=AZIENDEsearch(a, AZIENDAcrea(nomeA));
            pPersone->mat[persona][azienda]=indexAzienda;
        }
    }

    //Leggo le preferenze delle aziende
    for(azienda=0; azienda<N; azienda++){
        fscanf(fa, "%*s");
        for(persona=0; persona<N; persona++){
            fscanf(fa, "%s", nomeP);
            indexPersona=PERSONEsearch(p, PERSONAcrea(nomeP));
            pAziende->mat[azienda][persona]=indexPersona;
        }
    }
    return;
}




int **malloc2D(int nr, int nc){
    int **mat;
    int i;

    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);

    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    return mat;
}




void free2D(int **mat, int nr){
    int i;

    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL)
                free(mat[i]);
        }
        free(mat);
    }
    return;
}




void stampaPreferenza(Preferenze pr, int N){
    int i, j;

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%d\t", pr.mat[i][j]);
        }
        printf("\n");
    }
    return;
}




int *leggiProposta(Persone p, Aziende a, int N, char *nomeFile){
    int *proposta;
    int i, indexPersona, indexAzienda;
    FILE *f;
    char nomeP[MAX], nomeA[MAX];

    proposta=(int*)malloc(N*sizeof(int));
    if(proposta==NULL) exit(EXIT_FAILURE);

    f=fopen(nomeFile, "r");
    if(f==NULL) exit(EXIT_FAILURE);

    for(i=0; i<N; i++){
        fscanf(f, "%s %s", nomeP, nomeA);
        indexPersona=PERSONEsearch(p, PERSONAcrea(nomeP));
        indexAzienda=AZIENDEsearch(a, AZIENDAcrea(nomeA));
        proposta[indexPersona]=indexAzienda;
    }
    return proposta;
}




void stampaAssegnazione(int *proposta, int N){
    int i;

    for(i=0; i<N; i++){
        printf("(p%d, a%d) ", i, proposta[i]);
    }
    return;
}




Boolean verifica(int *proposta, int N, Preferenze pPersone, Preferenze pAziende){
    int persona, personaAssegnata, ordinePrefPersonaAziendaAssegnata;
    int aziendaAssegnata, i, azienda;
    int ordinePrefPersonaNuovaAzienda;
    int ordinePrefNuovaAziendaPersona;
    int ordinePrefNuovaAziendaPersonaAssegnata;

    for(persona=0; persona<N; persona++){
        aziendaAssegnata=proposta[persona];
        ordinePrefPersonaAziendaAssegnata=getOrdinePreferenza(pPersone.mat, persona, aziendaAssegnata, N);
        for(i=0; i<N; i++){
            if(i==persona){
                continue;
            }
            personaAssegnata=i;
            azienda=proposta[i];
            ordinePrefPersonaNuovaAzienda=getOrdinePreferenza(pPersone.mat, persona, azienda, N);
            ordinePrefNuovaAziendaPersona=getOrdinePreferenza(pAziende.mat, azienda, persona, N);
            ordinePrefNuovaAziendaPersonaAssegnata=getOrdinePreferenza(pAziende.mat, azienda, personaAssegnata, N);
            if(ordinePrefPersonaNuovaAzienda < ordinePrefPersonaAziendaAssegnata && ordinePrefNuovaAziendaPersona < ordinePrefNuovaAziendaPersonaAssegnata){
                return FALSO;
            }
        }
    }
    return VERO;
}




int getOrdinePreferenza(int **mat, int riga, int search, int N){
    int j;

    for(j=0; j<N; j++){
        if(mat[riga][j]==search)
            return j;
    }
    return -1;
}




void search(Preferenze pPersone, Preferenze pAziende, int N){
    int *sol, *mark;

    sol=(int*)malloc(N*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    mark=calloc(N, sizeof(int));
    if(mark==NULL) exit(EXIT_FAILURE);

    if(searchR(pPersone, pAziende, sol, N, mark, 0)==VERO){
        printf("Soluzione trovata.\n");
        printf("\n---MATCHING---\n");
        stampaAssegnazione(sol, N);
        printf("\n");
    }
    else{
        printf("Soluzione non trovata.\n");
    }
    return;
}




Boolean searchR(Preferenze pPersone, Preferenze pAziende, int *sol, int N, int *markAziende, int pos){
    int azienda, i;

    if(pos>=N){
        if(verifica(sol, N, pPersone, pAziende)==VERO){
            return VERO;
        }
        return FALSO;
    }

    for(i=0; i<N; i++){
        azienda=pPersone.mat[pos][i];
        if(markAziende[azienda]==0){
            markAziende[azienda]=1;
            sol[pos]=azienda;
            if(searchR(pPersone, pAziende, sol, N, markAziende, pos+1)==VERO){
                return VERO;
            }
            markAziende[azienda]=0;
        }
    }
    return FALSO;
}
