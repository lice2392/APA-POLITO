#include <stdio.h>
#include <stdlib.h>
#include "offerte.h"
#include "spesa.h"
#include <limits.h>

typedef enum{VERO, FALSO}Boolean;

void leggiFile(char *nomeFile, Prodotti *p, Offerte *o);
void solve(Prodotti p, Offerte o, Spesa s);
void solveR(Prodotti p, Offerte o, Spesa s, int *solOff, int *prodSingoli, int* qtaProd, int *bestSolOff, int *bestSolSin, int *min, int prezzo, int pos);
Boolean isOffertaValidaPerSpesa(Spesa s, Offerta o);
void aggiungiQtaProdotti(Offerta o, int *qta);
void eliminaQtaProdotti(Offerta o, int *qta);
int addSingoli(Prodotti p, Spesa s, int* qtaProd, int *qtaSingoli, int prezzo);
void azzeraSingoli(int *qtaSingoli, int dim);

int main()
{
    Prodotti p;
    Offerte o;
    Spesa s;
    FILE *f;

    leggiFile("catalogo.txt", &p, &o);

    f=fopen("spesa.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    s=SPESAread(p, f, PRODOTTIgetDim(p));

    printf("---LISTA DELLA SPESA---\n");
    SPESAprint(p, s, stdout);

    printf("\n---PROBLEMA DI RICERCA E OTTIMIZZAZIONE---\n");
    solve(p, o, s);

    fclose(f);
    PRODOTTIfree(p);
    OFFERTEfree(o);
    SPESAclear(&s);
    return 0;
}




void leggiFile(char *nomeFile, Prodotti *p, Offerte *o){
    FILE *f;
    int nP, nO;

    f=fopen(nomeFile, "r");
    if(f==NULL) exit(EXIT_FAILURE);

    fscanf(f, "%d %d", &nP, &nO);

    *p=PRODOTTIread(f, nP, nO);

    *o=OFFERTEread(*p, f, nO, nP);

    fclose(f);
    return;
}




void solve(Prodotti p, Offerte o, Spesa s){
    int *solOff, *bestSolOff, *bestSolSingoli;
    int *qtaProdottiSingoli, *qtaProdottiAcquistati;
    int min=INT_MAX, i;
    Prodotto *pr;
    Offerta *off;

    solOff=(int*)calloc(OFFERTEgetDim(o), sizeof(int));
    if(solOff==NULL) exit(EXIT_FAILURE);

    bestSolOff=(int*)calloc(OFFERTEgetDim(o), sizeof(int));
    if(bestSolOff==NULL) exit(EXIT_FAILURE);

    qtaProdottiSingoli=calloc(PRODOTTIgetDim(p), sizeof(int));
    if(qtaProdottiSingoli==NULL) exit(EXIT_FAILURE);

    qtaProdottiAcquistati=calloc(PRODOTTIgetDim(p), sizeof(int));
    if(qtaProdottiAcquistati==NULL) exit(EXIT_FAILURE);

    bestSolSingoli=calloc(PRODOTTIgetDim(p), sizeof(int));
    if(bestSolSingoli==NULL) exit(EXIT_FAILURE);

    solveR(p, o, s, solOff, qtaProdottiSingoli, qtaProdottiAcquistati, bestSolOff, bestSolSingoli, &min, 0, 0);

    printf("Best Solution:\n");
    printf("Prezzo minimo: %d\n", min);
    printf("Insieme di acquisti di prodotti singoli e/o di offerte:\n");
    for(i=0; i<OFFERTEgetDim(o); i++){
        if(bestSolOff[i]==1){
            off=OFFERTEgetOffertaByIndex(o, i);
            printf("%s\n", off->nome);
        }
    }

    for(i=0; i<PRODOTTIgetDim(p); i++){
        if(bestSolSingoli[i]>0){
            pr=PRODOTTIgetProdottoByIndex(p, i);
            printf("%d di %s\n", bestSolSingoli[i], pr->nome);
        }
    }

    free(solOff);
    free(bestSolOff);
    free(qtaProdottiSingoli);
    free(qtaProdottiAcquistati);
    free(bestSolSingoli);
    return;
}




void solveR(Prodotti p, Offerte o, Spesa s, int *solOff, int *prodSingoli, int* qtaProd, int *bestSolOff, int *bestSolSin, int *min, int prezzo, int pos){
    Offerta *off;
    int i;

    if(pos>=OFFERTEgetDim(o)){
        prezzo=addSingoli(p, s, qtaProd, prodSingoli, prezzo);
        if(prezzo < (*min)){
            (*min)=prezzo;
            for(i=0; i<OFFERTEgetDim(o); i++){
                bestSolOff[i]=solOff[i];
            }
            for(i=0; i<PRODOTTIgetDim(p); i++){
                bestSolSin[i]=prodSingoli[i];
            }
        }
        azzeraSingoli(prodSingoli, PRODOTTIgetDim(p));
        return;
    }

    off=OFFERTEgetOffertaByIndex(o, pos);
    if(isOffertaValidaPerSpesa(s, *off)==VERO){
        solOff[pos]=1;
        aggiungiQtaProdotti(*off, qtaProd);
        solveR(p, o, s, solOff, prodSingoli, qtaProd, bestSolOff, bestSolSin, min, prezzo+off->prezzo, pos+1);
        eliminaQtaProdotti(*off, qtaProd);
    }
    solOff[pos]=0;
    solveR(p, o, s, solOff, prodSingoli, qtaProd, bestSolOff, bestSolSin, min, prezzo, pos+1);
    return;
}





Boolean isOffertaValidaPerSpesa(Spesa s, Offerta o){
    int i;

    for(i=0; i<o.maxProdotti; i++){
        if(s.prodotti[i]==1 && o.prodotti[i]==1){
            return VERO;
        }
    }
    return FALSO;
}




void aggiungiQtaProdotti(Offerta o, int *qta){
    int i;

    for(i=0; i<o.maxProdotti; i++){
        if(o.prodotti[i]==1){
            qta[i]+=o.quantita[i];
        }
    }
    return;
}




void eliminaQtaProdotti(Offerta o, int *qta){
    int i;

    for(i=0; i<o.maxProdotti; i++){
        if(o.prodotti[i]==1){
            qta[i]-=o.quantita[i];
        }
    }
    return;
}




int addSingoli(Prodotti p, Spesa s, int* qtaProd, int *qtaSingoli, int prezzo){
    int i;
    Prodotto *pr;

    for(i=0; i<s.maxProdotti; i++){
        if(s.prodotti[i]==1 && qtaProd[i]<s.quantita[i]){
            pr=PRODOTTIgetProdottoByIndex(p, i);
            qtaSingoli[i]=(s.quantita[i]-qtaProd[i]);
            prezzo=prezzo+(qtaSingoli[i]*pr->prezzo);
        }
    }
    return prezzo;
}




void azzeraSingoli(int *qtaSingoli, int dim){
    int i;

    for(i=0; i<dim; i++){
        qtaSingoli[i]=0;
    }
    return;
}
