#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);
int getLunghezzaEffettiva(char *regexp);
bool isMetaCarattere(char car);
bool checkMetaCarattere(char carSrc, char *regexp, int *iR);

int main()
{
    char *regexp=".[aeiou][^xyz]\\a\\AtO";
    char *occ;
    int lenEffRegex, i, j;
    char *src[]={"Il baraTtOlo di marmellata e' in frigo.",
                 "Vorrei il ceroTtO con gli orsetti.",
                 "Per calcolare l'imposta sulla casa, il comune prende come riferimento i dati registrati al cataStO.",
                 "Ho pregAtO per un girETto. Ho sudato, pezzAtO e mi e' anche cascATO il telefono. Ero sfinIta. Per tirarmi su', ho mangiato un filettO.",
                 NULL};

    /* Determino la lunghezza effettiva della REGEXP. */
    lenEffRegex=getLunghezzaEffettiva(regexp);

    /* Stampo l'espressione regolare. */
    printf("ESPRESSIONE REGOLARE: %s\n\n", regexp);

    /* Per ogni frase contenuta in SRC: */
    for(i=0; src[i]!=NULL; i++){
        /* Stampo la frase. */
        printf("FRASE: %s\n", src[i]);
        /* Cerco una corrispondenza con l'espressione regolare. */
        occ=cercaRegexp(src[i], regexp);

        printf("CORRISPONDENZA: ");

        /* Se la trovo, la stampo. */
        if(occ!=NULL){
            for(j=0; j<lenEffRegex; j++){
                printf("%c", occ[j]);
            }
            printf("\n\n");
        }
        /* Altrimenti stampo un messaggio di errore. */
        else{
            printf("Nessuna corrispondenza.\n\n");
        }
    }
    return 0;
}




/* Funzione che cerca eventuali occorrenze di una espressione regolare REGEXP all'interno della
   stringa SRC. */
char *cercaRegexp(char *src, char *regexp){
    char *ret=NULL;
    int iS, iR=0, start=-1;
    bool ok;

    /* Scorro la stringa SRC. */
    for(iS=0; src[iS]!='\0'; iS++){
        /* Passo al prossimo carattere, se il carattere attuale SRC[IS] non e' alfabetico. */
        if(!isalpha(src[iS])){
            continue;
        }

        /* Nel caso in cui il carattere attuale SRC[IS] sia alfabetico: */
        /* Se il carattere attuale REGEXP[IR] e' alfabetico ed e' uguale al carattere SRC[IS]: */
        if(isalpha(regexp[iR]) && src[iS]==regexp[iR]){
            /* Salvo l'indice di inizio in SRC se e' la prima corrispondenza. */
            if(start==-1){
                start=iS;
            }
            /* Scorro le due stringhe contemporaneamente (passo al prossimo carattere di
               REGEXP). */
            iR++;
        }
        /* Se il carattere attuale REGEXP[IR] e' alfabetico e non e' uguale al carattere
           SRC[IS]: */
        else if(isalpha(regexp[iR]) && src[iS]!=regexp[iR]){
            /* Se avevo trovato una corrispondenza: */
            if(start!=-1){
                /* Riparto a scorrere SRC da START. */
                iS=start;
                /* Ripristino gli indici START e IR. */
                iR=0;
                start=-1;
            }
        }
        /* Se il carattere attuale REGEXP[IR] e' l'inizio di un METACARATTERE: */
        else if(isMetaCarattere(regexp[iR])){
            /* Verifico la corrispondenza tra il carattere SRC[IS] e il metacarattere che inizia
               da REGEXP[IR]. */
            /* In caso di corrispondenza, IR sara' l'indice dell'ultimo carattere del
               METACARATTERE. */
            ok=checkMetaCarattere(src[iS], regexp, &iR);
            /* Se il check ha avuto successo: */
            if(ok){
                /* Salvo l'indice di inizio in SRC se e' la prima corrispondenza. */
                if(start==-1){
                    start=iS;
                }
                /* Scorro le due stringhe contemporaneamente (passo al prossimo carattere
                   di REGEXP). */
                iR++;
            }
            /* Se invece il check non ha avuto successo: */
            else if(!ok){
                /* Se avevo trovato una corrispondenza: */
                if(start!=-1){
                    /* Riparto a scorrere SRC da START. */
                    iS=start;
                    /* Ripristino l'indice START. */
                    start=-1;
                }
                /* Ripristino l'indice IR (nella funzione CHECK_META_CARATTERE, IR viene comunque
                   modificato). */
                iR=0;
            }
        }
        /* Se sono arrivata alla fine di REGEXP vuol dire che ho trovato un'occorrenza.
           Salvo il valore di ritorno ed esco dal ciclo. */
        if(regexp[iR]=='\0'){
            ret=&src[start];
            break;
        }
    }
    /* Se non ho trovato alcuna occorrenza, RET sara' NULL; altrimenti sara' pari al puntatore al
       primo carattere in SRC. */
    return ret;
}




