#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAXC 31
#define MAX 1000

typedef struct{
    char codiceTratta[MAXC], partenza[MAXC], arrivo[MAXC];
    char data[MAXC];
    char oraP[MAXC], oraA[MAXC];
    int ritardo;
}Tratta;

typedef enum{errato=-1, stampa, o_data, o_codice, o_partenza, o_capolinea, ricerca, fine}Comando;

typedef enum{nessuno=-1, data, codice, partenza, capolinea}Ordinamento;

void leggiTratte(char nomeFile[], Tratta tratte[], int *nTratte);
void stampaTratta(Tratta corsa, FILE *fi);
Comando comStringToEnum(char comando[]);
void stringToMinuscola(char str[]);
void selezionaDati(Tratta tratte[], int nTratte, Comando com, Ordinamento *or);
void mergeSort(Tratta tratte[], int nTratte, Ordinamento or);
void mergeSortR(Tratta A[], Tratta B[], int left, int right, Ordinamento or);
void merge(Tratta A[], Tratta B[], int left, int middle, int right, Ordinamento or);
int compare(Tratta t1, Tratta t2, Ordinamento or);
bool ricercaLineare(Tratta tratte[], int nTratte, char partenza[]);
int ricercaDicotomica(Tratta tratte[], int nTratte, char partenza[]);
int ricercaDicotomicaR(Tratta tratte[], int left, int right, char partenza[]);


int main()
{
    int nTratte;
    Tratta tratte[MAX];
    Comando com;
    char comando[MAXC];
    Ordinamento orVett;

    /* Acquisizione delle tratte da file. */
    leggiTratte("corse.txt", tratte, &nTratte);

    /* Inizializzo l'ordinamento con NESSUNO: a questo punto, la base dati non e' ancora
       ordinata. */
    orVett=nessuno;

    /* Ciclo che permette all'utente di poter eseguire piu' interrogazioni fino a quando non decide
       di terminare. */
    do{
        printf("Inserisci:\n");
        printf(" -'stampa' per stampare la base dati.\n");
        printf(" -'o_data' per ordinare la base dati per data.\n");
        printf(" -'o_partenza' per ordinare la base dati per stazione di partenza.\n");
        printf(" -'o_capolinea' per ordinare la base dati per stazione di arrivo.\n");
        printf(" -'o_codice' per ordinare la base dati per codice di tratta.\n");
        printf(" -'ricerca' per cercare una tratta per stazione di partenza (anche parziale).\n");
        printf(" -'fine' per terminare.\n");
        printf("Che cosa vuoi fare? ");
        fgets(comando, MAXC, stdin);

        /* Elimino il '\n' presente nella stringa dopo la FGETS, sostituendolo con '\0'. */
        comando[strcspn(comando, "\n")]='\0';

        /* Reperisco l'enumerativo corrispondente al comando inserito dall'utente. */
        com=comStringToEnum(comando);

        /* Interrogazione della base dati. */
        /* Passo l'ordinamento per riferimento, in quanto il suo valore viene modificato
           all'interno della funzione, nel caso in cui l'utente voglia ordinare la base dati.
           In questo modo, la modifica non sara' limitata solo alla funzione SELEZIONA DATI ma
           sara' visibile anche al chiamante. */
        selezionaDati(tratte, nTratte, com, &orVett);
    }while(com!=fine);
    return 0;
}




