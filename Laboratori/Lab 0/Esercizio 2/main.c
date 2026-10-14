#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define C 21

void leggiEConta(char nomeFile[], int n);
bool isVocale(char car);
int conta(char S[], int n);

int main()
{
    char nomeFile[C];
    int n;

    /* Acquisizione da tastiera del nome del file. */
    printf("Inserisci il nome del file da leggere: ");
    scanf("%s", nomeFile);

    /* Acquisizione da tastiera della lunghezza delle sottostringhe. */
    printf("Inserisci la lunghezza delle sottostringhe: ");
    scanf("%d", &n);

    /* Lettura del file e conteggio delle sottostringhe di lunghezza
       N che contengono due vocali. */
    leggiEConta(nomeFile, n);
    return 0;
}



/* Funzione che legge il file e per ogni parola letta conta quante sottostringhe di lunghezza N contengono due vocali. */
void leggiEConta(char nomeFile[], int n){
    FILE *fi;
    char parola[C];
    int nSub;

    /* Apro il file. Se il file non si apre correttamente stampo un messaggio di errore ed esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Leggo il file. */
    while(fscanf(fi, "%s", parola)==1){
        /* Per ogni parola, conto quante sottostringhe di lunghezza N sono contenuti nella parola letta. */
        nSub=conta(parola, n);
        printf("Per la parola %s, il numero di sottostringhe di lunghezza %d contenenti due vocali sono %d\n", parola, n, nSub);
    }
    fclose(fi);
    return;
}




/* Funzione che conta quante sottostringhe di lunghezza N sono contenuti nella parola contenuta in S. */
int conta(char S[], int n){
    char sub[C];
    int i, len, j, nVocali, cnt=0;

    /* Determino la lunghezza della parola. */
    len=strlen(S);

    /* Controllo che la lunghezza N delle sottostringhe non superi quella della parola. */
    if(n>len){
        printf("\nLa lunghezza n = %d supera quella della parola (len = %d).\n", n, len);
        return 0;
    }

    printf("\n");
    /* Scorro la parola S. */
    for(i=0; i+n<=len; i++){
        /* Per ogni indice, copio in SUB la sottostirnga di N caratteri che inizia da S[I]. */
        strncpy(sub, S+i, n);
        sub[n]='\0';

        /* Scorro la sottostringa e conto il numero di vocali. */
        nVocali=0;
        for(j=0; j<n; j++){
            /* Conto ogni volta che incontro una vocale. */
            if(isVocale(sub[j])){
                nVocali++;
            }
        }

        /* Se la sottostringa contiene 2 vocali, la stampo e conto. */
        if(nVocali==2){
            printf("%s\n", sub);
            cnt++;
        }
    }
    return cnt;
}




/* Funzione che determina se un carattere e' una vocale o meno. */
bool isVocale(char car){
    char carMin;

    /* Trasformo il carattere CAR in minuscolo. */
    carMin=tolower(car);

    return ((carMin=='a') || (carMin=='e') || (carMin=='i') || (carMin=='o') || (carMin=='u'));
}
