#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* LITTLE ENDIAN vs BIG ENDIAN
   Dato il seguente numero in esadecimale su 32 BIT: 0A0B0C0D, ove 0A e' il MSB (byte piu' significativo) e 0D e' il LSB (byte meno significativo).

   BIG ENDIAN: Memorizza il MSB all'indirizzo di memoria piu' basso e il LSB all'indirizzo piu' alto, ovvero:
   +----+----+----+----+
   | 0A | 0B | 0C | 0D |
   +----+----+----+----+
   0    7   15   23   31

   LITTLE ENDIAN: Memorizza il LSB all'indirizzo di memoria piu' basso e il MSB all'indirizzo piu' alto, ovvero:
   +----+----+----+----+
   | 0D | 0C | 0B | 0A |
   +----+----+----+----+
   0    7   15   23   31
*/

/* RAPPRESENTAZIONE IN BIT DI UN FLOAT (32 BIT):
    1     8               23               lunghezza in bit
    +-+--------+-----------------------+
    |S|  Esp.  |       Mantissa        |
    +-+--------+-----------------------+
    MSB                               LSB
*/

/* RAPPRESENTAZIONE IN BIT DI UN DOUBLE (64 BIT):
     1     11                                52                            lunghezza in bit
    +-+-----------+----------------------------------------------------+
    |S| Esponente |  Mantissa                                          |
    +-+-----------+----------------------------------------------------+
    MSB                                                               LSB
*/

/* RAPPRESENTAZIONE IN BIT DI UN LONG DOUBLE (NUMERO DI BIT CHE DIPENDE DAL CALCOLATORE):
     1     15            VALORE CHE DIPENDE DAL CALCOLATORE                  lunghezza in bit
    +-+-------------+----------------------------------------------------+
    |S| Esponente   |  Mantissa                                          |
    +-+-------------+----------------------------------------------------+
    MSB                                                                 LSB
*/

int isBigEndian();
void stampaCodifica (void *p, int size, int bigEndian);
int getNBitEsponente(int size);
int getDimensioneEffettiva(int size);

int main()
{
    int bigEndian;
    float af;
    double ad;
    long double ald;

    /* Determino se il calcolatore utilizza la codifica LITTLE ENDIAN o BIG ENDIAN. */
    bigEndian=isBigEndian();

    /* Visualizzo il tipo di codifica usato dal calcolatore. */
    printf("Il calcolatore usa la codifica %s \n\n", (bigEndian==1)?"BIG ENDIAN":"LITTLE ENDIAN");

    /* Visualizzo la dimensione (espressa in BYTE e in BIT) delle tre variabili. */
    printf("La dimensione della variabile 'af' di TIPO FLOAT e' %d BYTE (ovvero %d BIT)\n", (int)(sizeof(af)), (int)(8*sizeof(af)));
    printf("La dimensione della variabile 'ad' di tipo DOUBLE e' %d BYTE (ovvero %d BIT)\n", (int)(sizeof(ad)), (int)(8*sizeof(ad)));
    printf("La dimensione della variabile 'ald' di tipo LONG DOUBLE e' %d BYTE (ovvero %d BIT)\n\n", (int)(sizeof(ald)), (int)(8*sizeof(ald)));

    /* Acquisisco da tastiera un numero decimale e lo assegno alle tre variabili. */
    printf("Inserisci un numero decimale: ");
    scanf("%f", &af);
    ad=(double)af;
    ald=(long double)af;

    /* Chiamo la funzione STAMPACODIFICA che, utilizzando l'aritmetica dei puntatori,
      la conoscenza del tipo di codifica e la dimensione ricevuta come parametro,
      stampa il bit di segno, i bit di esponente e i bit di mantissa delle tre
      variabili AF, AD e ALD rispettivamente di tipo FLOAT, DOUBLE e LONG DOUBLE. */
    printf("\nCodifica della variabile FLOAT:\n");
    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    printf("\n\nCodifica della variabile DOUBLE:\n");
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);
    printf("\n\nCodifica della variabile LONG DOUBLE:\n");
    stampaCodifica((void *)&ald,sizeof(ald),bigEndian);
    return 0;
}




