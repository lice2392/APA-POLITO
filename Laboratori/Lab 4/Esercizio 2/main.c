#include <stdio.h>
#include <stdlib.h>

int majority(int *a, int N);
int majorityR(int *a, int left, int right);
void stampaVettore(int *a, int N);

int main()
{
    int vet1[7]={3, 3, 9, 4, 3, 5, 3};
    int vet2[8]={0, 1, 0, 2, 3, 4, 0, 5};
    int maj1, maj2;

    /* Caso vettore 1. */
    /* Stampo il vettore. */
    printf("VETTORE: ");
    stampaVettore(vet1, 7);

    /* Calcolo l'elemento maggioritario. */
    maj1=majority(vet1, 7);

    /* Stampo l'elemento maggioritario se esiste, oppure un messaggio di errore. */
    if(maj1!=-1){
        printf("L'elemento maggioritario e' %d.\n\n", maj1);
    }
    else{
        printf("Il vettore non ha elemento maggioritario.\n\n");
    }


    /* Caso vettore 2. */
    /* Stampo il vettore. */
    printf("VETTORE: ");
    stampaVettore(vet2, 8);

    /* Calcolo l'elemento maggioritario. */
    maj2=majority(vet2, 8);

    /* Stampo l'elemento maggioritario se esiste, oppure un messaggio di errore. */
    if(maj2!=-1){
        printf("L'elemento maggioritario e' %d\n\n", maj2);
    }
    else{
        printf("Il vettore non ha elemento maggioritario.\n\n");
    }
    return 0;
}




/* Funzione che cerca e ritorna l'elemento maggioritario. */
/* Funzione WRAPPER. */
int majority(int *a, int N){
    return majorityR(a, 0, N-1);
}


/* Funzione ricorsiva. */
int majorityR(int *a, int left, int right){
    int dim, i;
    int majLeft, majRight, middle;
    int occMajLeft=0, occMajRight=0;

    /* Condizione di terminazione. */
    /* L'elemento maggioritario di un vettore composto da una cella
       e' l'elemento stesso. */
    if(left>=right){
        return a[left];
    }

    middle=(left+right)/2;

    /* Ricorro a sinistra. MAJ_LEFT e' l'elemento maggioritario del
       sottovettore sinistro. */
    majLeft=majorityR(a, left, middle);

    /* Ricorro a destra. MAJ_RIGHT e' l'elemento maggioritario del
       sottovettore destro. */
    majRight=majorityR(a, middle+1, right);

    /* Determino la dimensione del sottovettore attuale. */
    dim=right-left+1;

    /* Scorro il sottovettore attuale e determino il numero di occorrenze
       dei maggioritari destro e sinistro: essendo MAJ_LEFT e MAJ_RIGHT i
       maggioritari dei sottovettori destro e sinistro del sottovettore attuale,
       e' possibile che uno dei due sia maggioritario del sottovettore attuale. */
    for(i=left; i<=right; i++){
        if(a[i]==majLeft){
            occMajLeft++;
        }
        if(a[i]==majRight){
            occMajRight++;
        }
    }

    /* Se MAJ_LEFT ha numero di occorrenze > DIM/2, significa che questo e' il maggioritario
       del sottovettore attuale. Lo ritorno. */
    if(occMajLeft > dim/2){
        return majLeft;
    }

    /* Se MAJ_RIGHT ha numero di occorrenze > DIM/2, significa che questo e' il maggioritario
       del sottovettore attuale. Lo ritorno. */
    if(occMajRight > dim/2){
        return majRight;
    }
    /* Altrimenti ritorno -1: il sottovettore attuale non ha elemento maggioritario. */
    return -1;
}




/* Funzione che stampa un vettore. */
void stampaVettore(int *a, int N){
    int i;

    for(i=0; i<N; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return;
}
