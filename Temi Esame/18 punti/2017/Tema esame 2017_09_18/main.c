#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "famiglie.h"

typedef enum {VERO, FALSO}Boolean;

Boolean verifica(char *nomeFile, Famiglie f, Koalas k, int N, int S, int T, int m);
Boolean areThereEnemies(Famiglie f, Koalas k, int famiglia, int eucalipto, int *proposta, int dim);
void solve(Famiglie f, Koalas k, int N, int S, int T, int m);
void solveR(Famiglie f, Koalas k, int N, int S, int T, int m, int *countEucalipti, int *sol, int *bestSol, int *min, int pos);
int numEucalipti(int *markEucalipti, int T);

int main()
{
    Koalas k;
    Famiglie f;
    int N=8, S=4, T=6, m=3;
    FILE *fk, *ff, *fe;

    fk=fopen("habitat.txt", "r");
    if(fk==NULL) exit(EXIT_FAILURE);

    ff=fopen("families.txt", "r");
    if(ff==NULL) exit(EXIT_FAILURE);

    fe=fopen("enemies.txt", "r");
    if(fe==NULL) exit(EXIT_FAILURE);

    k=KOALASread(fk, N, T);

    f=FAMIGLIEread(k, ff, N, S);

    FAMIGLIEreadNemici(f, fe);

    printf("---PROBLEMA DI VERIFICA---\n");
    if(verifica("solution_ok.txt", f, k, N, S, T, m)==VERO){
        printf("Soluzione valida.\n\n");
    }
    else{
        printf("Soluzione non valida.\n\n");
    }

    printf("---PROBLEMA DI RICERCA---\n");
    solve(f, k, N, S, T, m);

    FAMIGLIEfree(f);
    KOALASfree(k);
    fclose(fk);
    fclose(ff);
    fclose(fe);
    return 0;
}




Boolean verifica(char *nomeFile, Famiglie f, Koalas k, int N, int S, int T, int m){
    FILE *fp;
    int *proposta;
    char koala[MAXC];
    int eucalipto, idKoala, i;
    int *countEucalipti;
    Koala *pKoala;

    fp=fopen(nomeFile, "r");
    if(fp==NULL) exit(EXIT_FAILURE);

    proposta=(int *)malloc(N*sizeof(int));
    if(proposta==NULL) exit(EXIT_FAILURE);

    for(i=0; i<N; i++)
        proposta[i]=-1;

    countEucalipti=(int *)calloc(T, sizeof(int));
    if(countEucalipti==NULL) exit(EXIT_FAILURE);

    while(fscanf(fp, "%s %d", koala, &eucalipto)==2){
        idKoala=KOALASsearch(k, koala);
        if(idKoala==-1){
            return FALSO;
        }
        if(eucalipto<0 || eucalipto>=T){
            return FALSO;
        }
        if(countEucalipti[eucalipto]==m){
            return FALSO;
        }
        if(proposta[idKoala]!=-1){
            return FALSO;
        }
        pKoala=KOALASgetKoalaByIndex(k, idKoala);
        if(pKoala->eucalipti[eucalipto]==0){
            return FALSO;
        }
        if(countEucalipti[eucalipto]>0 && areThereEnemies(f, k, pKoala->famiglia, eucalipto, proposta, N)==VERO){
            return FALSO;
        }
        countEucalipti[eucalipto]++;
        proposta[idKoala]=eucalipto;
    }
    for(i=0; i<N; i++){
        if(proposta[i]==-1){
            return FALSO;
        }
    }
    return VERO;
}




Boolean areThereEnemies(Famiglie f, Koalas k, int famiglia, int eucalipto, int *proposta, int dim){
    int koala;
    Famiglia *pFam;
    Koala *pK;

    pFam=FAMIGLIEgetFamigliaByIndex(f, famiglia);

    if(pFam->nNemici==0){
        return FALSO;
    }
    for(koala=0; koala<dim; koala++){
        if(proposta[koala]==eucalipto){
            pK=KOALASgetKoalaByIndex(k, koala);
            if(pFam->nemici[pK->famiglia]==1){
                return VERO;
            }
        }
    }
    return FALSO;
}




void solve(Famiglie f, Koalas k, int N, int S, int T, int m){
    int *sol, *countEucalipti, *bestSol, eucalipto, koala;
    int min=INT_MAX;
    Koala *pK;

    sol=(int *)malloc(N*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(int *)malloc(N*sizeof(int));
    if(bestSol==NULL) exit(EXIT_FAILURE);

    countEucalipti=(int *)calloc(T, sizeof(int));
    if(countEucalipti==NULL) exit(EXIT_FAILURE);

    solveR(f, k, N, S, T, m, countEucalipti, sol, bestSol, &min, 0);

    printf("Best solution:\n");
    printf("Numero di eucalipti: %d\n", min);
    printf("Assegnazione:\n");
    for(koala=0; koala<N; koala++){
        pK=KOALASgetKoalaByIndex(k, koala);
        printf("%s E%d\n", pK->nome, bestSol[koala]);
    }

    free(sol);
    free(bestSol);
    free(countEucalipti);
    return;
}


void solveR(Famiglie f, Koalas k, int N, int S, int T, int m, int *countEucalipti, int *sol, int *bestSol, int *min, int pos){
    int nEucalipti, i, eucalipto;
    Koala *pKoala;

    if(pos>=N){
        nEucalipti=numEucalipti(countEucalipti, T);
        if(nEucalipti < (*min)){
            (*min) = nEucalipti;
            for(i=0; i<N; i++){
                bestSol[i]=sol[i];
            }
        }
        return;
    }

    for(eucalipto=0; eucalipto<T; eucalipto++){
        if(countEucalipti[eucalipto]==m){
            continue;
        }
        pKoala=KOALASgetKoalaByIndex(k, pos);
        if(pKoala->eucalipti[eucalipto]==0){
            continue;
        }
        if(countEucalipti[eucalipto]>0 && areThereEnemies(f, k, pKoala->famiglia, eucalipto, sol, pos)==VERO){
            continue;
        }
        countEucalipti[eucalipto]++;
        sol[pos]=eucalipto;
        solveR(f, k, N, S, T, m, countEucalipti, sol, bestSol, min, pos+1);
        countEucalipti[eucalipto]--;
    }
    return;
}


int numEucalipti(int *markEucalipti, int T){
    int count=0;
    int i;

    for(i=0; i<T; i++){
        if(markEucalipti[i]>0){
            count++;
        }
    }
    return count;
}