/* Funzione che determina se il calcolatore utilizza la codifica LITTLE ENDIAN o BIG ENDIAN. */
int isBigEndian(){
    int var=1;
    unsigned char *p;

    /* Coverto la variabile INTERA (che so essere su 32 BIT) in un vettore di 4 UNISGNED CHAR, facendo
       puntare P al primo BYTE. So che un CHAR occupa 1 BYTE (8 BIT). Si usa l'UNSIGNED perche' e' il tipo
       di dato che interpreta il valore memorizzato senza segno (Es: il numero 255 e' codificato in bit
       cosi': 11111111. Salvando quel valore in una variabile di tipo UNSIGNED CHAR, quel valore
       viene interpretato come 255, non come −1).

                    LITTLE ENDIAN           BIG ENDIAN
        VAR         0   7  15  23  32      0   7  15  23  32
       +---+        +---+---+---+---+      +---+---+---+---+
       | 1 |  --->  | 1 | 0 | 0 | 0 |      | 0 | 0 | 0 | 1 |
       +---+        +---+---+---+---+      +---+---+---+---+
                      ^                      ^
                      |                      |
                      p                      p
    */
    p=(unsigned char *)&var;

    /* Come mostrato precedentemente, se il calcolatore usa la codifica BIG ENDIAN allora P[0] e' pari a 0;
       se, invece usa quella LITTLE ENDIAN allora P[0] e' pari a 1. */
    return p[0]==0;
}




/* Funzione che, utilizzando l'aritmetica dei puntatori, la conoscenza del tipo di codifica
   e la dimensione ricevuta come parametro, stampa il BIT DI SEGNO, i BIT DI ESPONENTE e i
   BIT DI MANTISSA della variabile passata alla funzione come PUNTATORE VOID. */
void stampaCodifica (void *p, int size, int bigEndian){
    int i, finish, index, nBit=0, bit[8], sizeEff;
    unsigned char *vet;
    int nbitSegno=1, nbitEsponente;

    /* Converto il puntatore VOID P, il cui valore occupa SIZE BYTE, in un vettore di BYTE avente
       SIZE CELLE ciascuna da 1 BYTE. */
    vet=(unsigned char*)p;

    /* Determino il numero dei bit dell'esponente a seconda del valore di SIZE espresso in BYTE. */
    nbitEsponente=getNBitEsponente(size);

    /* Se la variabile da codificare e' di tipo LONG DOUBLE, ovvero SIZE e' pari a un valore maggiore di
      8 BYTE, e' possibile che la dimensione effettiva della variabile sia pari a un numero di BYTE
      che non e' multiplo di 4. In tal caso, per allineare i dati, vengono aggiunti dei BYTE di PADDING
      alla fine del numero (agli indirizzi alti della memoria); SIZE quindi sarebbe il risultato della
      somma tra la dimensione effettiva del dato e il numero di BYTE DI PADDING. Determino quindi la
      dimensione effettiva della variabile LONG DOUBLE puntata da P. */
      if(size>8){
         sizeEff=getDimensioneEffettiva(size);
         /* Stampo la dimensione effettiva della variabile di tipo LONG DOUBLE se ci sono dei BYTE DI PADDING. */
         if(size!=sizeEff){
            printf("La dimensione effettiva della variabile di tipo LONG DOUBLE e' %d BYTE (N.BYTE DI PADDING = %d)\n", sizeEff, (size-sizeEff));
         }
         size=sizeEff;
      }

    /* Devo scorrere il vettore di BYTE VET, che ha dimensione SIZE BYTE, da MSB a LSB; pertanto, in caso di BIG ENDIAN, scorro
       da sinistra a destra perche' il MSB si trova agli indici di memoria piu' bassi; in caso di LITTLE ENDIAN, invece, scorro il
       vettore da destra a sinistra. */
    i=(bigEndian==1)?0:size-1;
    finish=(bigEndian==1)?(i<size):(i>=0);
    while(finish){
        /* Per ogni cella VET[I], che so contenere un numero decimale occupante 1 BYTE (8 bit), determino i corrispettivi bit. */
        /* Uso l'algoritmo delle divisioni successive per 2, che determina i bit dal meno significativo al piu' significativo.
           Per tale ragione il vettore BIT, che conterra' gli 8 BIT di codifica di VET[I], verra' riempito da destra a sinistra. */
        index=0;
        while(index<8){
            bit[8-index-1]=vet[i]%2;
            vet[i]/=2;
            index++;
        }

        /* Stampo i bit. */
        for(index=0; index<8; index++){
            /* Se NBIT e' pari a 0 (non ho ancora stampato alcun BIT), allora BIT[INDEX] sara' il BIT DI SEGNO. */
            if(nBit==0){
                printf("Bit di segno: ");
            }
            /* Se NBIT e' pari a NBITDISEGNO (ho stampato solo UN BIT, ovvero il BIT DI SEGNO), allora BIT[INDEX]
               sara' il PRIMO BIT DELL'ESPONENTE. */
            else if(nBit==nbitSegno){
                printf("\nBit di esponente: ");
            }
            /* Se NBIT e' pari a NBITDISEGNO + NBITESPONENTE (ho stampato il BIT DI SEGNO e TUTTI I BIT DELL'ESPONENTE),
               allora BIT[INDEX] sara' il PRIMO BIT DELLA MANTISSA. */
            else if(nBit==nbitSegno+nbitEsponente){
                printf("\nBit di mantissa: ");
            }
            printf("%d", bit[index]);
            nBit++;
        }
        i=(bigEndian==1)?(i+1):(i-1);
        finish=(bigEndian==1)?(i<size):(i>=0);
    }
    return;
}