/* Funzione che permette di interrogare la basi dati. */
void selezionaDati(Tratta tratte[], int nTratte, Comando com, Ordinamento *orVett){
    char sPartenza[MAXC], comStampa[MAXC];
    bool trovato;
    FILE *fi;
    int i, indexFind, len;

    switch(com){
        /* Stampo,o a scelta se a video o su file, i contenuti della base dati. */
        case stampa:
            /* Faccio inserire all'utente dove vuole stampare. */
            printf("\nDigita:\n");
            printf(" -'video' se vuoi stampare su video.\n");
            printf(" -'file' se vuoi stampare su file.\n");
            printf("Dove vuoi stampare? ");
            fgets(comStampa, MAXC, stdin);
            comStampa[strcspn(comStampa, "\n")]='\0';

            /* Trasformo il comando digitato dall'utente in stringa minuscola. */
            stringToMinuscola(comStampa);

            /* Se l'utente vuole stampare su file, apro il file su cui scrivere. */
            if(strcmp(comStampa, "file")==0){
                fi=fopen("log.txt", "w");
            }
            /* Se l'utente vuole stampare sa video, pongo il puntatore a file pari a STDOUT e
               stampo un a-capo prima della stampa della basi dati. */
            else if(strcmp(comStampa, "video")==0){
                fi=stdout;
                printf("\n");
            }
            /* Caso in cui l'utente abbia digitato un comando errato: stampo un messaggio di errore
               ed esco dalla funzione. */
            else{
                printf("\nComando errato. Impossibile stampare la basi dati.\n\n");
                return;
            }

            /* Se l'utente ha inserito un comando corretto, stampo la base dati. */
            fprintf(fi, "---BASE DATI---\n");
            for(i=0; i<nTratte; i++){
                stampaTratta(tratte[i], fi);
            }

            /* Se l'utente vuole stampare su file, stampo un messaggio di successo alla fine della
               stampa. */
            if(strcmp(comStampa, "file")==0){
                printf("\nSTAMPA ESEGUITA CORRETTAMENTE SUL FILE.\n");
            }
            break;


        /* Ordino la base dati per stazione di partenza. */
        case o_partenza:
            /* Chiamo l'algoritmo di MERGE SORT che ordina il vettore per FERMATA DI PARTENZA,
               grazie al tipo di ordinamento passato alla funzione. */
            mergeSort(tratte, nTratte, partenza);
            /* Ho ordinato il vettore per FERMATA DI PARTENZA: modifico il puntatore che punta alla
               variabile che ne tiene traccia. */
            (*orVett)=partenza;
            /* Stampo un messaggio di successo. */
            printf("\nORDINAMENTO ESEGUITO CON SUCCESSO.\n");
            break;



        /* Ordino la base dati per stazione di arrivo. */
        case o_capolinea:
            /* Chiamo l'algoritmo di MERGE SORT che ordina il vettore per FERMATA DI ARRIVO,
               grazie al tipo di ordinamento passato alla funzione. */
            mergeSort(tratte, nTratte, capolinea);
            /* Ho ordinato il vettore per FERMATA DI ARRIVO: modifico il puntatore che punta alla
               variabile che ne tiene traccia. */
            (*orVett)=capolinea;
            /* Stampo un messaggio di successo. */
            printf("\nORDINAMENTO ESEGUITO CON SUCCESSO.\n");
            break;



        /* Ordino la base dati per data. */
        case o_data:
            /* Chiamo l'algoritmo di MERGE SORT che ordina il vettore per DATA, grazie al tipo di
               ordinamento passato alla funzione. */
            mergeSort(tratte, nTratte, data);
            /* Ho ordinato il vettore per DATA: modifico il puntatore che punta alla variabile
               che ne tiene traccia. */
            (*orVett)=data;
            /* Stampo un messaggio di successo. */
            printf("\nORDINAMENTO ESEGUITO CON SUCCESSO.\n");
            break;


        /* Ordino la base dati per codice di tratta. */
        case o_codice:
            /* Chiamo l'algoritmo di MERGE SORT che ordina il vettore per CODICE TRATTA,
               grazie al tipo di ordinamento passato alla funzione. */
            mergeSort(tratte, nTratte, codice);
            /* Ho ordinato il vettore per CODICE TRATTA: modifico il puntatore che punta alla
               variabile che ne tiene traccia. */
            (*orVett)=codice;
            /* Stampo un messaggio di successo. */
            printf("\nORDINAMENTO ESEGUITO CON SUCCESSO.\n");
            break;


        /* Ricerco una tratta per stazione di partenza (anche parziale). */
        case ricerca:
            /* Faccio inserire all'utente una stazione di partenza. */
            printf("\nInserisci una stazione di partenza: ");
            fgets(sPartenza, MAXC, stdin);
            sPartenza[strcspn(sPartenza, "\n")]='\0';

            /* Se il vettore e' ordinato per FERMATA DI PARTENZA utilizzo la
               ricerca dicotomica. */
            if((*orVett)==partenza){
                printf("\nLe corse aventi come stazione di partenza %s sono:\n", sPartenza);
                /* La ricerca dicotomica ritorna l'indice di un'occorrenza trovata. Essendo questa
                   una ricerca parziale (non sto cercando una tratta che ha come STAZIONE DI
                   PARTENZA esattamente PARTENZA ma tutte le tratte la cui STAZIONE DI PARTENZA
                   comincia con PARTENZA (PARTENZA puo' essere esattamente una stazione completa,
                   ma anche una porzione inziale), e' possibile che ci siano anche altri
                   risultati. */
                indexFind=ricercaDicotomica(tratte, nTratte, sPartenza);
                /* Se la ricerca dicotomica non ha trovato nulla, stampo un messaggio di
                   insuccesso. */
                if(indexFind==-1){
                    printf("Non esiste alcuna tratta.\n");
                }
                /* Altrimenti:
                    1) Stampo la tratta che si trova ad INDEXFIND;
                    2) Dato INDEXFIND e sapendo che il vettore e' ordinato per STAZIONE DI
                       PARTENZA, cerco se ci sono altre occorrenze sopra e sotto INDEXFIND.
                       In tal caso le stampo. */
                else{
                    stampaTratta(tratte[indexFind], stdout);
                    len=strlen(sPartenza);
                    i=indexFind-1;
                    while(i>=0 && strncmp(tratte[i].partenza, sPartenza, len)==0){
                        stampaTratta(tratte[i], stdout);
                        i--;
                    }
                    i=indexFind+1;
                    while(i<nTratte && strncmp(tratte[i].partenza, sPartenza, len)==0){
                        stampaTratta(tratte[i], stdout);
                        i++;
                    }
                }
            }

            /* Se, invece, il vettore non e' ordinato per FERMATA DI PARTENZA utilizzo la
               ricerca lineare. */
            else{
                printf("\nLe corse aventi come stazione di partenza %s sono:\n", sPartenza);
                trovato=ricercaLineare(tratte, nTratte, sPartenza);
                if(!trovato){
                    printf("Non esiste alcuna tratta.\n");
                }
            }
            break;

        /* Termine del programma. */
        case fine:
            printf("\nPROGRAMMA TERMINATO.\n");
            break;

        /* Comando errato. */
        default:
            printf("\nComando errato. Reinseriscilo.\n");
    }
    printf("\n");
    return;
}




