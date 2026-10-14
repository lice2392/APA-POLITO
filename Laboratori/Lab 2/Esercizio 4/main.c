#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define filein "sort.txt"
#define maxN 100

void selectionSort(int A[], int N);
void insertionSort(int A[], int N);
void shellSort(int A[], int N);
void stampaVettore(int A[], int N);


int main(int argc, char **argv) {
  int A[maxN], A_sel[maxN], A_shell[maxN], A_ins[maxN], N, S;
  int i, j;
  FILE *fi;

  /* Apro il file. Se il file non si apre correttamente stampo un messaggio di errore ed esco. */
  fi=fopen("sort.txt", "r");
  if(fi==NULL){
    printf("Errore nell'apertura del file.\n");
    exit(EXIT_FAILURE);
  }

  /* Leggo il numero di vettori presenti nel file. */
  fscanf(fi, "%d", &S);

  /* Leggo i vettori presenti nel file. */
  for(i=0;i<S;i++) {
    /* Per ogni vettore: */
    /* Leggo la sua dimensione effettiva. */
    fscanf(fi, "%d", &N);
    /* Leggo il vettore. */
    for(j=0; j<N; j++){
        fscanf(fi, "%d", &A[j]);
        /* Salvo ogni elemento nei vettori di supporto che saranno usati negli
           algoritmi di ordinamento. */
       A_sel[j]=A_shell[j]=A_ins[j]=A[j];
    }
    /* Stampo il vettore appena letto. */
    printf("Vettore %d: ", i+1);
    stampaVettore(A, N);
    /* Chiamo l'INSERTION SORT. */
    insertionSort(A_ins, N);
    printf("\n");
    /* Chiamo il SELECTION SORT. */
    selectionSort(A_sel, N);
    printf("\n");
    /* Chiamo lo SHELL SORT. */
    shellSort(A_shell, N);
    printf("\n\n");
  }
  fclose(fi);
  return 0;
}




/* Algoritmo di ordinamento SELECTION SORT. */
void selectionSort(int A[], int N) {
  int i, j, l=0, r=N-1, min, tmp;
  int cntEs = 0, cntIn = 0, cntSwap = 0, cntTot = 0;

  printf("---SELECTION SORT---\n");
  for (i=l; i<r; i++) {
      cntEs++;
      min=i;
      for (j=i+1; j<=r; j++) {
        cntIn++;
        if (A[j] < A[min])
        min = j;
      }
      if (min != i) {
        tmp = A[min];
        A[min] = A[i];
        A[i] = tmp;
        cntSwap++;
      }
      printf("Passo %d: N.Iterazioni Interne = %d\n", i, cntIn);
      cntTot+=cntIn;
      cntIn=0;
  }
  cntTot+=cntEs;
  printf("N.Iterazioni Esterne = %d, N.Scambi = %d, N.Iterazioni Totali = %d\n", cntEs, cntSwap, cntTot);
}




/* Algoritmo di ordinamento INSERTION SORT. */
void insertionSort(int A[], int N) {
  int i, j, l=0, r=N-1, x;
  int cntEs = 0, cntIn = 0, cntSwap = 0, cntTot = 0;

  printf("---INSERTION SORT---\n");
  for (i=l+1; i<=r; i++) {
    cntEs++;
    x = A[i];
    j = i-1;
    while (j>=l && x<A[j]) {
      cntIn++;
      A[j+1] = A[j];
      cntSwap++;
      j--;
    }
    printf("Passo %d: N.Iterazioni Interne = %d\n", i, cntIn);
    cntTot+=cntIn;
    cntIn=0;
    A[j+1] = x;
  }
  cntTot+=cntEs;
  printf("N.Iterazioni Esterne = %d, N.Scambi = %d, N.Iterazioni Totali = %d\n", cntEs, cntSwap, cntTot);
  return;
}




/* Algoritmo di ordinamento SHELL SORT. */
void shellSort(int A[], int N) {
  int i, j, h=1, l=0, r= N-1, tmp;
  int cntEs = 0, cntIn = 0, cntSwap = 0, cntTot = 0, cntEsTot = 0;

  while (h < N/3)
    h = 3*h +1;

  while(h >= 1) {
    printf("Ciclo for per h = %d\n", h);
    for (i = l+h; i <= r; i++) {
      cntEs++;
      tmp = A[i];
      j = i;
      while (j >= l+h && tmp < A[j-h]) {
        A[j] = A[j-h];
        j -=h;
        cntIn++;
        cntSwap++;
      }
      printf("Passo %d: N.Iterazioni Interne = %d\n", i, cntIn);
      cntTot+=cntIn;
      cntIn=0;
      A[j] = tmp;
    }
    printf("N.Iterazioni Esterne = %d\n", cntEs);
    h = h/3;
    cntEsTot +=cntEs;
    cntEs=0;

  }
  cntTot+=cntEsTot;
  printf("N.Iterazioni Esterne Totali = %d,  N.Scambi = %d, N.Iterazioni Totali = %d\n", cntEsTot, cntSwap, cntTot);
}




/* Funzione che stampa un vettore. */
void stampaVettore(int A[], int N) {
  int i;
  for(i=0;i<N;i++)
    printf("%d ", A[i]);
  printf("\n");
}
