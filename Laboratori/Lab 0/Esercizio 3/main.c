#include <stdio.h>
#include <stdlib.h>
#define MAX 30

void leggiVettore(int vet[], int dim);
void stampa(int vet[], int dim);
void ruota(int vet[], int dim, int P, int dir);
void copia(int source[], int dest[], int dim);

int main()
{
    int N;
    int vet[MAX];
    int P, dir;

    /* Inserimento della dimensione effettiva. */
    printf("Inserisci la dimensione del vettore: ");
    scanf("%d", &N);

    /* Controllo sulla dimensione inserita. Stampo un messaggio di errore e termino se il valore
       inserito non va bene. */
    if(N>MAX){
        printf("La dimensione inserita supera la dimensione massima del vettore (MAX = %d)\n", MAX);
        exit(EXIT_FAILURE);
    }

    /* Acquisizione del vettore da tastiera. */
    leggiVettore(vet, N);

    /* Stampa del vettore inserito. */
    printf("\nIl vettore inserito e': ");
    stampa(vet, N);

    /* Inserimento del numero di posizioni di cui far ruotare il vettore. */
    printf("\nDi quante posizioni vuoi far ruotare il vettore? Inserisci un valore (0 PER TERMINARE): ");
    scanf("%d", &P);

    /* Ciclo per permettere all'utente di effettuare ripetutamente delle rotazioni. */
    while(P!=0){
        /* Controllo sulla correttezza dell'inserimento. Stampo un messaggio di errore se il valore di P
           e' un numero negativo oppure e' maggiore o uguale della dimensione del vettore. */
        if(P<0 || P>=N){
            printf("Il numero di posizioni inserite non va bene. Inserisci un valore positivo minore di %d.\n", N);
        }
        /* Se va tutto bene, continuo. */
        else{
            /* Inserimento della direzione di rotazione. */
            printf("\nIn quale direzione vuoi far ruotare il vettore? (DESTRA = -1, SINISTRA = 1): ");
            scanf("%d", &dir);
            /* Rotazione del vettore. */
            ruota(vet, N, P, dir);
        }
        /* Inserimento del numero di posizioni di cui far ruotare il vettore. */
        printf("\nDi quante posizioni vuoi far ruotare il vettore? Inserisci un valore (0 PER TERMINARE): ");
        scanf("%d", &P);
    }
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




/* Funzione per ruotare il vettore di un numero P di posizioni a destra o sinistra. */
void ruota(int vet[], int dim, int P, int dir){
    int tmp[MAX], i, nuovaP;

    switch(dir){
        /* Rotazione a destra. */
        case -1:
            /* Scorro il vettore VET. */
            for(i=0; i<dim; i++){
                /* Determino la nuova posizione dell'elemento VET[I], ricordando che l'elemento a destra di VET[DIM-1] e' VET[0]:
                   - se "I+P" genera un indice che e' minore della dimensione di VET, "I+P" e' la nuova posizione.
                   - se "I+P" genera un indice che e' maggiore o uguale della dimensione di VET, significa che, dopo DIM-1, gli indici devono
                     ripartire da 0: "I+P-DIM" e' la nuova posizione. */
                nuovaP=(i+P>=dim)?(i+P-dim):i+P;

                /* Salvo l'elemento VET[I] nel vettore temporaneo alla posizione NUOVAP. */
                tmp[nuovaP]=vet[i];
            }

            /* Copio il contenuto del vettore temporaneo in VET. */
            copia(tmp, vet, dim);

            /* Stampo il vettore ruotato. */
            printf("\nIl vettore ruotato e': ");
            stampa(vet, dim);
            break;

        /* Rotazione a sinistra. */
        case 1:
            /* Scorro il vettore VET. */
            for(i=0; i<dim; i++){
                /* Determino la nuova posizione dell'elemento VET[I], ricordando che l'elemento a sinistra di VET[0] e' VET[DIM-1]:
                   - se "I-P" genera un indice che e' maggiore o uguale a 0, "I-P" e' la nuova posizione.
                   - se "I-P" genera un indice che e' minore di 0, significa che, dopo 0, gli indici devono ripartire da DIM-1:
                     "I-P+DIM" e' la nuova posizione. */
                nuovaP=(i-P<0)?(i-P+dim):i-P;

                /* Salvo l'elemento VET[I] nel vettore temporaneo alla posizione NUOVAP. */
                tmp[nuovaP]=vet[i];
            }

            /* Copio il contenuto del vettore temporaneo in VET. */
            copia(tmp, vet, dim);

            /* Stampo il vettore ruotato. */
            printf("\nIl vettore ruotato e': ");
            stampa(vet, dim);
            break;
        default:
            printf("La direzione inserita non va bene. Impossibile ruotare il vettore.\n");

    }
    return;
}




/* Funzione che copia il vettore SOURCE nel vettore DEST. I vettori hanno la stessa dimensione. */
void copia(int source[], int dest[], int dim){
    int i;

    for(i=0; i<dim; i++){
        dest[i]=source[i];
    }
    return;
}





