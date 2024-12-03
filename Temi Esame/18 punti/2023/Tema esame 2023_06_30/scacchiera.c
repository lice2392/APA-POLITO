#include "scacchiera.h"
#define BUCO -1

struct scacchiera{
    int **griglia;
    int dim;
};


static int **malloc2D(int nr, int nc);
static void free2D(int **mat, int nr);
static Boolean checkPuzzleR(Scacchiera s, Tessere t, int riga, int colonna, int *markTessere);
static Boolean dispRip(Scacchiera s, Tessere t, Mosse sol, int nMosse, Cella *tessereDaMuovere, int pos);
static Boolean findTessere(Scacchiera s, Cella *tessere, Direzione dir, int *nTessere);


Scacchiera SCACCHIERAinit(int dim){
    Scacchiera s;

    s=(Scacchiera)malloc(sizeof(struct scacchiera));
    if(s==NULL) exit(EXIT_FAILURE);

    s->dim=dim;

    s->griglia=malloc2D(s->dim, s->dim);

    return s;
}


static int **malloc2D(int nr, int nc){
    int **mat, i;

    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);

    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    return mat;
}




Scacchiera SCACCHIERAread(FILE *f, Tessere *t){
    Tessere te;
    Tessera tessera;
    int dimMatrice, nTessere, i, j, indexTessera;;
    Scacchiera s;

    fscanf(f, "%d %d", &dimMatrice, &nTessere);

    te=TESSEREinit(nTessere);
    s=SCACCHIERAinit(dimMatrice);

    for(i=0; i<dimMatrice; i++){
        for(j=0; j<dimMatrice; j++){
            tessera=TESSERAread(f);
            if(TESSERAisBuco(tessera)==FALSO){
                indexTessera=TESSEREgetNumTessere(te);
                TESSEREaddTessera(te, tessera);
                s->griglia[i][j]=indexTessera;
            }
            else{
                s->griglia[i][j]=BUCO;
            }
        }
    }
    *t=te;
    return s;
}




void SCACCHIERAprint(Scacchiera s, Tessere t, FILE *f){
    int i, j;
    Tessera te;

    for(i=0; i<s->dim; i++){
        for(j=0; j<s->dim; j++){
           if(s->griglia[i][j]==BUCO){
                fprintf(f, " ");
           }
           else{
                te=TESSEREgetTessera(t, s->griglia[i][j]);
                TESSERAprint(te, f);

           }
           fprintf(f, "\t\t");
        }
        fprintf(f, "\n");
    }
}




Boolean SCACCHIERAverificaMosse(Scacchiera s, Tessere t, Mosse m, int M, char *messaggio){
    int nMosse, i, nTessere, *markTessereMossa, j, indexTessera;
    Mossa mossa;
    Cella c;

    nMosse=MOSSEgetNumMosse(m);
    nTessere=TESSEREgetNumTessere(t);

    if(nMosse>M){
        strcpy(messaggio, "il numero di mosse e' maggiore del numero massimo di mosse consentite.\n");
        return FALSO;
    }

    for(i=0; i<nMosse; i++){
        markTessereMossa=calloc(nTessere, sizeof(int));
        if(markTessereMossa==NULL) exit(EXIT_FAILURE);

        mossa=MOSSEgetMossa(m, i);
        if(mossa.direzione==-1){
            strcpy(messaggio, "direzione errata.\n");
            return FALSO;
        }
        if(mossa.nTessereMosse<0 || mossa.nTessereMosse>nTessere){
            strcpy(messaggio, "il numero di tessere usate nella mossa e' errato.\n");
            return FALSO;
        }
        for(j=0; j<mossa.nTessereMosse; j++){
            c=mossa.tessereMosse[j];
            if(c.riga<0 || c.riga>=s->dim){
                strcpy(messaggio, "la riga nella griglia della tessera da muovere e' errata.\n");
                return FALSO;
            }
            if(c.colonna<0 || c.colonna>=s->dim){
                strcpy(messaggio, "la colonna nella griglia della tessera da muovere e' errata.\n");
                return FALSO;
            }
            if(s->griglia[c.riga][c.colonna]==BUCO){
                strcpy(messaggio, "la tessera da muovere in realta' e' un buco.\n");
                return FALSO;
            }
            if((mossa.direzione==NORD && c.riga==0) || (mossa.direzione==SUD && c.riga==(s->dim-1)) || (mossa.direzione==OVEST && c.colonna==0) || (mossa.direzione==EST && c.colonna==(s->dim-1))){
                strcpy(messaggio, "la tessera non puo' muoversi al di fuori della griglia.\n");
                return FALSO;
            }
            if((mossa.direzione==NORD && s->griglia[c.riga-1][c.colonna]!=BUCO) || (mossa.direzione==SUD && s->griglia[c.riga+1][c.colonna]!=BUCO) || (mossa.direzione==OVEST && s->griglia[c.riga][c.colonna-1]!=BUCO) || (mossa.direzione==EST &&s->griglia[c.riga][c.colonna+1]!=BUCO)){
                strcpy(messaggio, "la tessera non e' libera di muoversi verso la direzione scelta.\n");
                return FALSO;
            }
            indexTessera=s->griglia[c.riga][c.colonna];
            if(markTessereMossa[indexTessera]==1){
                strcpy(messaggio, "una tessera non puo' muoversi piu' di una volta nella stessa mossa.\n");
                return FALSO;
            }
            markTessereMossa[indexTessera]=1;
        }
        SCACCHIERAmuoviTessere(s, mossa);
        free(markTessereMossa);
    }
    return VERO;
}




