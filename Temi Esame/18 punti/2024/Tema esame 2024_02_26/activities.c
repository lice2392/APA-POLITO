#include "activities.h"

struct activities{
    Attivita *attivita;
    int dim, maxEl;
};


static void insertOrdinato(ACT a, Attivita attivita);
static void insertPrecedenze(ACT a, char *riga);
static Attivita *getAttivita(ACT a, char *nome);
static int getIndexAttivita(ACT a, char *nome);
static void getParola(char *word, char *riga, int start);
static Attivita getAttivitaByIndex(ACT a, int index);
static Boolean checkPrecedenze(Attivita a, int *sol, int dim);
static void mergeSort(ACT a, int *attivita, int n);
static void mergeSortR(ACT a, int *attivita, int *B, int left, int right);
static void merge(ACT a, int *attivita, int *B, int left, int mezzo, int right);
static void bestR(ACT a, int *sol, int *bestSol, int*bestLun, int *max, int profitto, int start, int pos);


ACT ACTIVITIESinit(int maxN){
    ACT a;

    a=(ACT)malloc(sizeof(struct activities));
    if(a==NULL) exit(EXIT_FAILURE);

    a->dim=0;
    a->maxEl=maxN;

    a->attivita=(Attivita*)malloc(maxN*sizeof(Attivita));
    if(a->attivita==NULL) exit(EXIT_FAILURE);
    return a;
}




ACT ACTIVITIESread(FILE *f){
    ACT a;
    int nA, nP;
    int i;
    Attivita att;
    char riga[(3*MAXC)+4];

    fscanf(f, "%d %d", &nA, &nP);

    a=ACTIVITIESinit(nA);

    for(i=0; i<nA; i++){
        att=ATTIVITAread(f);
        insertOrdinato(a, att);
    }

    for(i=0; i<nP; i++){
       fgets(riga, (3*MAXC)+4, f);
       insertPrecedenze(a, riga);
    }
    return a;
}


static void insertOrdinato(ACT a, Attivita attivita){
    int i, pos;

    if(a->dim==a->maxEl){
        a->maxEl=2*a->maxEl;
        a->attivita=realloc(a->attivita, a->maxEl*sizeof(Attivita));
        if(a->attivita==NULL) exit(EXIT_FAILURE);
    }

    for(i=0; i<a->dim && attivita.tempoInizio>=a->attivita[i].tempoInizio; i++);

    pos=i;

    for(i=a->dim; i>=(pos+1) && i>=0; i--){
        a->attivita[i]=a->attivita[i-1];
    }

    a->attivita[pos]=attivita;
    (a->dim)++;
    return;
}


static void insertPrecedenze(ACT a, char *riga){
    char nomeAtt[MAXC];
    int i, idA;
    Attivita *att;

    for(i=0; i<strlen(riga); i++){
        getParola(nomeAtt, riga, i);
        if(i==0){
            att=getAttivita(a, nomeAtt);
            att->requisitoPrecedenza=VERO;
        }
        else{
           idA=getIndexAttivita(a, nomeAtt);
           ATTIVITAaddPrecedenza(att, idA);
        }
        i+=strlen(nomeAtt);
    }
    return;
}


static Attivita *getAttivita(ACT a, char *nome){
    int i;

    for(i=0; i<a->dim; i++){
        if(strcmp(a->attivita[i].nome, nome)==0){
            return &a->attivita[i];
        }
    }
    return NULL;
}


static int getIndexAttivita(ACT a, char *nome){
        int i;

    for(i=0; i<a->dim; i++){
        if(strcmp(a->attivita[i].nome, nome)==0){
            return i;
        }
    }
    return -1;
}


static void getParola(char *word, char *riga, int start){
    int i;

    for(i=start; i<strlen(riga) && riga[i]!=' ' && riga[i]!='\n'; i++){
        word[i-start]=riga[i];
    }
    word[i-start]='\0';
    return;
}




int ACTIVITIEScheckSelection(ACT a, char **selected, int nsel){
    Attivita attuale, prec;
    int i, idA;
    int *proposta, *mark;

    if(nsel<=0 || nsel>a->dim){
        return FALSO;
    }

    proposta=(int*)malloc(nsel*sizeof(int));
    if(proposta==NULL) exit(EXIT_FAILURE);

    mark=calloc(a->dim, sizeof(int));
    if(mark==NULL) exit(EXIT_FAILURE);

    for(i=0; i<nsel; i++){
        idA=getIndexAttivita(a, selected[i]);
        if(idA==-1){
            return FALSO;
        }
        if(mark[idA]==1){
            return FALSO;
        }
        proposta[i]=idA;
        mark[idA]=1;
    }

    mergeSort(a, proposta, nsel);

    for(i=0; i<nsel; i++){
        attuale=getAttivitaByIndex(a, proposta[i]);
        if(i==0 && attuale.requisitoPrecedenza==VERO){
            return FALSO;
        }
        if(i>0){
            prec=getAttivitaByIndex(a, proposta[i-1]);
            if(prec.tempoInizio<attuale.tempoFine && attuale.tempoInizio<prec.tempoFine){
                return FALSO;
            }

            if(attuale.requisitoPrecedenza==VERO && checkPrecedenze(attuale, proposta, i)==FALSO){
                return FALSO;
            }
        }
    }
    return VERO;
}


