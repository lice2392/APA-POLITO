#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAXC 31
#define MAX 1000

typedef struct{
    int gg, mm, aa;
}Data;

typedef struct{
    char codiceTratta[MAXC], partenza[MAXC], arrivo[MAXC];
    char data[MAXC];
    char oraP[MAXC], oraA[MAXC];
    int ritardo;
}Tratta;

typedef enum{errato=-1, r_date, r_partenza, r_capolinea, r_ritardo, r_ritardoTot, r_fine}Comando;

int leggiTratte(char nomeFile[], Tratta tratte[]);
void stampaTratta(Tratta corsa);
Comando comStringToEnum(char comando[]);
void stringToMinuscola(char str[]);
void selezionaDati(Tratta tratte[], int nTratte, Comando com);
Data inserisciData();
bool isDataCorretta(Data d);
bool isBisestile(int anno);
int dateCompare(Data d1, Data d2);
bool cercaEStampa(Tratta tratte[], int dim, char key1[], char key2[], Comando com);


int main()
{
    int nTratte;
    Tratta tratte[MAX];
    Comando com;
    char comando[MAXC];

    /* Acquisizione delle tratte da file. */
    nTratte=leggiTratte("corse.txt", tratte);

    /* Ciclo che permette all'utente di poter eseguire piu' interrogazioni fino a quando non decide di terminare. */
    do{
        printf("Inserisci:\n");
        printf(" -'date' per elencare tutte le corse partite in un certo intervallo di date.\n");
        printf(" -'partenza' per elencare tutti le corse partite da una certa fermata.\n");
        printf(" -'capolinea' per elencare tutti le corse che fanno capolinea in una certa fermata.\n");
        printf(" -'ritardo' per elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date.\n");
        printf(" -'ritardo_tot' per elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta.\n");
        printf(" -'fine' per terminare.\n");
        printf("Che cosa vuoi fare? ");
        fgets(comando, MAXC, stdin);

        /* Elimino il '\n' presente nella stringa dopo la FGETS, sostituendolo con '\0'. */
        comando[strcspn(comando, "\n")]='\0';

        /* Reperisco l'enumerativo corrispondente al comando inserito dall'utente. */
        com=comStringToEnum(comando);

        /* Interrogazione della basi dati e stampa delle corse desiderate. */
        selezionaDati(tratte, nTratte, com);
    }while(com!=r_fine);
    return 0;
}




