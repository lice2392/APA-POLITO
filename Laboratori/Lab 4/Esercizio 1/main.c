#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);
void scambia(int *a, int *b);

int main()
{
    int a, b;

    /* Inserimento di due valori interi positivi. */
    printf("Inserisci un numero intero positivo: ");
    scanf("%d", &a);
    printf("\nInserisci un numero intero positivo: ");
    scanf("%d", &b);

    /* Stampo un messaggio di errore se uno dei valori inseriti non è un intero positivo. */
    if(a<=0 || b<=0){
        printf("\nImpossibile calcolare il MASSIMO COMUN DIVISORE: i due numeri devono essere interi positivi.\n");
    }
    /* Se invece sia A che B sono interi positivi, calcolo il loro MASSIMO COMUN DIVISORE e lo stampo. */
    else{
        printf("\nIl MASSIMO COMUN DIVISORE di %d e %d e' %d.\n", a, b, gcd(a, b));
    }

    return 0;
}




/* Funzione che determina il MASSIMO COMUN DIVISORE di due
   valori interi positivi A e B. */
int gcd(int a, int b){
    /* Condizione di terminazione. */
    if(a==b){
        return a;
    }
    if(a==0){
        return b;
    }
    if(b==0){
        return a;
    }


    /* Nel calcolo del MASSIMO COMUN DIVISOREe si assume che A > B. Se tale
       condizione non è soddisfatta, si scambiano A e B. */
    if(a<b){
        scambia(&a, &b);
    }

    /* Se A e B sono entrambi pari. */
    if(a%2==0 && b%2==0){
        return 2*gcd(a/2, b/2);
    }

    /* Se A è dispari e B è pari. */
    if(a%2!=0 && b%2==0){
        return gcd(a, b/2);
    }

    /* Se A è pari e B è dispari. */
    if(a%2==0 && b%2!=0){
        return gcd(a/2, b);
    }

    /* Se A e B sono dispari. */
    return gcd((a-b)/2, b);
}




/* Funzione che permette di scambiare due valori. */
void scambia(int *a, int *b){
    int tmp;

    tmp=(*a);
    (*a)=(*b);
    (*b)=tmp;
    return;
}
