#include <stdio.h>
#include <stdlib.h>
#include "clienti.h"
#include "alberghi.h"

Boolean readProposta(Alberghi a, Clienti c, char *nomeFile);
void solve(Alberghi alberghi, Clienti clienti, int a, int b);
void solveR(Alberghi alberghi, int nAlberghi, Clienti clienti, int nClienti, int a, int b, int *sol, int *bestSol, float *max, int pos);

int main()
{
    Clienti prenotazioni;
    Alberghi alberghi;
    FILE *f;
    int N=4;
    int X=4;
    int a=1, b=2;
    int M[]={2, 3, 4, 5};


    f=fopen("prenotazioni.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    prenotazioni=CLIENTIread(f);

    alberghi=ALBERGHIcrea(N, X, M);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(readProposta(alberghi, prenotazioni, "proposta_ok.txt")==VERO){
        printf("Soluzione valida.\n");
    }
    else{
        printf("Soluzione non valida.\n");
    }

    ALBERGHIreset(alberghi);

    printf("\n\n---PROBLEMA DI RICERCA---\n");
    solve(alberghi, prenotazioni, a, b);

    CLIENTIfree(prenotazioni);
    ALBERGHIfree(alberghi);
    return 0;
}




Boolean readProposta(Alberghi a, Clienti c, char *nomeFile){
    FILE *f;
    int *proposta;
    int nClienti, i, nAlberghi, indexAl, indexC, camera;
    char idC[MAX];
    Albergo albergo;
    Cliente cliente;

    f=fopen(nomeFile, "r");
    if(f==NULL) exit(EXIT_FAILURE);

    nClienti=CLIENTIgetNumClienti(c);

    nAlberghi=ALBERGHIgetNumAlberghi(a);

    proposta=(int*)malloc(nClienti*sizeof(int));
    if(proposta==NULL) exit(EXIT_FAILURE);

    for(i=0; i<nClienti; i++){
        proposta[i]=-1;
    }

    while(fscanf(f, "%s %d", idC, &indexAl)==2){
        if(indexAl<0 || indexAl>=nAlberghi){
            return FALSO;
        }
        indexC=CLIENTIsearch(c, idC);
        if(indexC==-1){
            return FALSO;
        }
        if(proposta[indexC]!=-1){
            return FALSO;
        }
        albergo=ALBERGHIgetAlbergo(a, indexAl);
        cliente=CLIENTIgetCliente(c, indexC);
        camera=ALBERGOisThereFreeRoom(albergo, cliente.giornoArrivo, cliente.giorniPernottamento);
        if(camera==-1){
            return FALSO;
        }
        ALBERGOinsertPrenotazione(&albergo, indexC, camera, cliente.giornoArrivo, cliente.giorniPernottamento);
        proposta[indexC]=indexAl;
    }

    for(i=0; i<nClienti; i++){
        if(proposta[i]==-1)
            return FALSO;
    }
    return VERO;
}




void solve(Alberghi alberghi, Clienti clienti, int a, int b){
    int *sol, *bestSol;
    float max=0;
    int nClienti, nAlberghi, i;
    FILE *f;

    nClienti=CLIENTIgetNumClienti(clienti);

    nAlberghi=ALBERGHIgetNumAlberghi(alberghi);

    sol=(int*)malloc(nClienti*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(int*)malloc(nClienti*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    solveR(alberghi, nAlberghi, clienti, nClienti, a, b, sol, bestSol, &max, 0);

    f=fopen("output.txt", "w");
    fprintf(f, "---BEST SOLUTION---\n");
    fprintf(f, "Funzione massima: %.2f\n", max);
    for(i=0; i<nClienti; i++){
        fprintf(f, "Cliente: ");
        CLIENTEprint(CLIENTIgetCliente(clienti, i), f);
        fprintf(f, " - Albergo: %d\n", bestSol[i]);
    }
    printf("La soluzione migliore e' stampata sul file 'output.txt'\n");

    free(sol);
    free(bestSol);
    return;
}


void solveR(Alberghi alberghi, int nAlberghi, Clienti clienti, int nClienti, int a, int b, int *sol, int *bestSol, float *max, int pos){
    int albergo, camera, i;
    float f;
    Albergo al;
    Cliente cl;

    if(pos>=nClienti){
        f=ALBERGHIcalcoloFunzioneUtilizzoStrutture(alberghi, a, b);
        if(f>(*max)){
            (*max)=f;
            for(i=0; i<nClienti; i++){
                bestSol[i]=sol[i];
            }
        }
        return;
    }

    cl=CLIENTIgetCliente(clienti, pos);

    for(albergo=0; albergo<nAlberghi; albergo++){
        al=ALBERGHIgetAlbergo(alberghi, albergo);
        camera=ALBERGOisThereFreeRoom(al, cl.giornoArrivo, cl.giorniPernottamento);
        if(camera==-1){
            continue;
        }
        sol[pos]=albergo;
        ALBERGOinsertPrenotazione(&al, pos, camera, cl.giornoArrivo, cl.giorniPernottamento);
        solveR(alberghi, nAlberghi, clienti, nClienti, a, b, sol, bestSol, max, pos+1);
        ALBERGOdeletePrenotazione(&al, camera, cl.giornoArrivo, cl.giorniPernottamento);
    }
    return;
}
