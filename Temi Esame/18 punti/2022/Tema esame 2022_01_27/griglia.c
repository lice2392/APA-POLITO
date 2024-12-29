#include "griglia.h"

struct griglia{
    int **griglia;
    int nr,  nc;
};


static int **malloc2D(int nr, int nc);
static void free2D(int **mat, int nr);
static int minimo(int a, int b);


Griglia GRIGLIAinit(int nr, int nc){
    Griglia g;

    g=(Griglia)malloc(sizeof(struct griglia));
    if(g==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    g->nr=nr;
    g->nc=nc;
    g->griglia=malloc2D(nr, nc);
    return g;
}


Griglia GRIGLIAread(FILE *f){
    int i, nr, nc, j;
    Griglia g;
    fscanf(f, "%d %d", &nr, &nc);
    g=GRIGLIAinit(nr, nc);
    for(i=0; i<nr; i++)
       for(j=0; j<nc; j++)
          fscanf(f, "%d", &g->griglia[i][j]);
    return g;

}


void GRIGLIAfillRegione (Griglia g, int rI, int cI, int base, int altezza, int value){
    int i, j;
    for(i=rI; i<rI+altezza && i<g->nr; i++)
       for(j=cI; j<cI+base && j<g->nc; j++)
          g->griglia[i][j]=value;
    return;
}


void GRIGLIAdeleteRegione (Griglia g, int rI, int cI, int base, int altezza){
    int i, j;
    for(i=rI; i<rI+altezza && i<g->nr; i++)
       for(j=cI; j<cI+base && j<g->nc; j++)
          g->griglia[i][j]=BIANCO;
    return;
}


Boolean GRIGLIAcheckRegione(Griglia g, int rI, int cI, int base, int altezza){
    int i, j;
    for(i=rI; i<rI+altezza && i<g->nr; i++)
       for(j=cI; j<cI+base && j<g->nc; j++)
          if(g->griglia[i][j]!=BIANCO)
             return FALSO;
    return VERO;
}


int GRIGLIAareaBianco(Griglia g){
    int i, j, bianco=0;
    for(i=0; i<g->nr; i++)
       for(j=0; j<g->nc; j++)
          if(g->griglia[i][j]!=NERO)
             bianco++;
    return bianco;
}


void GRIGLIAreset(Griglia g){
    int i, j;
    for(i=0; i<g->nr; i++)
       for(j=0; j<g->nc; j++)
          if(g->griglia[i][j]!=NERO && g->griglia[i][j]!=BIANCO)
             g->griglia[i][j]=BIANCO;
    return;
}


int GRIGLIAgetMaxAreaBianco(Griglia g, int rI, int cI){
   int i, j, base, altezza;

   i=rI;
   altezza=0;
   while(i<g->nr && g->griglia[i][cI]==BIANCO){
      altezza++;
      i++;
   }

   j=cI;
   base=0;
   while(j<g->nc && g->griglia[rI][j]==BIANCO){
      base++;
      j++;
   }
   return minimo(base, altezza);
}


int GRIGLIAgetNumRighe(Griglia g){
    return g->nr;
}


int GRIGLIAgetNumColonne(Griglia g){
    return g->nc;
}


int GRIGLIAgetCella(Griglia g, int riga, int colonna){
    return g->griglia[riga][colonna];
}


void GRIGLIAprint(Griglia g, FILE *f){
    int i, j;

    for(i=0; i<g->nr; i++){
        for(j=0; j<g->nc; j++){
            fprintf(f, "%d%s", g->griglia[i][j], (g->griglia[i][j]>9)?" ":"  ");
        }
        fprintf(f, "\n");
    }
    return;
}


void GRIGLIAcopia(Griglia g1, Griglia g2){
    int i, j;

    for(i=0; i<g1->nr; i++){
        for(j=0; j<g1->nc; j++){
            g2->griglia[i][j]=g1->griglia[i][j];
        }
    }
    return;
}


void GRIGLIAfree(Griglia g){
    if(g!=NULL){
        free2D(g->griglia, g->nr);
        free(g);
    }
    return;
}



//funzioni static
static int **malloc2D(int nr, int nc){
    int i, **mat;
    mat=(int**)malloc(nr*sizeof(int));
    if(mat==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL){
            printf("Errore di allocazione.");
            exit(EXIT_FAILURE);
        }
    }
    return mat;
}


static int minimo(int a, int b){
    if(a<b)
       return a;
    return b;
}


static void free2D(int **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL)
                free(mat[i]);
        }
        free(mat);
    }
    return;
}