/* Funzione che determina se un carattere e' un METACARATTERE. */
bool isMetaCarattere(char car){
    return car=='[' || car=='.' || car=='\\';
}




/* Funzione che e' in grado di determinare la lunghezza effettiva di un'espressione regolare. */
int getLunghezzaEffettiva(char *regexp){
    int i;
    int lenEff=0;

    /* Scorro l'espressione regolare contenuta in REGEXP. */
    for(i=0; regexp[i]!='\0'; i++){
        /* Conto 1 per ogni CARATTERE e METACARATTERE che incontro. */
        lenEff++;
        /* Se incontro un METACARATTERE composto da piu' di un carattere, incremento I fino
           alla fine del METACARATTERE in mnodo da passare al prossimo CARATTERE o
           METACARATTERE. */
        if(regexp[i]=='['){
            while(regexp[i]!=']'){
                i++;
            }
        }
        else if(regexp[i]=='\\'){
            i++;
        }
    }
    return lenEff;
}




/* Funzione che permette di verificare una corrispondenza tra il carattere di SRC e il
   metacarattere di REGEXP. */
bool checkMetaCarattere(char carSrc, char *regexp, int *iR){
    int indexR;
    bool ret=false, trovato;

    /* Per comodita' salvo in INDEXR l'indice puntato da IR (indice di inizio del
       metacarattere). */
    indexR=(*iR);

    switch(regexp[indexR]){
        /* Caso di metacarattere '.': corrisponde a un singolo carattere alfabetico. */
        case '.':
            if(isalpha(carSrc)){
                ret=true;
            }
            break;


        /* Caso di metacarattere '[]' (corrisponde a uno dei caratteri tra parentesi) oppure di
           metacarattere '[^]' (corrisponde a un carattere che non sia tra quelli tra
           parentesi). */
        case '[':
            /* Passo al prossimo carattere di REGEXP. */
            indexR++;
            /* Caso '[^]': */
            if(regexp[indexR]=='^'){
                /* Passo al prossimo carattere di REGEXP per poter scorrere le lettere tra
                   parentesi. */
                indexR++;
                /* Scorro le lettere tra le parentesi quadre. Se CAR_SRC coincide con uno dei
                   caratteri tra parentesi, il check ha dato esito NEGATIVO: pongo TROVATO pari a
                   VERO ed esco dal ciclo. */
                trovato=false;
                while(regexp[indexR]!=']'){
                    if(carSrc==regexp[indexR]){
                        trovato=true;
                        break;
                    }
                    indexR++;
                }

                /* Se CAR_SRC non e' pari ad alcun carattere tra parentesi quadre, il check ha dato
                   esito POSITIVO: pongo RET pari a VERO. */
                if(!trovato){
                    ret=true;
                }
                /* Se il valore di ritorno e' VERO, vuol dire che ho scorso tutto il METACARATTERE
                   senza trovare alcuna corrispondenza: questo significa che INDEXR e' l'indice
                   dell'ultimo carattere del METACARATTERE. */
            }
            /* Caso '[]': */
            else{
                /* Scorro le lettere tra le parentesi quadre. Se CAR_SRC coincide con uno dei
                   caratteri tra parentesi, il check ha dato esito POSITIVO: pongo RET pari a VERO.
                   Non esco anticipatamente dal ciclo, perche', in caso di esito POSITIVO, INDEXR
                   deve essere l'indice dell'ultimo carattere del METACARATTERE. */
                while(regexp[indexR]!=']'){
                    if(carSrc==regexp[indexR]){
                        ret=true;
                    }
                    indexR++;
                }
            }
            break;


        /* Caso di metacarattere '\a' (corrisponde a un carattere minuscolo) oppure di
            metacarattere '\A' (corrisponde a un carattere maiuscolo). */
        case '\\':
            /* Passo al prossimo carattere di REGEXP. */
            indexR++;
            /* Caso '\A': */
            if(regexp[indexR]=='A' && isalpha(carSrc) && isupper(carSrc)){
                ret=true;
            }
            /* Caso '\a': */
            else if(regexp[indexR]=='a' && isalpha(carSrc) && islower(carSrc)){
                ret=true;
            }
            break;
    }
    (*iR)=indexR;
    return ret;
}
