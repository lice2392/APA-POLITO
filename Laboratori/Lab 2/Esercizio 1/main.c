#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50

typedef enum{BIANCO=0, NERO}Colore;

typedef struct{
    int nr, nc;
}Dimensioni;

typedef struct{
    int startR, startC, altezza, base, area;
}Cella;

Dimensioni leggiMatrice(char nomeFile[], int mat[][MAX]);
void findRegioni(int mat[][MAX], int nr, int nc);
bool isInizioRegione(int mat[][MAX], int indexR, int indexC, int nr, int nc);
int calcolaAltezza(int mat[][MAX], int indexR, int indexC, int nr, int nc);
int calcolLarghezza(int mat[][MAX], int indexR, int indexC, int nr, int nc);

int main()
{
    Dimensioni dimMat;
    int mat[MAX][MAX];

     /* Acquisizione della matrice da file. */
    dimMat=leggiMatrice("file.txt", mat);

    /* Individuo e stampo le regioni nere piu' grandi per altezza, larghezza e area totale. */
    findRegioni(mat, dimMat.nr, dimMat.nc);
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




/* Funzione che determina e stampa le regioni nere piu' grandi per altezza, larghezza e area totale. */
void findRegioni(int mat[][MAX], int nr, int nc){
    int i, j, altezza, base, area;
    Cella maxBase={-1, -1, 0, 0, 0}, maxAltezza={-1, -1, 0, 0, 0}, maxArea={-1, -1, 0, 0, 0};

    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            /* Passo alla prossima cella se non e' l'inizio di una regione NERA. */
            if(mat[i][j]==BIANCO ||(mat[i][j]==NERO && !isInizioRegione(mat, i, j, nr, nc))){
                continue;
            }
            /* Altrimenti calcolo larghezza, altezza e area della regione. */
            altezza=calcolaAltezza(mat, i, j, nr, nc);
            base=calcolLarghezza(mat, i, j, nr, nc);
            area=altezza*base;

            /* Check sulla base massima. */
            if(base>maxBase.base){
                maxBase.startR=i;
                maxBase.startC=j;
                maxBase.base=base;
                maxBase.altezza=altezza;
                maxBase.area=area;
            }

            /* Check sull'altezza massima. */
            if(altezza>maxAltezza.altezza){
                maxAltezza.startR=i;
                maxAltezza.startC=j;
                maxAltezza.base=base;
                maxAltezza.altezza=altezza;
                maxAltezza.area=area;
            }

            /* Check sull'area massima. */
            if(area>maxArea.area){
                maxArea.startR=i;
                maxArea.startC=j;
                maxArea.base=base;
                maxArea.altezza=altezza;
                maxArea.area=area;
            }
        }
    }

    /* Stampo le regioni nere piu' grandi per altezza, larghezza e area totale. */
    printf("Le regioni nere piu' grandi per altezza, larghezza e area totale sono:\n");
    printf("Max Base: estremo superiore sinistro = <%d, %d>: b = %d, h = %d, Area = %d\n", maxBase.startR, maxBase.startC, maxBase.base, maxBase.altezza, maxBase.area);
    printf("Max Altezza: estremo superiore sinistro = <%d, %d>: b = %d, h = %d, Area = %d\n", maxAltezza.startR, maxAltezza.startC, maxAltezza.base, maxAltezza.altezza, maxAltezza.area);
    printf("Max Area: estremo superiore sinistro = <%d, %d>: b = %d, h = %d, Area = %d\n", maxArea.startR, maxArea.startC, maxArea.base, maxArea.altezza, maxArea.area);
    return;
}




/* Funzione che determina se una cella e' o meno l'inizio di una regione nera. */
bool isInizioRegione(int mat[][MAX], int indexR, int indexC, int nr, int nc){
    bool su, sinistra;

    /* Per essere l'inizio di una regione nera:
       1) La cella attuale, se sulla prima riga, deve essere la prima cella della matrice oppure deve
          avere una cella BIANCA a sinistra.
       2) La cella attuale, se sulla prima colonna, deve avere una cella BIANCA sopra.
       3) La cella attuale, se altrove nella matrice, deve avere una cella BIANCA sopra e a sinistra. */
    su=((indexR==0) || (indexR>0 && mat[indexR-1][indexC]==BIANCO));
    sinistra=((indexC==0) || (indexC>0 && mat[indexR][indexC-1]==BIANCO));
    return su && sinistra;
}




/* Funzione che calcola l'altezza di una regione nera. */
int calcolaAltezza(int mat[][MAX], int indexR, int indexC, int nr, int nc){
    int i, altezza=0;

    /* Scorro la colonna INDEXC a partire dalla riga INDEXR fino a quando non incontro una
       cella BIANCA oppure fino alla fine della colonna. Durante il ciclo conto il numero di
       celle NERE. */
    for(i=indexR; mat[i][indexC]==NERO && i<nr; i++){
        altezza++;
    }
    return altezza;
}




/* Funzione che calcola la larghezza di una regione nera. */
int calcolLarghezza(int mat[][MAX], int indexR, int indexC, int nr, int nc){
    int j, larghezza=0;

    /* Scorro la riga INDEXR a partire dalla colonna INDEXC fino a quando non incontro una
       cella BIANCA oppure fino alla fine della riga. Durante il ciclo conto il numero di
       celle NERE. */
    for(j=indexC; mat[indexR][j]==NERO && j<nc; j++){
        larghezza++;
    }
    return larghezza;
}
