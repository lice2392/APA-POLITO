#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "elenco.h"
#include "distanze.h"
#include "sedi.h"
#include "servizi.h"
#define PRONTOS -2
#define SERVITA -1

typedef enum{VERO, FALSO}Boolean;
typedef enum {PS_NO_CITTA, PS_NO_ABB_CITTA}Tipo;

char *messaggi[2]={" vanno bene come sedi di pronto soccorso.", " non vanno bene come sedi di pronto soccorso: "};
char *motivazione;

void caricaDati(char *nomeFile, Distanze *d, Elenco *e);
Boolean checkSedi(Sedi s, Distanze d, Elenco e, int maxD, int minS);
Servizi bestPart(Sedi s, Distanze d, Elenco e, int maxD, int minS);
void bestPartR(Sedi s, int nSedi, Distanze d, Elenco e, int nCitta, int maxD, int minS, int*sol, int*bestSol, float*min, int distTot, int pos);
Boolean prunePart(Sedi s, Distanze d, int sede, int citta, int *distanza, int maxD);
Boolean checkPart(int *sol, int nCitta, int nSedi, int minS);
void getMotivazione(Citta c, int minS, Tipo motivo);

int main()
{
    Elenco citta;
    Sedi prontoSoccorso_ok, prontoSoccorso_wrong;
    Distanze distanze;
    Servizi assegnazioni;
    Boolean risultato;
    int maxD=4, minS=2;

    caricaDati("file.txt", &distanze, &citta);

    printf("---ELENCO CITTA'---\n");
    ELENCOprint(citta, stdout);

    printf("\n---DISTANZE---\n");
    DISTANZEprint(distanze, stdout);


    printf("\n---PROBLEMA DI VERIFICA---\n");
    //VERIFICA_OK
    prontoSoccorso_ok=SEDIread("sedi_ok.txt", citta);
    printf("1) Con MIN_S = %d e MAX_D = %d, le citta' ", minS, maxD);
    SEDIprint(prontoSoccorso_ok, stdout, citta);
    risultato=checkSedi(prontoSoccorso_ok, distanze, citta, maxD, minS);
    printf("%s%s", messaggi[risultato], (risultato==VERO)?"\n":motivazione);
    if(risultato==FALSO){
        free(motivazione);
    }

    //VERIFICA_SBAGLIATA: NON TUTTE LE CITTA SERVITE
    prontoSoccorso_wrong=SEDIread("sedi_wrong.txt", citta);
    printf("2) Con MIN_S = %d e MAX_D = %d, le citta' ", minS, maxD);
    SEDIprint(prontoSoccorso_wrong, stdout, citta);
    risultato=checkSedi(prontoSoccorso_wrong, distanze, citta, maxD, minS);
    printf("%s%s", messaggi[risultato], (risultato==VERO)?"\n":motivazione);
    if(risultato==FALSO){
        free(motivazione);
    }

    //VERIFICA_SBAGLIATA: UNA SEDE NON SERVE IL NUMERO MINIMO DI CITTA
    printf("3) Con MIN_S = 3 e MAX_D = %d, le citta' ", maxD);
    SEDIprint(prontoSoccorso_wrong, stdout, citta);
    risultato=checkSedi(prontoSoccorso_wrong, distanze, citta, maxD, 3);
    printf("%s%s", messaggi[risultato], (risultato==VERO)?"\n":motivazione);
    if(risultato==FALSO){
        free(motivazione);
    }

    SEDIfree(prontoSoccorso_wrong);


    printf("\n---PROBLEMA DI RICERCA E OTTIMIZZAZIONE---\n");
    assegnazioni=bestPart(prontoSoccorso_ok, distanze, citta, maxD, minS);
    printf("BEST SOLUTION:\n");
    SERVIZIprint(assegnazioni, prontoSoccorso_ok, stdout, citta);

    ELENCOfree(citta);
    DISTANZEfree(distanze);
    SEDIfree(prontoSoccorso_ok);
    return 0;
}




void caricaDati(char *nomeFile, Distanze *d, Elenco *e){
    int N;
    FILE *f;

    f=fopen(nomeFile, "r");
    if(f==NULL){
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &N);

    *e=ELENCOread(f, N);
    *d=DISTANZEread(f, N);
    return;
}




Boolean checkSedi(Sedi s, Distanze d, Elenco e, int maxD, int minS){
    int *assegnazioniProntoS;
    int nSedi, nCitta, distanza, prontoS, nCittaServite, i, citta;

    nSedi=SEDIgetNumSedi(s);
    nCitta=DISTANZEgetNumCitta(d);

    assegnazioniProntoS=(int*)calloc(nCitta, sizeof(int));
    if(assegnazioniProntoS==NULL){
        exit(EXIT_FAILURE);
    }

    for(i=0; i<nSedi; i++){
        prontoS=SEDIgetSede(s, i);
        nCittaServite=0;
        for(citta=0; citta<nCitta; citta++){
            if(prontoS==citta){
                assegnazioniProntoS[citta]=PRONTOS;
                continue;
            }
            distanza=DISTANZEgetDistanza(d, prontoS, citta);
            if(distanza<=maxD){
                nCittaServite++;
                assegnazioniProntoS[citta]=SERVITA;
            }
        }
        if(nCittaServite<minS){
            getMotivazione(ELENCOgetCittaByIndex(e, prontoS), minS, PS_NO_ABB_CITTA);
            free(assegnazioniProntoS);
            return FALSO;
        }
    }

    for(i=0; i<nCitta; i++){
        if(assegnazioniProntoS[i]!=SERVITA && assegnazioniProntoS[i]!=PRONTOS){
            getMotivazione(ELENCOgetCittaByIndex(e, i), minS, PS_NO_CITTA);
            free(assegnazioniProntoS);
            return FALSO;
        }
    }
    free(assegnazioniProntoS);
    return VERO;
}




