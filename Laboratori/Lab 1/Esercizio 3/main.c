#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define MAX 30
#define MAXC 21
#define MAXR 101

typedef struct{
    int nr, nc;
}Dimensioni;

typedef enum {wrong=-1, riga, colonna, fine}Selettore;
typedef enum {errato=-1, su, giu, destra, sinistra}Direzione;

typedef struct{
    Selettore sel;
    int indice;
    Direzione dir;
    int nP;
    bool ok;
}Comando;


Dimensioni leggiMatrice(char nomeFile[], int mat[][MAX]);
void stampa(int mat[][MAX], int nr, int nc);
Comando checkComando(char comando[], int nr, int nc);
Selettore selStringToEnum(char selettore[]);
Direzione dirStringToEnum(char direzione[]);
bool isStringaNumerica(char s[]);
void stringToMinuscola(char s[]);
void ruotaMatrice(int mat[][MAX], int nr, int nc, Comando com);
void ruotaVettore(int vet[], int dim, int P, int dir);
void copiaVettore(int source[], int dest[], int dim);

int main()
{
    char nomeFile[MAXC];
    int mat[MAX][MAX];
    Dimensioni dimMat;
    char comando[MAXR];
    Comando com;

    /* Acquisizione del nome del file da tastiera. */
    printf("Inserisci il nome del file: ");
    fgets(nomeFile, MAXC, stdin);
    /* FGETS salva nella stringa anche il carattere '\n'.
       Tramite la funzione STRCSPN trovo l'indice di '\n' in NOME_FILE e lo sostituisco con '\0'. */
    nomeFile[strcspn(nomeFile, "\n")]='\0';

    /* Acquisizione della matrice da file. */
    dimMat=leggiMatrice(nomeFile, mat);

    /* Stampa della matrice letta. */
    printf("\nLa matrice inserita e':\n");
    stampa(mat, dimMat.nr, dimMat.nc);

    /* Ciclo per permettere all'utente di effettuare ripetutamente delle rotazioni. */
    do{
        /* Inserimento del comando. */
        printf("Inserisci un comando nella forma <selettore> <indice> <direzione> <posizioni>.\n");
        printf(" - SELETTORE = RIGA, COLONNA, FINE.\n");
        printf(" - INDICE = NUMERO COMPRESO TRA 1 e %d, se SELETTORE = RIGA, o NUMERO COMPRESO TRA 1 e %d, se SELETTORE = COLONNA.\n", dimMat.nr, dimMat.nc);
        printf(" - DIREZIONE = SU, GIU, DESTRA, SINISTRA.\n");
        printf(" - N.POSIZIONI = NUMERO INTERO POSITIVO.\n");
        printf("Cosa vuoi fare? ");
        fgets(comando, MAXR, stdin);
        /* FGETS salva nella stringa anche il carattere '\n'.
           Tramite la funzione STRCSPN trovo l'indice di '\n' in COMANDO e lo sostituisco con '\0'. */
        comando[strcspn(comando, "\n")]='\0';
        printf("\n");

        /* Reperisco dalla stringa dalla stringa i vari valori del comando e ne verifico la correttezza. */
        com=checkComando(comando, dimMat.nr, dimMat.nc);

        /* Proseguo e ruoto la matrice se il comando e' corretto e il SELETTORE non e' FINE. */
        if(com.ok && com.sel!=fine){
            ruotaMatrice(mat, dimMat.nr, dimMat.nc, com);
        }
    }while(com.sel!=fine);
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




/* Funzione che stampa la matrice passata come parametro di dimensione NRxNC. */
void stampa(int mat[][MAX], int nr, int nc){
    int i, j;

    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}




/* Funzione che verifica la correttezza del comando inserito e reperisce dalla stringa i vari valori. */
Comando checkComando(char comando[], int nr, int nc){
    char selettore[MAXR], direzione[MAXR], indice[MAXR], posizioni[MAXR];
    Comando com;

    /* Suddivido la stringa comando, che e' nella forma <selettore> <indice> <direzione> <posizioni>, in
       diverse stringhe. */
    sscanf(comando, "%s %s %s %s", selettore, indice, direzione, posizioni);


    /* SELETTORE: trasformo la stringa in ENUM e, nel frattempo, ne verifico la correttezza. */
    com.sel=selStringToEnum(selettore);
    if(com.sel==wrong){
        printf("Comando errato: il SELETTORE puo' essere solo RIGA, COLONNA, FINE. Reinserisci comando.\n\n");
        com.ok=false;
        return com;
    }

    /* Se il selettore e' FINE e' inutile che procedo. */
    if(com.sel==fine){
        com.ok=true;
        return com;
    }


    /* INDICE: verifico che la stringa sia numerica; in caso affermativo la trasformo in intero e, nel frattempo, verifico
               la correttezza del numero inserito. */
    /* Verifica 1: l'indice inserito deve essere un numero. */
    if(!isStringaNumerica(indice)){
        printf("Comando errato: l'INDICE puo' essere solo un valore numerico. Reinserisci comando.\n\n");
        com.ok=false;
        return com;
    }

    /* Verifica 2: l'indice inserito deve essere coerente con le dimensioni della matrice. */
    /* N.B. Le righe e le colonne sono numerata a partire da 1 ma il C le numera a partire da 0.*/
    com.indice=atoi(indice)-1;
    if(com.sel==riga && (com.indice<0 || com.indice>=nr)){
        printf("Comando errato: l'INDICE DI RIGA deve essere un valore compreso tra 1 e %d. Reinserisci comando.\n\n", nr);
        com.ok=false;
        return com;
    }
    if(com.sel==colonna && (com.indice<0 || com.indice>=nc)){
        printf("Comando errato: l'INDICE DI COLONNA deve essere un valore compreso tra 1 e %d. Reinserisci comando.\n\n", nc);
        com.ok=false;
        return com;
    }


    /* DIREZIONE: trasformo la stringa in ENUM e, nel frattempo, ne verifico la correttezza. */
    com.dir=dirStringToEnum(direzione);
    if(com.dir==errato){
        printf("Comando errato: la DIREZIONE puo' essere solo SU, GIU, DESTRA, SINISTRA. Reinserisci comando.\n\n");
        com.ok=false;
        return com;
    }

    /* La RIGA puo' essere ruotata solo a DESTRA o SINISTRA. */
    if(com.sel==riga && (com.dir==su || com.dir==giu)){
        printf("Comando errato: la RIGA pu' essere ruotata solo a DESTRA o SINISTRA. Reinserisci comando.\n\n");
        com.ok=false;
        return com;
    }

    /* La COLONNA puo' essere ruotata solo SU o GIU. */
    if(com.sel==colonna && (com.dir==destra || com.dir==sinistra)){
        printf("Comando errato: la COLONNA pu' essere ruotata solo SU o GIU. Reinserisci comando.\n\n");
        com.ok=false;
        return com;
    }


    /* POSIZIONI: verifico che la stringa sia numerica; in caso affermativo la trasformo in intero e, nel frattempo, verifico
                  la correttezza del numero inserito. */
    /* Verifica 1: il numero di posizioni inserito deve essere un numero. */
    if(!isStringaNumerica(posizioni)){
        printf("Comando errato: il NUMERO DI POSIZIONI puo' essere solo un valore numerico. Reinserisci comando.\n\n");
        com.ok=false;
        return com;
    }

    /* Verifica 2: il numero di posizioni deve essere un numero intero positivo. */
    com.nP=atoi(posizioni);
    if(com.nP<0){
        printf("Comando errato: il NUMERO DI POSIZIONI deve essere un numero intero positivo. Reinserisci comando.\n\n");
        com.ok=false;
        return com;
    }
    return com;
}




/* Funzione che data una stringa, restituisce l'enumerativo di tipo SELETTORE corrispondente. */
Selettore selStringToEnum(char selettore[]){

    /* Trasformo DIREZIONE in una stringa minuscola. */
    stringToMinuscola(selettore);

    /* Restituisco al chiamante l'enumerativo corrispondente alla parola presente nella stringa. */
    if(strcmp(selettore, "riga")==0){
        return riga;
    }
    if(strcmp(selettore, "colonna")==0){
        return colonna;
    }
    if(strcmp(selettore, "fine")==0){
        return fine;
    }
    return wrong;
}




/* Funzione che data una stringa, restituisce l'enumerativo di tipo DIREZIONE corrispondente. */
Direzione dirStringToEnum(char direzione[]){

    /* Trasformo DIREZIONE in una stringa minuscola. */
    stringToMinuscola(direzione);

    /* Restituisco al chiamante l'enumerativo corrispondente alla parola presente nella stringa. */
    if(strcmp(direzione, "su")==0){
        return su;
    }
    if(strcmp(direzione, "giu")==0){
        return giu;
    }
    if(strcmp(direzione, "destra")==0){
        return destra;
    }
    if(strcmp(direzione, "sinistra")==0){
        return sinistra;
    }
    return errato;
}




/* Funzione che verifica se una stringa e' numerica. */
bool isStringaNumerica(char s[]){
    int len, i;

    len=strlen(s);

    for(i=0; i<len; i++){
        if(!isdigit(s[i]) && s[i]!='-'){
            return false;
        }
    }
    return true;
}




/* Funzione che trasforma tutte le lettere della stringa in minuscole. */
void stringToMinuscola(char s[]){
    int len, i;

    len=strlen(s);

    for(i=0; i<len; i++){
        s[i]=tolower(s[i]);
    }
    return;
}




/* Funzione che permettere di ruotare una RIGA (a DESTRA o SINISTRA) o una COLONNA (SU o GIU) della matrice. */
void ruotaMatrice(int mat[][MAX], int nr, int nc, Comando com){
    int col[MAX];
    int i, dir;

    switch(com.sel){
        case riga:
            /* La RIGA puo' essere ruotata a DESTRA o SINISTRA. */

            /* Caso in cui il numero di posizioni inserito e' maggiore o uguale della lunghezza della riga.
               N.B. Se il vettore ha 3 elementi, ruotarlo a destra o sinistra ad esempio di 3 posizioni,
                    equivale a ruotarlo di 0 posizioni; ruotarlo a destra o sinistra ad esempio di 4
                    posizioni, equivale a ruotarlo di 1 posizione etc. */
            if(com.nP>=nc){
                com.nP-=nc;
            }

            /* Utilizzo la funzione scritta nel LAB 0, che ruota un vettore riga a DESTRA o SINISTRA.
               In quella funzione DESTRA = -1, SINISTRA = 1. */
            /* La riga della matrice puo' essere direttamente passata ad una funzione. */
            dir=(com.dir==sinistra)?1:-1;
            ruotaVettore(mat[com.indice], nc, com.nP, dir);
            break;


        case colonna:
            /* La COLONNA puo' essere ruotata in SU o GIU. */
            /* Ruotare un vettore colonna in SU equivale a ruotare un vettore riga a SINISTRA. */
            /* Ruotare un vettore colonna in GIU equivale a ruotare un vettore riga a DESTRA. */

            /* Caso in cui il numero di posizioni inserito e' maggiore o uguale della lunghezza della colonna.
               N.B. Se il vettore ha 3 elementi, ruotarlo a destra o sinistra ad esempio di 3 posizioni,
                    equivale a ruotarlo di 0 posizioni; ruotarlo a destra o sinistra ad esempio di 4
                    posizioni, equivale a ruotarlo di 1 posizione etc. */
            if(com.nP>=nr){
                com.nP-=nr;
            }

            /* Le colonne non possono essere passate direttamente ad una funzione. Pertanto copio in un
               vettore di supporto la colonna da ruotare. */
            for(i=0; i<nr; i++){
                col[i]=mat[i][com.indice];
            }


            /* Utilizzo la funzione scritta nel LAB 0, che ruota un vettore riga a DESTRA o SINISTRA,
               per ruotare il vettore colonna. In quella funzione DESTRA = -1, SINISTRA = 1. */
            dir=(com.dir==su)?1:-1;
            ruotaVettore(col, nr, com.nP, dir);

            /* Copio il vettore di supporto ruotato nella matrice. */
            for(i=0; i<nr; i++){
                mat[i][com.indice]=col[i];
            }
            break;

    }

    /* Stampo la matrice ruotata. */
    printf("La matrice ruotata e':\n");
    stampa(mat, nr, nc);
    return;
}




/* Funzione per ruotare il vettore di un numero P di posizioni a destra o sinistra. */
void ruotaVettore(int vet[], int dim, int P, int dir){
    int tmp[MAX], i, nuovaP;

    switch(dir){
        /* Rotazione a destra. */
        case -1:
            /* Scorro il vettore VET. */
            for(i=0; i<dim; i++){
                /* Determino la nuova posizione dell'elemento VET[I], ricordando che l'elemento a destra di VET[DIM-1] e' VET[0]:
                   - se "I+P" genera un indice che e' minore della dimensione di VET, "I+P" e' la nuova posizione.
                   - se "I+P" genera un indice che e' maggiore o uguale della dimensione di VET, significa che, dopo DIM-1, gli indici devono
                     ripartire da 0: "I+P-DIM" e' la nuova posizione. */
                nuovaP=(i+P>=dim)?(i+P-dim):i+P;

                /* Salvo l'elemento VET[I] nel vettore temporaneo alla posizione NUOVAP. */
                tmp[nuovaP]=vet[i];
            }

            /* Copio il contenuto del vettore temporaneo in VET. */
            copiaVettore(tmp, vet, dim);
            break;

        /* Rotazione a sinistra. */
        case 1:
            /* Scorro il vettore VET. */
            for(i=0; i<dim; i++){
                /* Determino la nuova posizione dell'elemento VET[I], ricordando che l'elemento a sinistra di VET[0] e' VET[DIM-1]:
                   - se "I-P" genera un indice che e' maggiore o uguale a 0, "I-P" e' la nuova posizione.
                   - se "I-P" genera un indice che e' minore di 0, significa che, dopo 0, gli indici devono ripartire da DIM-1:
                     "I-P+DIM" e' la nuova posizione. */
                nuovaP=(i-P<0)?(i-P+dim):i-P;

                /* Salvo l'elemento VET[I] nel vettore temporaneo alla posizione NUOVAP. */
                tmp[nuovaP]=vet[i];
            }

            /* Copio il contenuto del vettore temporaneo in VET. */
            copiaVettore(tmp, vet, dim);
            break;

    }
    return;
}




/* Funzione che copia il vettore SOURCE nel vettore DEST. I vettori hanno la stessa dimensione. */
void copiaVettore(int source[], int dest[], int dim){
    int i;

    for(i=0; i<dim; i++){
        dest[i]=source[i];
    }
    return;
}





