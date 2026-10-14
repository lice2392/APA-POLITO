#include <stdio.h>
#include <stdlib.h>
#define MAX 20

typedef struct{
    int nr, nc;
}Dimensioni;

Dimensioni leggiMatrice(char nomeFile[], int mat[][MAX]);
void stampaCapolista(int mat[][MAX], int nr, int nc);
void stampaMatrice(int mat[][MAX], int nR, int nC);

int main()
{
    int mat[MAX][MAX];
    Dimensioni dimMat;

    /* Lettura della matrice e delle sue dimensioni dal file. */
    dimMat=leggiMatrice("file.txt", mat);

    /* Stampa della matrice appena acquisita. */
    printf("La matrice letta dal file e':\n");
    stampaMatrice(mat, dimMat.nr, dimMat.nc);
    printf("\n");

    /* Stampa, per ciascuna giornata, l'indice di squadra capolista. */
    stampaCapolista(mat, dimMat.nr, dimMat.nc);
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




/* Funzione che stampa, per ciascuna giornata, l'indice di squadra capolista. */
void stampaCapolista(int mat[][MAX], int nr, int nc){
    int maxP, maxS, i, j;

    /* Scorro la matrice per colonne. */
    for(j=0; j<nc; j++){
        /* Per ogni giornata J-ESIMA, cerco la squadra I-ESIMA con il punteggio piu' alto. */
        maxP=0;
        for(i=0; i<nr; i++){
            if(mat[i][j]>maxP){
                maxP=mat[i][j];
                maxS=i;
            }
        }
        /* Stampo l'indice della squadra capolista della giornata J-ESIMA. */
        printf("Squadra capolista della giornata %d: %d\n", j, maxS);
    }
    return;

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