Servizi bestPart(Sedi s, Distanze d, Elenco e, int maxD, int minS){
    int *sol, *bestSol, nCitta, nSedi, i, prontoS;
    float min=INT_MAX;
    Servizi sv;

    nCitta=ELENCOgetNumCitta(e);
    nSedi=SEDIgetNumSedi(s);

    sol=(int*)malloc(nCitta*sizeof(int));
    bestSol=(int*)malloc(nCitta*sizeof(int));
    if(sol==NULL || bestSol==NULL){
        exit(EXIT_FAILURE);
    }

    for(i=0; i<nSedi; i++){
        prontoS=SEDIgetSede(s, i);
        sol[prontoS]=PRONTOS;
    }

    bestPartR(s, nSedi, d, e, nCitta, maxD, minS, sol, bestSol, &min, 0, 0);

    sv=SERVIZIinit(nCitta);

    for(i=0; i<nCitta; i++){
        if(bestSol[i]==PRONTOS){
            prontoS=SEDIgetSede(s, i);
        }
        else{
            prontoS=SEDIgetSede(s, bestSol[i]);
        }
        SERVIZIassegna(sv, prontoS, i);
    }
    printf("Distanza media minima: %.2f\n", min);
    free(sol);
    free(bestSol);
    return sv;
}


void bestPartR(Sedi s, int nSedi, Distanze d, Elenco e, int nCitta, int maxD, int minS, int*sol, int*bestSol, float*min, int distTot, int pos){
    int sede, distanza, i;
    float distMedia;

    if(pos>=nCitta){
        distMedia=(float)distTot/(float)(nCitta-nSedi);
        if(distMedia < (*min) && checkPart(sol, nCitta, nSedi, minS)==VERO){
            for(i=0; i<nCitta; i++){
                bestSol[i]=sol[i];
            }
            (*min)=distMedia;
        }
        return;
    }

    if(sol[pos]==PRONTOS){
        bestPartR(s, nSedi, d, e, nCitta, maxD, minS, sol, bestSol, min, distTot, pos+1);
        return;
    }

    for(sede=0; sede<nSedi; sede++){
        if(prunePart(s, d, sede, pos, &distanza, maxD)==FALSO){
            continue;
        }
        sol[pos]=sede;
        bestPartR(s, nSedi, d, e, nCitta, maxD, minS, sol, bestSol, min, distTot+distanza, pos+1);
    }
    return;
}


Boolean prunePart(Sedi s, Distanze d, int sede, int citta, int *distanza, int maxD){
    int prontoS;

    prontoS=SEDIgetSede(s, sede);
    *distanza=DISTANZEgetDistanza(d, prontoS, citta);

    if((*distanza)>maxD)
        return FALSO;
    return VERO;
}


Boolean checkPart(int *sol, int nCitta, int nSedi, int minS){
    int *occProntoS, i, sede;

    occProntoS=(int*)calloc(nSedi, nSedi*sizeof(int));
    if(occProntoS==NULL){
        exit(EXIT_FAILURE);
    }

    for(i=0; i<nCitta; i++){
        if(sol[i]==PRONTOS){
            continue;
        }
        sede=sol[i];
        occProntoS[sede]++;
    }

    for(i=0; i<nSedi; i++){
        if(occProntoS[i]<minS){
            free(occProntoS);
            return FALSO;
        }
    }

    free(occProntoS);
    return VERO;
}




void getMotivazione(Citta c, int minS, Tipo motivo){
    int len;
    switch(motivo){
        case PS_NO_CITTA:
            len=snprintf(NULL, 0, "la citta' %s non e' servita da nessun pronto soccorso.\n", c.nome)+1;
            motivazione=(char*)malloc(len*sizeof(char));
            if(motivazione==NULL){
                exit(EXIT_FAILURE);
            }
            sprintf(motivazione, "la citta' %s non e' servita da nessun pronto soccorso.\n", c.nome);
            break;
        case PS_NO_ABB_CITTA:
            len=snprintf(NULL, 0, "la sede candidata %s non serve almeno %d citta'.\n", c.nome, minS)+1;
            motivazione=(char*)malloc(len*sizeof(char));
            if(motivazione==NULL){
                exit(EXIT_FAILURE);
            }
            sprintf(motivazione, "la sede candidata %s non serve almeno %d citta'.\n", c.nome, minS);
            break;
    }
    return;
}