/* Funzione che determina il numero di bit dell'esponente, a seconda del valore di SIZE espresso in BYTE. */
int getNBitEsponente(int size){
    /* Se SIZE e' 4 BYTE (32 BIT), ovvero la variabile e' di tipo FLOAT, il numero di bit
       dell'esponente e' pari a 8. */
    if(size==4)
        return 8;
    /* Se SIZE e' 8 BYTE (64 BIT), ovvero la variabile e' di tipo DOUBLE, il numero di bit
       dell'esponente e' pari a 11. */
    if(size==8)
        return 11;
    /* Se la variabile e' di tipo LONG DOUBLE, il numero di bit dell'esponente e' pari a 15. */
    return 15;
}





/* Funzione che determina la dimensione effettiva della variabile di tipo LONG DOUBLE, determinando il numero
   di BYTE DI PADDING. */
int getDimensioneEffettiva(int size){
    long double a;
    unsigned char *pa;
    int nPadding, i;

    /* Converto la variabile di tipo LONG DOUBLE in un vettore di SIZE celle, ciascuna da 1 BYTE, facendo
       puntare PA al primo BYTE. */
    pa=(unsigned char *)&a;

    /* Riempio tutta la memoria della variabile A del valore 0xFF (compreso il padding virtuale).
       Grazie alla funzione MEMSET, ciascuno dei SIZE BYTE conterra' il valore 0xFF. */
    memset(&a, 0xFF, size);

    /* Assegniamo il valore 0 alla variabile A. La CPU sovrascrive SOLO i dati utili portandoli a 0x00;
       i BYTE DI PADDING continueranno ad essere pari a 0xFF. */
    a = 0x00;


    /* Scorro il vettore PA e conto quanti BYTE sono pari a 0xFF. */
    nPadding = 0;
    for(i=0; i<size; i++){
        if(pa[i]==0xFF){
            nPadding++;
        }
    }
    /* La dimensione effettiva e' pari alla differenza tra SIZE e il numero di BYTE DI PADDING. */
    return (size-nPadding);
}