/* Funzione che legge le tratte e le sue dimensioni effettive da file. */
void leggiTratte(char nomeFile[], Tratta tratte[], int *nTratte){
    FILE *fi;
    int i;

    /* Apro il file. Se il file non si apre correttamente stampo un messaggio di errore ed
       esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Acquisisco le dimensioni effettive delle tratte. */
    fscanf(fi, "%d", nTratte);

    /* Leggo le tratte dal file. */
    for(i=0; i<(*nTratte); i++){
        fscanf(fi, "%s %s %s %s %s %s %d", tratte[i].codiceTratta, tratte[i].partenza, tratte[i].arrivo, tratte[i].data, tratte[i].oraP, tratte[i].oraA, &tratte[i].ritardo);
    }
    fclose(fi);
    return;
}




/* Funzione che stampa una tratta. */
void stampaTratta(Tratta corsa, FILE *fi){
    fprintf(fi, "%s %s %s %s %s %s %d\n", corsa.codiceTratta, corsa.partenza, corsa.arrivo, corsa.data, corsa.oraP, corsa.oraA, corsa.ritardo);
}




/* Funzione che data una stringa, restituisce l'enumerativo di tipo COMANDO corrispondente. */
Comando comStringToEnum(char comando[]){

    /* Trasformo COMANDO in una stringa minuscola. */
    stringToMinuscola(comando);

    /* Restituisco al chiamante l'enumerativo corrispondente alla parola presente nella
       stringa. */
    if(strcmp(comando, "stampa")==0){
        return stampa;
    }
    if(strcmp(comando, "o_data")==0){
        return o_data;
    }
    if(strcmp(comando, "o_codice")==0){
        return o_codice;
    }
    if(strcmp(comando, "o_partenza")==0){
        return o_partenza;
    }
    if(strcmp(comando, "o_capolinea")==0){
        return o_capolinea;
    }
    if(strcmp(comando, "fine")==0){
        return fine;
    }
    if(strcmp(comando, "ricerca")==0){
        return ricerca;
    }
    return errato;
}




/* Funzione che converte la stringa in minuscola. */
void stringToMinuscola(char str[]){
    int i, len;

    len=strlen(str);

    for(i=0; i<len; i++){
        str[i]=tolower(str[i]);
    }
    return;
}




/* Algoritmo di ordinamento MERGE SORT.*/
/* Funzione wrapper. */
void mergeSort(Tratta tratte[], int nTratte, Ordinamento or){
    Tratta B[MAX];
    mergeSortR(tratte, B, 0, nTratte-1, or);
    return;
}


