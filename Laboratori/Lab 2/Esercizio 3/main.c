#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXS 20
#define MAXCS 6
#define MAXR 201
#define MAXP 26

typedef struct{
    char parola[MAXP];
    int posP;
}Occorrenza;

typedef struct{
    char str[MAXCS];
    Occorrenza occ[10];
    int dim;
}Sequenza;

int leggiSequenze(char nomeFile[], Sequenza sequenze[]);
void findOccorrenzeSequenze(char nomeFile[], Sequenza sequenze[], int dim);
void getParola(char riga[], int start, char parola[]);
void getStringaMinuscola(char str[], char strMin[]);
void stampaOccorrenze(Sequenza sequenze[], int dim);

int main()
{
    int nSeq;
    Sequenza sequenze[MAXS];

    /* Lettura delle sequenze dal file. */
    nSeq=leggiSequenze("sequenze.txt", sequenze);

    /* Lettura del file contenente il testo. Ogni parola del testo che contiene una o piu' sequenze, viene salvata
       tra le occorrenze di queste insieme alla sua posizione nel testo. */
    findOccorrenzeSequenze("testo.txt", sequenze, nSeq);

    /* Stampo, per ogni occorrenza, le parole del testo che la contengono e le relative posizioni. */
    stampaOccorrenze(sequenze, nSeq);
    return 0;
}




/* Funzione che permettere di leggere le sequenze da file. */
int leggiSequenze(char nomeFile[], Sequenza sequenze[]){
    FILE *fi;
    int i, dim;

    /* Apro il file. Se il file non si apre correttamente stampo un messaggio di errore ed esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Acquisisco il numero effettivo delle sequenze. */
    fscanf(fi, "%d", &dim);

    /* Leggo le sequenze dal file. */
    for(i=0; i<dim; i++){
        fscanf(fi, "%s", sequenze[i].str);

        /* Per ogni sequenza, inizializzo il numero di occorrenze a 0. */
        sequenze[i].dim=0;
    }
    fclose(fi);
    return dim;
}




/* Funzione che permette di leggere il file contenente il testo per riga. Per ogni riga, reperisco le parole e verifico se ciascuna di queste
   contenga una o piu' delle sequenze. In caso positivo salvo la parola e la sua posizione nel testo tra le occorrenze delle sequenze
   contenute nella parola. */
void findOccorrenzeSequenze(char nomeFile[], Sequenza sequenze[], int dim){
    FILE *fi;
    int i, nP=0, lenP, j;
    char parola[MAXP], parolaMin[MAXP], seqMin[MAXCS];
    char riga[MAXR];

    /* Apro il file contenente il testo. Se il file non si apre correttamente stampo un messaggio di errore ed esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Leggo il file riga per riga. */
    while(fgets(riga, MAXR, fi)){
        /* Scorro la riga. */
        for(i=0; riga[i]|='\0'; i++){
            /* Se trovo un carattere alfanumerico vuol dire che ho trovato l'inizio di una parola*/
            if(isalnum(riga[i])){
                /* Reperisco la parola e incremento il contatore NP, che tiene il conto del
                   numero di parole trovate (tale valore corrisponde alla posizione nel testo
                   della parola trovata). */
                getParola(riga, i, parola);
                lenP=strlen(parola);
                nP++;

                /* Trasformo la parola in minuscola. */
                getStringaMinuscola(parola, parolaMin);

                /* Per ogni parola, scorro le sequenze. */
                for(j=0; j<dim; j++){
                    /* Continuo se la sequenza ha gia' 10 occorrenze. */
                    if(sequenze[j].dim==10){
                        continue;
                    }
                    /* Altrimenti trasformo la sequenza in minuscola. */
                    getStringaMinuscola(sequenze[j].str, seqMin);

                    /* Se la sequenza e' sottostringa della parola, salvo la parola e la posizione della
                       parola tra le occorrenze della sequenza. */
                    if(strstr(parolaMin, seqMin)!=NULL){
                        sequenze[j].occ[sequenze[j].dim].posP=nP;
                        strcpy(sequenze[j].occ[sequenze[j].dim].parola, parola);
                        sequenze[j].dim++;
                    }
                }
                /* Incremento I fino alla fine della parola. */
                i+=lenP-1;
            }
        }
    }
    fclose(fi);
    return;
}




/* Funzione che, data una riga, permette di ricavare una parola contenuta nella riga, la cui prima lettera e' sita all'indice START.
   N.B. Con PAROLA si intende una sequenza di caratteri alfanumerici contigui, separata da spazi o segni di punteggiatura. */
void getParola(char riga[], int start, char parola[]){
    int i;

    i=start;
    while(riga[i]!='\0' && isalnum(riga[i])){
        parola[i-start]=riga[i];
        i++;
    }
    parola[i-start]='\0';
    return;
}




/* Funzione che permette di convertire una stringa minuscola e salvarla in un altro vettore di caratteri. */
void getStringaMinuscola(char str[], char strMin[]){
    int i;

    for(i=0; str[i]!='\0'; i++){
        strMin[i]=tolower(str[i]);
    }
    strMin[i]='\0';
    return;
}




/* Funzione che permette di stampare le occorrenze di ogni sequenza. */
void stampaOccorrenze(Sequenza sequenze[], int dim){
    int i, j;

    for(i=0; i<dim; i++){
        if(sequenze[i].dim==0){
            printf("La sequenza %s non e' contenuta in alcuna parola nel testo.\n\n", sequenze[i].str);
        }
        else{
            printf("La sequenza %s e' contenuta nelle seguenti parole:\n", sequenze[i].str);
            for(j=0; j<sequenze[i].dim; j++){
                printf("%s (parola in posizione %d nel testo)\n", sequenze[i].occ[j].parola, sequenze[i].occ[j].posP);
            }
            printf("\n");
        }
    }
    return;
}
