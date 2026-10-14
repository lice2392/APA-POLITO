#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXR 201
#define MAXP 21
#define MAXD 30

typedef struct{
    char parola[MAXP];
    int compresso;
}Coppia;

int leggiDizionario(char nomeFile[], Coppia dizionario[]);
void leggiTesto(char nomeFile[], Coppia dizionario[], int S);
void getParola(char riga[], int start, int dimR, char parola[]);
void codificaParola(char parola[], Coppia dizionario[], int S);
int strStrMia(char source[], char sub[]);

int main()
{
    Coppia dizionario[MAXD];
    int S;

    /* Lettura da file del dizionario. */
    S=leggiDizionario("dizionario.txt", dizionario);

    leggiTesto("sorgente.txt", dizionario, S);
    return 0;
}



/* Funzione che legge il dizionario e restituisce il numero di coppie lette. */
int leggiDizionario(char nomeFile[], Coppia dizionario[]){
    FILE *fi;
    int S, i;

    /* Apro il file. Se il file non si apre correttamente stampo un messaggio di errore ed esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Acquisisco il numero effettivo di coppie. */
    /* Con il comando '%*c' evito che l'a-capo venga salvato nel buffer e letto successivamente. */
    fscanf(fi, "%d%*c", &S);

    /* Leggo il dizionario dal file. */
    /* Ogni coppia e' nella forma: $<INTERO>$ <PAROLA>. Evito la lettura dei '$' ed evito che l'a-capo venga
       salvato nel buffer e letto successivamente. */
    for(i=0; i<S; i++){
        fscanf(fi, "%*c%d%*c %s%*c", &dizionario[i].compresso, dizionario[i].parola);
    }
    fclose(fi);
    return S;
}




/* Funzione che legge il file sorgente e lo ricodifica consultando il dizionario. */
void leggiTesto(char nomeFile[], Coppia dizionario[], int S){
    FILE *fi, *fo;
    char riga[MAXR], parola[MAXP];
    int lenR, i, lenP;

    /* Apro il file sorgente in lettura. Se il file non si apre correttamente stampo un messaggio di errore ed esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Apro il file su cui andro' a scrivere il file ricodificato in scrittura. */
    fo=fopen("ricodificato.txt", "w");

    /* Leggo il file sorgente per riga. */
    while(fgets(riga, MAXR, fi)){
        /* Determino la lunghezza della riga. */
        lenR=strlen(riga);
        /* Scorro la riga. */
        for(i=0; i<lenR; i++){
            /* Se il carattere non e' alfabetico, lo scrivo sul file di uscita. */
            if(!isalpha(riga[i])){
                fprintf(fo, "%c", riga[i]);
            }
            else{
                /* Altrimenti reperisco la parola e la sua dimensione. */
                getParola(riga, i, lenR, parola);
                lenP=strlen(parola);

                /* Cerco nel dizionario se c'e' una sostituzione possibile o meno.
                   Se c'e' scrivo sul file di uscita la parola codificata, altrimenti la
                   parola originale. */
                codificaParola(parola, dizionario, S);
                fprintf(fo, "%s", parola);

                /* Faccio avanzare i fino alla fine della parola. */
                i+=lenP-1;
            }
        }
    }
    fclose(fi);
    fclose(fo);
    return;
}




/* Funzione che reperisce una parola da una riga. */
void getParola(char riga[], int start, int dimR, char parola[]){
    int i, index=0;

    i=start;
    while(i<dimR && riga[i]!=' '){
        parola[index++]=riga[i];
        i++;
    }
    parola[index]='\0';
    return;
}




/* Funzione che cerca nel dizionario se c'e' una sottostringa di PAROLA da codificare. */
void codificaParola(char parola[], Coppia dizionario[], int S){
    int i, index, start, lenP, j;
    char codificata[MAXP];

    /* Scorro il dizionario e determino se c'e' una sottostringa di PAROLA da codificare.
       In caso affermativo, START sara' diverso da -1: salvo l'indice della coppia nel
       dizionario. */
    start=-1;
    for(i=0; i<S && start==-1; i++){
        start=strStrMia(parola, dizionario[i].parola);
        if(start!=-1){
            index=i;
        }
    }

    /* Esco dalla funzione se non c'e' una sottostringa di PAROLA da codificare. */
    if(start==-1){
        return;
    }

    /* Se invece c'e', creo la parola codificata. */
    lenP=strlen(parola);
    j=0;
    for(i=0; i<lenP;){
        if(i!=start){
            codificata[j++]=parola[i++];
        }
        else{
            codificata[j++]='$';
            j+=sprintf(codificata+j, "%d", dizionario[index].compresso);
            codificata[j++]='$';
            i+=strlen(dizionario[index].parola);
        }
    }
    codificata[j]='\0';
    strcpy(parola, codificata);
    return;
}




/* Funzione che determina se SUB e sottostringa di SOURCE. */
int strStrMia(char source[], char sub[]){
    int lenS, lenSub;
    int i, j, start;

    /* Determino le lunghezze di SOURCE e SUB. */
    lenS=strlen(source);
    lenSub=strlen(sub);

    /* Esco dalla funzione se la lunghezza di SUB e' maggiore di quella di SOURCE: SUB non
       puo' essere sottostringa di SOURCE. */
    if(lenSub>lenS)
        return -1;

    /* Scorro la stringa SOURCE. */
    j=0;
    for(i=0; i<lenS && j<lenSub;){
        /* Se trovo una corrispondenza: */
        if(source[i]==sub[j]){
            /* Salvo l'indice di inizio di SOURCE. */
            if(j==0){
                start=i;
            }
            /* Scorro entrambe le stringhe contemporaneamente per controllare gli altri caratteri. */
            while(source[i]==sub[j] && i<lenS && j<lenSub){
                i++;
                j++;
            }
            /* Se sono arrivata fino alla fine di SUB vuol dire che SUB e' sottostringa di SOURCE: ritorno l'indice
               di inizio della sottostringa salvata in START. */
            if(j==lenSub){
                return start;
            }
            /* Altrimenti rincomincio a scorrere SOURCE dal carattere successivo a START e azzero l'indice di SUB. */
            i=start+1;
            j=0;
        }
        /* Se non trovo alcuna corrispondenza, continuo a scorrere SOURCE. */
        else{
            i++;
        }
    }

    /* Se sono arrivata fino a qua, vuol dire che SUB non e' sottostringa di SOURCE. */
    return -1;
}



