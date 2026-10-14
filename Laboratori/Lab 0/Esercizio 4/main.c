#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define C 21

typedef struct{
    int nr, nc;
}Dimensioni;

Dimensioni leggiMatrice(char nomeFile[], int mat[][MAX]);
void findSottomatrici(int mat[][MAX], int nr, int nc, int dim);
void stampaSottomatrice(int mat[][MAX], int startR, int startC, int dim);
void stampaMatrice(int mat[][MAX], int nR, int nC);
int sommaSottomatrice(int mat[][MAX], int startR, int startC, int dim);

int main()
{
    int mat[MAX][MAX];
    Dimensioni dimMat;
    char nomeFile[C];
    int dim, limite;

    /* Acquisizione da tastiera del nome del file. */
    printf("Inserisci il nome del file da leggere: ");
    scanf("%s", nomeFile);

    /* Lettura della matrice e delle sue dimensioni dal file. */
    dimMat=leggiMatrice(nomeFile, mat);

    /* Stampa della matrice appena acquisita. */
    printf("\nLa matrice letta dal file e':\n");
    stampaMatrice(mat, dimMat.nr, dimMat.nc);
    printf("\n");

    /* Il valore di DIM che deve inserire l'utente e' compreso tra 1 e il minimo tra nr e nc.
       Determino il limite massimo di DIM. */
    limite=(dimMat.nr<dimMat.nc)?dimMat.nr:dimMat.nc;

    /* Inserimento da tastiera di DIM. */
    printf("Inserisci un valore compreso tra 1 e %d: ", limite);
    scanf("%d", &dim);

    /* Ciclo per permettere all'utente di inserire ripetutamente il valore di DIM,
       stampare tutte le sottomatrici quadrate di tale dimensione contenute nella matrice
       e stampare tra queste la sottomatrice avente somma massima degli elementi. */
    while(dim>=1 && dim<=limite){
        /* Stampo sia le sottomatrici quadrate DIMxDIM sia la sottomatrice quadrata DIMxDIM avente
           somma massima degli elementi. */
        findSottomatrici(mat, dimMat.nr, dimMat.nc, dim);

        /* Inserimento da tastiera di DIM. */
        printf("\nInserisci un valore compreso tra 1 e %d: ", limite);
        scanf("%d", &dim);
    }
    return 0;
}




/* Funzione che legge la matrice e le sue dimensioni effettive da file. */
Dimensioni leggiMatrice(char nomeFile[], int mat[][MAX]){
    FILE *fi;
    Dimensioni dim;
    int i, j;

    /* Apro il file. Se il file non si apre correttamente stampo un messaggio di errore ed
       esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Acquisisco le dimensioni effettive della matrice. */
    fscanf(fi, "%d %d", &dim.nr, &dim.nc);

    /* Leggo la matrice dal file. */
    for(i=0; i<dim.nr; i++){
        for(j=0; j<dim.nc; j++){
            fscanf(fi, "%d", &mat[i][j]);
        }
    }
    fclose(fi);
    return dim;
}




/* Funzione che stampa tutte le sottomatrici quadrate DIMxDIM e la sottomatrice quadrata DIMxDIM avente somma
   massima degli elementi. */
void findSottomatrici(int mat[][MAX], int nr, int nc, int dim){
    int i, j;
    int max=0, maxR=0, maxC=0, somma;

    /* Stampo tutte le sottomatrici quadrate DIMxDIM e determino la sottomatrice quadrata DIMxDIM avente somma
       massima degli elementi. */
    printf("\nLe sottomatrici quadrate %d x %d sono:\n", dim, dim);
    for(i=0; i+dim<=nr; i++){
        for(j=0; j+dim<=nc; j++){
            stampaSottomatrice(mat, i, j, dim);
            printf("\n");
            somma=sommaSottomatrice(mat, i, j, dim);
            if(somma>max){
                max=somma;
                maxR=i;
                maxC=j;
            }
        }
    }

    /* Stampo la sottomatrice quadrata DIMxDIM avente somma massima degli elementi. */
    printf("La sottomatrice quadrata %d x %d avente somma massima degli elementi (SumMax = %d) e':\n", dim, dim, max);
    stampaSottomatrice(mat, maxR, maxC, dim);
    return;
}




/* Funzione che stampa una sottomatrice quadrata DIMxDIM. SRTART_R e START_C sono gli indici di riga e colonna di inizio
   della sottomatrice. */
void stampaSottomatrice(int mat[][MAX], int startR, int startC, int dim){
    int i, j;

    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            printf("%d ", mat[i+startR][j+startC]);
        }
        printf("\n");
    }
    return;
}




/* Funzione che calcola la somma degli elementi di una sottomatrice quadrata DIMxDIM. SRTART_R e START_C sono gli indici di riga e colonna di inizio
   della sottomatrice. */
int sommaSottomatrice(int mat[][MAX], int startR, int startC, int dim){
    int sum=0, i, j;

    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            sum+=mat[i+startR][j+startC];
        }
    }
    return sum;
}




/* Funzione che stampa una matrice di dimensioni NR e NC */
void stampaMatrice(int mat[][MAX], int nR, int nC){
    int i, j;

    for(i=0; i<nR; i++){
        for(j=0; j<nC; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return;
}