void SCACCHIERAmuoviTessere(Scacchiera s, Mossa m){
    int i, tmp;
    Cella c;
    int mosseRighe[]={-1, 1, 0, 0};
    int mosseColonne[]={0, 0, -1, 1};
    int mossaRiga, mossaColonna;

    mossaRiga=mosseRighe[m.direzione];
    mossaColonna=mosseColonne[m.direzione];
    for(i=0; i<m.nTessereMosse; i++){
        c=m.tessereMosse[i];
        tmp=s->griglia[c.riga+mossaRiga][c.colonna+mossaColonna];
        s->griglia[c.riga+mossaRiga][c.colonna+mossaColonna]=s->griglia[c.riga][c.colonna];
        s->griglia[c.riga][c.colonna]=tmp;
    }
    return;
}




Boolean SCACCHIERAverificaPuzzle(Scacchiera s, Tessere t){
    int nTessere, *mark, indexTessera, i, j, startRiga=-1, startColonna=-1;
    Tessera te;

    nTessere=TESSEREgetNumTessere(t);

    mark=calloc(nTessere, sizeof(int));
    if(mark==NULL) exit(EXIT_FAILURE);

    for(i=0; i<s->dim && startRiga==-1 && startColonna==-1; i++){
        for(j=0; j<s->dim && startRiga==-1 && startColonna==-1; j++){
            if(s->griglia[i][j]!=BUCO){
                indexTessera=s->griglia[i][j];
                te=TESSEREgetTessera(t, indexTessera);
                if(TESSERAisSorgenteODestinazione(te)==VERO){
                    startRiga=i;
                    startColonna=j;
                }
            }
        }
    }
    return checkPuzzleR(s, t, startRiga, startColonna, mark);
}


static Boolean checkPuzzleR(Scacchiera s, Tessere t, int riga, int colonna, int *markTessere){
    int indexTessera, indexTesseraOther;
    Tessera te, teOther;

    indexTessera=s->griglia[riga][colonna];
    markTessere[indexTessera]=1;
    te=TESSEREgetTessera(t, indexTessera);

    if(te.nord==1){
        if(riga==0){
            return FALSO;
        }
        if(s->griglia[riga-1][colonna]==BUCO){
            return FALSO;
        }
        indexTesseraOther=s->griglia[riga-1][colonna];
        teOther=TESSEREgetTessera(t, indexTesseraOther);
        if(teOther.sud==0){
            return FALSO;
        }
        if(markTessere[indexTesseraOther]==0){
            if(checkPuzzleR(s, t, riga-1, colonna, markTessere)==FALSO){
                return FALSO;
            }
        }
    }

    if(te.sud==1){
        if(riga==(s->dim-1)){
            return FALSO;
        }
        if(s->griglia[riga+1][colonna]==BUCO){
            return FALSO;
        }
        indexTesseraOther=s->griglia[riga+1][colonna];
        teOther=TESSEREgetTessera(t, indexTesseraOther);
        if(teOther.nord==0){
            return FALSO;
        }
        if(markTessere[indexTesseraOther]==0){
            if(checkPuzzleR(s, t, riga+1, colonna, markTessere)==FALSO){
                return FALSO;
            }
        }
    }

    if(te.ovest==1){
        if(colonna==0){
            return FALSO;
        }
        if(s->griglia[riga][colonna-1]==BUCO){
            return FALSO;
        }
        indexTesseraOther=s->griglia[riga][colonna-1];
        teOther=TESSEREgetTessera(t, indexTesseraOther);
        if(teOther.est==0){
            return FALSO;
        }
        if(markTessere[indexTesseraOther]==0){
            if(checkPuzzleR(s, t, riga, colonna-1, markTessere)==FALSO){
                return FALSO;
            }
        }
    }

    if(te.est==1){
        if(colonna==(s->dim-1)){
            return FALSO;
        }
        if(s->griglia[riga][colonna+1]==BUCO){
            return FALSO;
        }
        indexTesseraOther=s->griglia[riga][colonna+1];
        teOther=TESSEREgetTessera(t, indexTesseraOther);
        if(teOther.ovest==0){
            return FALSO;
        }
        if(markTessere[indexTesseraOther]==0){
            if(checkPuzzleR(s, t, riga, colonna+1, markTessere)==FALSO){
                return FALSO;
            }
        }
    }
    return VERO;
}




