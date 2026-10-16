#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50

typedef enum{BIANCO=0, NERO}Colore;

void leggiMatrice(char nomeFile[], int mat[][MAX], int *nr, int *nc);
void findRegioni(int mat[][MAX], int nr, int nc);
bool riconosciRegione(int mat[][MAX], int indexR, int indexC, int nr, int nc, int *base, int *altezza);
bool isInizioRegione(int mat[][MAX], int indexR, int indexC, int nr, int nc);
int calcolaAltezza(int mat[][MAX], int indexR, int indexC, int nr, int nc);
int calcolaLarghezza(int mat[][MAX], int indexR, int indexC, int nr, int nc);

int main()
{
    int nr, nc;
    int mat[MAX][MAX];

     /* Acquisizione della matrice da file. Acquisico le dimensioni effettive della matrice passando
        NR e NC by reference (ovvero passo alla funzione dei puntatori che puntano a NR e NC). */
    leggiMatrice("file.txt", mat, &nr, &nc);

    /* Individuo e stampo le varie regioni nere. */
    findRegioni(mat, nr, nc);
    return 0;
}




/* Funzione che legge la matrice e le sue dimensioni effettive da file, passando queste by reference. */
void leggiMatrice(char nomeFile[], int mat[][MAX], int *nr, int *nc){
    FILE *fi;
    int i, j;

    /* Apro il file. Se il file non si apre correttamente stampo un messaggio di errore ed
       esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Acquisisco le dimensioni effettive della matrice. Poiché NR e NC sono passati by reference,
       non metto la "&": NR e NC sono gia' dei puntatori. */
    fscanf(fi, "%d %d", nr, nc);

    /* Leggo la matrice dal file. */
    /* Poiché NR e NC sono passati by reference (ovvero sono dei puntatori) per poter utilizzare le
       dimensioni effettive della matrice nei CICLI FOR devo usare il VALORE PUNTATO DA NR e NC */
    for(i=0; i<(*nr); i++){
        for(j=0; j<(*nc); j++){
            fscanf(fi, "%d", &mat[i][j]);
        }
    }
    fclose(fi);
    return;
}




/* Funzione che determina e stampa le regioni nere piu' grandi per altezza, larghezza e area totale. */
void findRegioni(int mat[][MAX], int nr, int nc){
    int i, j, altezza, base, area;

    printf("Le regioni nere presenti sono:\n");
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            /* Verifico se la cella MAT[I][J] e' l'inizio di una regione nera. In caso affermativo, vengono calcolati la BASE e l'ALTEZZA nella
               funzione RICONOSCI REGIONE (acquisisco i loro valori passando BASE E ALTWZZA by reference, ovvero passo alla funzione dei puntatori
               che puntano a BASE e ALTEZZA) e successivamente nell'IF l'area. Infine stampo il suo estremo superiore e i valori di BASE, ALTEZZA
               e AREA. */
            if(riconosciRegione(mat, i, j, nr, nc, &base, &altezza)){
                area=base*altezza;
                printf("Estremo superiore sinistro = <%d, %d>: b = %d, h = %d, Area = %d\n", i,j, base, altezza, area);
            }
        }
    }
    return;
}




/* Funzione che permette, data una cella, di determinare se e' una regione nera o meno. In caso affermativo, calcolo la sua base e la sua altezza
   (valori che sono passati by reference). */
bool riconosciRegione(int mat[][MAX], int indexR, int indexC, int nr, int nc, int *base, int *altezza){

    /* Se la cella MAT[INDEX_R][INDEX_C] e' l'inizio di una regione nera: */
    if(mat[indexR][indexC]==NERO && isInizioRegione(mat, indexR, indexC, nr, nc)){
        /* Calcolo la sua altezza (essendo ALTEZZA un puntatore, salvo il valore ottenuto nella VARIABILE PUNTATA DA ALTEZZA). */
        (*altezza)=calcolaAltezza(mat, indexR, indexC, nr, nc);

        /* Calcolo la sua base (essendo BASE un puntatore, salvo il valore ottenuto nella VARIABILE PUNTATA DA BASE). */
        (*base)=calcolaLarghezza(mat, indexR, indexC, nr, nc);
        /* Ritorno VERO al chiamante. */
        return true;
    }
    /* Se non sono entrato nell'IF, vuol dire che MAT[INDEX_R][INDEX_C] non e' l'inizio di una regione nera:
       ritorno FALSO al chiamante. */
    return false;
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
int calcolaLarghezza(int mat[][MAX], int indexR, int indexC, int nr, int nc){
    int j, larghezza=0;

    /* Scorro la riga INDEXR a partire dalla colonna INDEXC fino a quando non incontro una
       cella BIANCA oppure fino alla fine della riga. Durante il ciclo conto il numero di
       celle NERE. */
    for(j=indexC; mat[indexR][j]==NERO && j<nc; j++){
        larghezza++;
    }
    return larghezza;
}
