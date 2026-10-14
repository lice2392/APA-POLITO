#include <stdio.h>
#include <stdlib.h>
#define N 30

typedef struct{
    int nSottovettori;
    int max;
}Parametri;

void leggiVettore(int vet[], int dim);
Parametri trovaSottovettori(int vet[], int dim, int indici[]);
void stampaSub(int vet[], int dim, int indici[], Parametri par);
void stampa(int vet[], int dim);

int main()
{
    int vet[N];
    int dim;
    int indici[N];
    Parametri par;

    /* Inserimento della dimensione effettiva. */
    printf("Inserisci la dimensione del vettore: ");
    scanf("%d", &dim);

    /* Controllo sulla dimensione inserita. Stampo un messaggio di errore e termino se il valore
       inserito non va bene. */
    if(dim>N){
        printf("La dimensione inserita supera la dimensione massima del vettore (N = %d)\n", N);
        exit(EXIT_FAILURE);
    }

    /* Acquisizione del vettore da tastiera. */
    leggiVettore(vet, dim);

    /* Stampa del vettore inserito. */
    printf("\nIl vettore inserito e': ");
    stampa(vet, dim);

    /* Determinazione dei sottovettori di lunghezza massima non contenenti elementi nulli. */
    par=trovaSottovettori(vet, dim, indici);

    /* Stampa dei sottovettori. */
    printf("\nI sottovettori di lunghezza massima pari a %d non contenenti elementi nulli sono:\n", par.max);
    stampaSub(vet, dim, indici, par);
    return 0;
}




/* Funzione che acquisisce il vettore da tastiera. */
void leggiVettore(int vet[], int dim){
    int i;

    printf("\nInserisci il vettore:\n");
    for(i=0; i<dim; i++){
        printf("Inserisci un elemento: ");
        scanf("%d", &vet[i]);
    }
    return;
}




/* Funzione che stampa il vettore passato come parametro di dimensione DIM. */
void stampa(int vet[], int dim){
    int i;

    for(i=0; i<dim; i++){
        printf("%d", vet[i]);
    }
    printf("\n");
    return;
}




/* Funzione che trova i sottovettori di lunghezza massima non contenenti elementi non nulli.
   Salva gli indici di inizio nel vettore INDICI e restituisce in una STRUCT PARAMETRI il numero di sottovettori e la dimensione massima di questi. */
Parametri trovaSottovettori(int vet[], int dim, int indici[]){
    int cnt=0, i, index=0;
    Parametri par;

    /* Scorro il vettore VET. */
    par.max=0;
    for(i=0; i<dim; i++){
        /* Se l'elemento VET[I] e' 0, vuol dire che ho terminato un possibile sottovettore di lunghezza massima. */
        if(vet[i]==0){
            /* Se la lunghezza CNT del sottovettore e' pari alla lunghezza massima attuale e non e' 0: */
            if(cnt==par.max && cnt > 0){
                /* Salvo nella cella successiva di INDICI l'indice di partenza di tale sottovettore. */
                indici[index++]=i-cnt;
            }
            /* Invece, se la lunghezza CNT del sottovettore e' maggiore della lunghezza massima attuale: */
            else if(cnt>par.max){
                /* Aggiorno il massimo. */
                par.max=cnt;
                /* Salvo nella prima cella di INDICI l'indice di partenza di tale sottovettore. */
                index=0;
                indici[index++]=i-cnt;
            }
            cnt=0;
        }

        /* Se l'elemento VET[I] non e' 0, incremento la lunghezza del sottovettore. */
        else{
            cnt++;
        }
    }

    /* Check della lunghezza per possibili sottovettori di lunghezza massima non contenenti elementi nulli il cui ultimo elemento coincide
       con l'ultimo elemento di VET. */
    if(cnt==par.max && cnt > 0){
            indici[index++]=i-cnt;
    }
    else if(cnt>par.max){
        par.max=cnt;
        index=0;
        indici[index++]=i-cnt;
    }

    /* Il numero di sottovettori trovati coincide con il numero di celle di INDICI occupate. */
    par.nSottovettori=index;
    return par;
}




/* Funzione che stampa i sottovettori di lunghezza massima non contenenti elementi nulli. */
void stampaSub(int vet[], int dim, int indici[], Parametri par){
    int i, start, lun;

    /* Scorro il vettore INDICI. */
    for(i=0; i<par.nSottovettori; i++){
       /* Ogni cella INDICI[I] contiene l'indice di inizio di un sottovettore di lunghezza massima non contenente elementi nulli. */
       /* Stampo il sottovettore iniziante dall'indice INDICI[I]. */
       start=indici[i];
       lun=0;
       printf("Sottovettore %d: ", i+1);
       while(lun<par.max){
            printf("%d ", vet[start]);
            start++;
            lun++;
       }
       printf("\n");
    }
    return;
}