void SCACCHIERAreset(Scacchiera s, Mosse m){
    int nMosse, i;
    Mossa mo;

    nMosse=MOSSEgetNumMosse(m);

    for(i=nMosse-1; i>=0; i--){
        mo=MOSSEgetMossa(m, i);
        SCACCHIERAmuoviTessere(s, mo);
    }
    return;
}




void SCACCHIERAsearch(Scacchiera s, Tessere t, int M){
    Mosse sol;
    int nMosse, nTessere;
    Boolean trovato;
    Cella *tessereDaMuovere;

    nTessere=TESSEREgetNumTessere(t);

    tessereDaMuovere=(Cella *)malloc(nTessere*sizeof(nTessere));
    if(tessereDaMuovere==NULL) exit(EXIT_FAILURE);

    sol=MOSSEinit(M);

    for(nMosse=1; nMosse<=M; nMosse++){
        trovato= dispRip(s, t, sol, nMosse, tessereDaMuovere, 0);
        if(trovato==VERO){
            break;
        }
    }
    if(trovato==VERO){
        printf("Soluzione trovata.\n\n");
        printf("---MOSSE:---\n");
        MOSSEprint(sol, stdout);
        printf("\n---SCACCHIERA RISOLTA:---\n");
        SCACCHIERAprint(s, t, stdout);
    }
    else{
        printf("Soluzione non trovata.");
    }
    return;
}


static Boolean dispRip(Scacchiera s, Tessere t, Mosse sol, int nMosse, Cella *tessereDaMuovere, int pos){
    int nTessere;
    Mossa mossa;
    Direzione direzione;

    if(pos>=nMosse){
        if(SCACCHIERAverificaPuzzle(s, t)==VERO){
            return VERO;
        }
        return FALSO;
    }

    nTessere=0;
    for(direzione=NORD; direzione<=EST; direzione++){
        if(findTessere(s, tessereDaMuovere, direzione, &nTessere)==FALSO){
            continue;
        }
        mossa=MOSSAcrea(direzione, tessereDaMuovere, nTessere);
        MOSSEaddMossa(sol, mossa);
        SCACCHIERAmuoviTessere(s, mossa);
        if(dispRip(s, t, sol, nMosse, tessereDaMuovere, pos+1)==VERO){
            return VERO;
        }
        SCACCHIERAmuoviTessere(s, mossa);
        MOSSEeliminaMossa(sol);
        MOSSAclear(&mossa);
    }
    return FALSO;
}


static Boolean findTessere(Scacchiera s, Cella *tessere, Direzione dir, int *nTessere){
    int n, riga, colonna;

    n=0;
    for(riga=0; riga<s->dim; riga++){
        if(dir==NORD && riga==0){
            continue;
        }
        else if(dir==SUD && riga==(s->dim-1)){
            break;
        }
        for(colonna=0; colonna<s->dim; colonna++){
            if(dir==OVEST && colonna==0){
                continue;
            }
            else if(dir==EST && colonna==(s->dim-1)){
                break;
            }
            switch (dir){
                case NORD:
                    if(s->griglia[riga][colonna]!=BUCO &&  s->griglia[riga-1][colonna]==BUCO){
                        tessere[n++]=CELLAcreate(riga, colonna);
                    }
                    break;
                case SUD:
                    if(s->griglia[riga][colonna]!=BUCO && s->griglia[riga+1][colonna]==BUCO){
                        tessere[n++]=CELLAcreate(riga, colonna);
                    }
                    break;
                case EST:
                    if(s->griglia[riga][colonna]!=BUCO && s->griglia[riga][colonna+1]==BUCO){
                        tessere[n++]=CELLAcreate(riga, colonna);
                    }
                    break;
                case OVEST:
                    if(s->griglia[riga][colonna]!=BUCO && s->griglia[riga][colonna-1]==BUCO){
                        tessere[n++]=CELLAcreate(riga, colonna);
                    }
                    break;
            }
        }
    }
    if(n==0)
        return FALSO;
    *nTessere=n;
    return VERO;
}




void SCACCHIERAfree(Scacchiera s){
    if(s!=NULL){
        free2D(s->griglia, s->dim);
        free(s);
    }
}


static void free2D(int **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL){
                free(mat[i]);
            }
        }
        free(mat);
    }
}