/* Funzione che permette di interrogare la basi dati. */
void selezionaDati(Tratta tratte[], int nTratte, Comando com){
    Data d1, d2, tmp;
    char data1[MAXC], data2[MAXC], codTratta[MAXC], partenza[MAXC], capolinea[MAXC];
    bool trovato;

    switch(com){
        /* Elenco tutte le corse partite in un certo intervallo di date. */
        case r_date:
            /* Inserimento delle due date. */
            printf("\nPRIMA DATA:");
            d1=inserisciData();

            printf("\nSECONDA DATA:");
            d2=inserisciData();

            /* Scambio le due date se D1 viene dopo di D2. */
            if(dateCompare(d1, d2)>0){
                tmp=d1;
                d1=d2;
                d2=tmp;
            }

            /* Converto le due date in stringhe. */
            sprintf(data1, "%d/%d/%02d", d1.aa, d1.mm, d1.gg);
            sprintf(data2, "%d/%d/%02d", d2.aa, d2.mm, d2.gg);

            /* Elenco tutte le corse partite nell'intervallo di date [data1, data2]. */
            printf("\nLe corse parite tra %s e %s sono:\n", data1, data2);
            trovato=cercaEStampa(tratte, nTratte, data1, data2, com);
            if(!trovato){
                printf("Non esiste alcuna corsa.\n");
            }
            break;



        /* Elenco tutte le corse partite da una certa fermata. */
        case r_partenza:
            /* Inserimento della fermata di partenza. */
            printf("\nInserisci una fermata di partenza: ");
            fgets(partenza, MAXC, stdin);
            partenza[strcspn(partenza, "\n")]='\0';

            /* Elenco tutte le corse partite da PARTENZA. */
            printf("\nLe corse parite dalla fermata %s sono:\n", partenza);
            trovato=cercaEStampa(tratte, nTratte, partenza, "\0", com);
            if(!trovato){
                printf("Non esiste alcuna corsa.\n");
            }
            break;



        /* Elenco tutte le corse che fanno capolinea in una certa fermata. */
        case r_capolinea:
            /* Inserimento della fermata di arrivo. */
            printf("\nInserisci una fermata di arrivo: ");
            fgets(capolinea, MAXC, stdin);
            capolinea[strcspn(capolinea, "\n")]='\0';

            /* Elenco tutte le corse partite da PARTENZA. */
            printf("\nLe corse aventi come capolinea la fermata %s sono:\n", capolinea);
            trovato=cercaEStampa(tratte, nTratte, capolinea, "\0", com);
            if(!trovato){
                printf("Non esiste alcuna corsa.\n");
            }
            break;



        /* Elenco tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date. */
        case r_ritardo:
            /* Inserimento delle due date. */
            printf("\nPRIMA DATA:");
            d1=inserisciData();

            printf("\nSECONDA DATA:");
            d2=inserisciData();

            /* Scambio le due date se D1 viene dopo di D2. */
            if(dateCompare(d1, d2)>0){
                tmp=d1;
                d1=d2;
                d2=tmp;
            }

            /* Converto le due date in stringhe. */
            sprintf(data1, "%d/%d/%02d", d1.aa, d1.mm, d1.gg);
            sprintf(data2, "%d/%d/%02d", d2.aa, d2.mm, d2.gg);

            /* Elenco tutte le corse che hanno raggiunto la destinazione in ritardo nell'intervallo di date [data1, data2]. */
            printf("\nLe corse che hanno raggiunto in ritardo la destrinazione tra %s e %s sono:\n", data1, data2);
            trovato=cercaEStampa(tratte, nTratte, data1, data2, com);
            if(!trovato){
                printf("Non esiste alcuna corsa.\n");
            }
            break;

        /* Elenco il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta. */
        case r_ritardoTot:
            /* Inserimento del codice tratta. */
            printf("\nInserisci un codice tratta: ");
            fgets(codTratta, MAXC, stdin);
            codTratta[strcspn(codTratta, "\n")]='\0';

            /* Elenco il ritardo complessivo accumulato dalle corse identificate dal codice presente in COD_TRATTA. */
            printf("\nIl ritardo complessivo delle corse identificate dal codice %s e': ", codTratta);
            trovato=cercaEStampa(tratte, nTratte, codTratta, "\0", com);
            if(!trovato){
                printf("\nNon esiste alcuna corsa avente codice %s.\n", codTratta);
            }
            break;

        /* Termine del programma. */
        case r_fine:
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
int leggiTratte(char nomeFile[], Tratta tratte[]){
    FILE *fi;
    int dim;
    int i;
    char data[MAXC];

    /* Apro il file. Se il file non si apre correttamente stampo un messaggio di errore ed
       esco. */
    fi=fopen(nomeFile, "r");
    if(fi==NULL){
        printf("Errore nell'apertura del file.\n");
        exit(EXIT_FAILURE);
    }

    /* Acquisisco le dimensioni effettive delle tratte. */
    fscanf(fi, "%d", &dim);

    /* Leggo le tratte dal file. */
    for(i=0; i<dim; i++){
        fscanf(fi, "%s %s %s %s %s %s %d", tratte[i].codiceTratta, tratte[i].partenza, tratte[i].arrivo, tratte[i].data, tratte[i].oraP, tratte[i].oraA, &tratte[i].ritardo);
    }
    fclose(fi);
    return dim;
}




/* Funzione che stampa una tratta. */
void stampaTratta(Tratta corsa){
    printf("%s %s %s %s %s %s %d\n", corsa.codiceTratta, corsa.partenza, corsa.arrivo, corsa.data, corsa.oraP, corsa.oraA, corsa.ritardo);
}




/* Funzione che data una stringa, restituisce l'enumerativo di tipo COMANDO corrispondente. */
Comando comStringToEnum(char comando[]){

    /* Trasformo COMANDO in una stringa minuscola. */
    stringToMinuscola(comando);

    /* Restituisco al chiamante l'enumerativo corrispondente alla parola presente nella stringa. */
    if(strcmp(comando, "date")==0){
        return r_date;
    }
    if(strcmp(comando, "partenza")==0){
        return r_partenza;
    }
    if(strcmp(comando, "capolinea")==0){
        return r_capolinea;
    }
    if(strcmp(comando, "ritardo")==0){
        return r_ritardo;
    }
    if(strcmp(comando, "ritardo_tot")==0){
        return r_ritardoTot;
    }
    if(strcmp(comando, "fine")==0){
        return r_fine;
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




/* Funzione che verifica la correttezza della data. */
bool isDataCorretta(Data d){

    /* Check sul mese. */
    if(d.mm<1 || d.mm>12)
        return false;

    /* Check sul giorno. */
    if(d.gg<1)
        return false;
    if(d.gg>30 && (d.mm==4 || d.mm==6 || d.mm==9 || d.mm==11))
        return false;
    if(d.gg>31 && (d.mm==1 || d.mm==3 || d.mm==5 || d.mm==7 || d.mm==8 || d.mm==10 || d.mm==12))
        return false;
    if(isBisestile(d.aa) && d.mm==2 && d.gg>29)
        return false;
    if(!isBisestile(d.aa) && d.mm==2 && d.gg>28)
        return false;

    return true;
}




/* Funzione che verifica se un anno e' bisestile. */
bool isBisestile(int anno){
    /* Un anno e' bisestile se:
        1) E' divisibile per 4 ma non per 100.
        2) E' divisibile per 400. */
    return (anno%4==0 && anno%100!=0) || (anno%400==0);
}




/* Funzione che permette l'inserimento di una data. L'inserimento continua fino a quando la data non e' corretta. */
Data inserisciData(){
    Data d;

    do{
        printf("\nInserisci una data:\n");
        printf("Inserisci il giorno: ");
        scanf("%d%*c", &d.gg);
        printf("Inserisci il mese: ");
        scanf("%d%*c", &d.mm);
        printf("Inserisci l'anno: ");
        scanf("%d%*c", &d.aa);

        if(!isDataCorretta(d)){
            printf("\nLa data inserita non e' corretta. Reinseriscila.\n");
        }
    }while(!isDataCorretta(d));
    return d;
}




/* Funzione che permette il confronto tra due date. */
int dateCompare(Data d1, Data d2){
    if(d1.aa!=d2.aa)
        return d1.aa-d2.aa;
    if(d1.mm!=d2.mm)
        return d1.mm-d2.mm;
    return d1.gg-d2.gg;
}




/* Funzione che permette, a seconda del comando passato alla funzione, di:
     1. elencare tutte le corse partite in un certo intervallo di date (in questo caso KEY1=DATA1, KEY2=DATA2);
     2. elencare tutti le corse partite da una certa fermata (in questo caso KEY1=FERMATA DI PARTENZA, KEY2=STRINGA VUOTA);
     3. elencare tutti le corse che fanno capolinea in una certa fermata (in questo caso KEY1=FERMATA DI ARRIVO, KEY2=STRINGA VUOTA);
     4. elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date (in questo caso KEY1=DATA1, KEY2=DATA2);
     5. elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta (in questo caso KEY1=CODICE TRATTA, KEY2=DATA2)
Se non e' stata trovata nessuna tratta, la funzione non stampa nulla e ritorna FALSO; altrimenti stampa le tratte desiderate e ritorna VERO. */
bool cercaEStampa(Tratta tratte[], int dim, char key1[], char key2[], Comando com){
    bool trovato=false;
    int i;
    char data1[MAXC], data2[MAXC], codTratta[MAXC], partenza[MAXC], capolinea[MAXC];
    int ritardoTot=0;

    /* In base al comando ricevuto, assegno KEY1 e KEY2 alle variabili che ne descrivono il significato. */
    if(com==r_date || com==r_ritardo){
        strcpy(data1, key1);
        strcpy(data2, key2);
    }
    else if(com==r_partenza){
        strcpy(partenza, key1);
    }
    else if(com==r_capolinea){
        strcpy(capolinea, key1);
    }
    else if(com==r_ritardoTot){
        strcpy(codTratta, key1);
    }

    for(i=0; i<dim; i++){
        switch(com){
                /* Stampo la tratta la cui data appartiene all'intervallo [data1, data2]. */
                case r_date:
                    if(strcmp(tratte[i].data, data1)>=0 && strcmp(tratte[i].data, data2)<=0){
                        stampaTratta(tratte[i]);
                        trovato=true;
                    }
                    break;

                /* Stampo la tratta che e' partita dalla fermata contenuta in PARTENZA. */
                case r_partenza:
                    if(strcmp(tratte[i].partenza, partenza)==0){
                        stampaTratta(tratte[i]);
                        trovato=true;
                    }
                    break;

                /* Stampo la tratta che fa capolinea nella fermata contenuta in CAPOLINEA. */
                case r_capolinea:
                    if(strcmp(tratte[i].arrivo, capolinea)==0){
                        stampaTratta(tratte[i]);
                        trovato=true;
                    }
                    break;

                /* Stampo la tratta che ha raggiunto la destinazione in ritardo nell'intervallo [data1, data2]. */
                case r_ritardo:
                    if(tratte[i].ritardo>0 && strcmp(tratte[i].data, data1)>=0 && strcmp(tratte[i].data, data2)<=0){
                        stampaTratta(tratte[i]);
                        trovato=true;
                    }
                    break;

                /* Calcolo il ritardo accumulato dalle corse identificate dal codice di tratta contenuto in COD_TRATTA. */
                case r_ritardoTot:
                    if(strcmp(tratte[i].codiceTratta, codTratta)==0){
                        ritardoTot+=tratte[i].ritardo;
                        trovato=true;
                    }
                    break;
        }
    }
    if(com==r_ritardoTot && trovato==true){
        printf("%d\n", ritardoTot);
    }
    return trovato;
}