/* Funzione ricorsiva. */
void mergeSortR(Tratta A[], Tratta B[], int left, int right, Ordinamento or){
    int middle;

    /* Condizione di terminazione. */
    if(left>=right){
        return;
    }

    middle=(left+right)/2;

    mergeSortR(A, B, left, middle, or);
    mergeSortR(A, B, middle+1, right, or);
    merge(A, B, left, middle, right, or);
    return;
}


/* Funzione di merge. */
void merge(Tratta A[], Tratta B[], int left, int middle, int right, Ordinamento or){
    int i, j, k;

    i=left;
    j=middle+1;

    for(k=left; k<=right; k++){
        if(i>middle){
            B[k]=A[j++];
        }
        else if(j>right){
            B[k]=A[i++];
        }
        else if(compare(A[i], A[j], or)<=0){
            B[k]=A[i++];
        }
        else{
            B[k]=A[j++];
        }
    }

    for(k=left; k<=right; k++){
        A[k]=B[k];
    }
    return;
}


/* Funzione che confronta due tratte. A seconda del tipo di ordinamento presente nella variabile
   OR, le due tratte vengono confrontate per DATA (a parita' di DATA per ORA), STAZIONE DI PARTENZA,
   STAZIONE DI ARRIVO o CODICE TRATTA. */
int compare(Tratta t1, Tratta t2, Ordinamento or){
    int ret;

    switch(or){
        case data:
            if(strcmp(t1.data, t2.data)==0){
                if(strcmp(t1.oraP, t2.oraP)==0){
                    ret=strcmp(t1.oraA, t2.oraA);
                }
                else{
                    ret=strcmp(t1.oraP, t2.oraP);
                }
            }
            else{
                ret=strcmp(t1.data, t2.data);
            }
            break;
        case partenza:
            ret=strcmp(t1.partenza, t2.partenza);
            break;
        case capolinea:
            ret=strcmp(t1.arrivo, t2.arrivo);
            break;
        case codice:
            ret=strcmp(t1.codiceTratta, t2.codiceTratta);

    }
    return ret;
}




/* Algoritmo di ricerca lineare, che permette di cercare e stampare le tratte che hanno come
   FERMATA DI PARTENZA una stringa che contiene quanto contenuto nella stringa PARTENZA.
   La funzione ritorna VERO se e' stata trovata almeno una tratta, FALSO altrimenti.
   N.B. PARTENZA puo' contenere una FERMATA DI PARTENZA completa o una porzione di essa
        (con porzione si intende la parte iniziale di una STAZIONE DI PARTENZA).  */
bool ricercaLineare(Tratta tratte[], int nTratte, char partenza[]){
    int i;
    bool trovato=false;
    int len;

    len=strlen(partenza);

    for(i=0; i<nTratte; i++){
        if(strncmp(tratte[i].partenza, partenza, len)==0){
            stampaTratta(tratte[i], stdout);
            trovato=true;
        }
    }
    return trovato;
}



/* Algoritmo di ricerca dicotomica, che permette di cercare e stampare la tratta che ha come
   FERMATA DI PARTENZA una stringa che contiene quanto contenuto nella stringa PARTENZA.
   La funzione ritorna l'indice di tale corsa se e' stata trovata, -1 altrimenti.
   Si puo' usare solo se il vettore TRATTE e' ordinato per FERMATA DI PARTENZA.
   N.B. PARTENZA puo' contenere una FERMATA DI PARTENZA completa o una porzione di essa
        (con porzione si intende la parte iniziale di una STAZIONE DI PARTENZA).  */
/* Funzione WRAPPER. */
int ricercaDicotomica(Tratta tratte[], int nTratte, char partenza[]){
    return ricercaDicotomicaR(tratte, 0, nTratte-1, partenza);
}


/* Funzione ricorsiva. */
int ricercaDicotomicaR(Tratta tratte[], int left, int right, char partenza[]){
    int middle, len;

    if(left>right)
        return -1;

    middle=(right+left)/2;
    len=strlen(partenza);

    if(strncmp(tratte[middle].partenza, partenza, len)==0){
        return middle;
    }
    if(strcmp(partenza, tratte[middle].partenza)<0)
        return ricercaDicotomicaR(tratte, left, middle-1, partenza);
    return ricercaDicotomicaR(tratte, middle+1, right, partenza);
}