static Boolean checkPrecedenze(Attivita a, int *sol, int dim){
    int i, j;
    Boolean trovato=FALSO;

    for(i=0; i<a.nPrecedenze; i++){
        for(j=0; j<dim; j++){
            if(a.precedenze[i]==sol[j]){
                trovato=VERO;
                break;
            }
       }
       if(trovato==FALSO){
            return FALSO;
        }
    }
    return VERO;
}


static Attivita getAttivitaByIndex(ACT a, int index){
    return a->attivita[index];
}


static void mergeSort(ACT a, int *attivita, int n){
    int left, right;
    int *B;

    left=0;
    right=n-1;

    B=(int*)malloc(n*sizeof(int));
    if(B==NULL){
        exit(EXIT_FAILURE);
    }
    mergeSortR(a, attivita, B, left, right);
    free(B);
    return;
}


static void mergeSortR(ACT a, int *attivita, int *B, int left, int right){
    int mezzo;

    if(left==right){
        return;
    }

    mezzo=(left+right)/2;
    mergeSortR(a, attivita, B, left, mezzo);
    mergeSortR(a, attivita, B, mezzo+1, right);
    merge(a, attivita, B, left, mezzo, right);
    return;
}


static void merge(ACT a, int *attivita, int *B, int left, int mezzo, int right){
    int i, j, k;
    Attivita attI, attJ;

    i=left;
    j=mezzo+1;

    for(k=left; k<=right; k++){
        if(i<=mezzo){
            attI=getAttivitaByIndex(a, attivita[i]);
        }
        if(j<=right){
            attJ=getAttivitaByIndex(a, attivita[j]);
        }
        if(i>mezzo){
            B[k]=attivita[j++];
        }
        else if(j>right){
            B[k]=attivita[i++];
        }
        else if(attI.tempoInizio<=attJ.tempoInizio){
            B[k]=attivita[i++];
        }
        else{
            B[k]=attivita[j++];
        }
    }

    for(k=left; k<=right; k++){
        attivita[k]=B[k];
    }
    return;
}




char** ACTIVITIESbestSelection(ACT a, int *nAtt, int *profittoMax){
    int *sol, *bestSol, bestLun, max=0, i;
    char **bestActivities;
    Attivita att;

    sol=(int*)malloc(a->dim*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(int*)malloc(a->dim*sizeof(int));
    if(bestSol==NULL) exit(EXIT_FAILURE);

    bestR(a, sol, bestSol, &bestLun, &max, 0, 0, 0);

    bestActivities=(char**)malloc(bestLun*sizeof(char*));
    if(bestActivities==NULL) exit(EXIT_FAILURE);

    for(i=0; i<bestLun; i++){
       att=getAttivitaByIndex(a, bestSol[i]);
       bestActivities[i]=strdup(att.nome);
    }
    (*nAtt)=bestLun;
    (*profittoMax)=max;
    return bestActivities;
}


static void bestR(ACT a, int *sol, int *bestSol, int*bestLun, int *max, int profitto, int start, int pos){
    int attivita, i;
    Attivita att, prec;

    if(profitto>(*max)){
        (*max)=profitto;
        (*bestLun)=pos;
        for(i=0; i<pos; i++){
            bestSol[i]=sol[i];
        }
    }

    if(pos>=a->dim){
        return;
    }

    for(attivita=start; attivita<a->dim; attivita++){
        att=getAttivitaByIndex(a, attivita);
        if(pos==0 && att.requisitoPrecedenza==VERO)
            continue;
        if(att.requisitoPrecedenza==VERO && checkPrecedenze(att, sol, pos)==FALSO)
            continue;
        if(pos>0){
            prec=getAttivitaByIndex(a, sol[pos-1]);
            if(prec.tempoInizio<att.tempoFine && att.tempoInizio<prec.tempoFine)
                continue;
        }
        sol[pos]=attivita;
        profitto+=att.profitto;
        bestR(a, sol, bestSol, bestLun, max, profitto, attivita+1, pos+1);
        profitto-=att.profitto;
    }
    return;
}




void ACTIVITIESfree(ACT a){
    if(a!=NULL){
        if(a->attivita!=NULL){
            free(a->attivita);
        }
        free(a);
    }
    return;
}
