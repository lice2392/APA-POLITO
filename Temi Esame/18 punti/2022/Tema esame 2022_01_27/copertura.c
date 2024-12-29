#include "copertura.h"
#include <limits.h>

struct copertura{
    Regione *regioni;
    int dim, maxD;
};

static void solveR(Griglia g, Griglia tmp, Copertura sol, Copertura bestSol, int *min, int currNumRegion, int pos);

Copertura COPERTURAinit(int maxD){
    Copertura c;

    c=(Copertura)malloc(sizeof(struct copertura));
    if(c==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    c->maxD=maxD;
    c->dim=0;
    c->regioni=(Regione*)malloc(maxD*sizeof(Regione));
    if(c->regioni==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    return c;
}


Copertura COPERTURAread(FILE *f){
    Copertura c;
    Regione r;
    c=COPERTURAinit(1);
    r=REGIONEread(f);
    while(REGIONEisNull(r)==FALSO){
       COPERTURAinsert(c, r);
       r=REGIONEread(f);
    }
    return c;
}


void COPERTURAinsert(Copertura c, Regione r){
    if(c->maxD==c->dim){
       c->maxD=c->maxD*2;
       c->regioni=realloc(c->regioni, c->maxD*sizeof(Regione));
       if(c->regioni==NULL){
          printf("Errore di allocazione.");
          exit(EXIT_FAILURE);
       }
    }
    c->regioni[c->dim]=r;
    (c->dim)++;
    return;
}


void COPERTURAdelete(Copertura c){
    (c->dim)--;
    return;
}


Boolean COPERTURAcheck(Copertura c, Griglia g, int *nRegioni, int areaBianco){
    int i, area=0;
    for(i=0; i<c->dim; i++){
        if(c->regioni[i].base!=c->regioni[i].altezza)
           return FALSO;
        if(c->regioni[i].riga <0 || c->regioni[i].riga>=GRIGLIAgetNumRighe(g))
           return FALSO;
        if(c->regioni[i].colonna<0 || c->regioni[i].colonna>=GRIGLIAgetNumColonne(g))
           return FALSO;
        if(c->regioni[i].riga+c->regioni[i].altezza>GRIGLIAgetNumRighe(g))
           return FALSO;
        if(c->regioni[i].colonna+c->regioni[i].base>GRIGLIAgetNumColonne(g))
           return FALSO;
        if(GRIGLIAcheckRegione(g, c->regioni[i].riga, c->regioni[i].colonna, c->regioni[i].base, c->regioni[i].altezza)==FALSO)
           return FALSO;
        GRIGLIAfillRegione(g, c->regioni[i].riga, c->regioni[i].colonna, c->regioni[i].base, c->regioni[i].altezza, i+2);
        area=area+(c->regioni[i].base*c->regioni[i].altezza);
    }
    if(area!=areaBianco)
       return FALSO;
    (*nRegioni)=c->dim;
    return VERO;
}


void COPERTURAsolve(Griglia g){
    Copertura sol, bestSol;
    int min=INT_MAX, currNumRegion=0;
    Griglia tmp;

    sol=COPERTURAinit(1);
    bestSol=COPERTURAinit(1);
    tmp=GRIGLIAinit(GRIGLIAgetNumRighe(g), GRIGLIAgetNumColonne(g));

    GRIGLIAcopia(g, tmp);

    solveR(g, tmp, sol, bestSol, &min, currNumRegion, 0);

    printf("La soluzione ottima utilizza %d regioni quadrate per coprire l'intera regione bianca.\n\n", bestSol->dim);
    printf("~~~ELENCO REGIONI:~~~\n");
    COPERTURAprint(bestSol, stdout);
    printf("\n~~~GRIGLIA:~~~\n");
    GRIGLIAprint(g, stdout);

    COPERTURAfree(sol);
    COPERTURAfree(bestSol);
    GRIGLIAfree(tmp);
    return;
}


void COPERTURAprint(Copertura c, FILE *f){
   int i;
   for(i=0; i<c->dim; i++){
      fprintf(f, "Regione %d: %s", i+1, (i+1>9)?"":" ");
      REGIONEprint(c->regioni[i], f);
      fprintf(f, "\n");
   }
   return;
}


void COPERTURAfree(Copertura c){
    if(c!=NULL){
        if(c->regioni!=NULL){
            free(c->regioni);
        }
        free(c);
    }
    return;
}




//funzioni static
static void solveR(Griglia g, Griglia tmp, Copertura sol, Copertura bestSol, int *min, int currNumRegion, int pos){
    int lato, maxAreaBianco, j;
    int r, c;

    if(currNumRegion >= (*min)){
        return;
    }

    if(pos>=(GRIGLIAgetNumRighe(g)*GRIGLIAgetNumColonne(g))){
       if(currNumRegion < (*min)){
          (*min)=currNumRegion;
          bestSol->dim=0;
          for(j=0; j<currNumRegion; j++){
             COPERTURAinsert(bestSol, sol->regioni[j]);
          }
          GRIGLIAcopia(tmp, g);
       }
       return;
    }

    r=pos/GRIGLIAgetNumColonne(tmp);
    c=pos%GRIGLIAgetNumColonne(tmp);

    if(GRIGLIAgetCella(tmp, r, c)!=BIANCO){
       solveR(g, tmp, sol, bestSol, min, currNumRegion, pos+1);
       return;
    }
    maxAreaBianco=GRIGLIAgetMaxAreaBianco(tmp, r, c);
    for(lato=maxAreaBianco; lato>=1; lato--){
       if(GRIGLIAcheckRegione(tmp, r, c, lato, lato)==FALSO){
          continue;
       }
       COPERTURAinsert(sol, REGIONEcrea(r, c, lato, lato));
       GRIGLIAfillRegione(tmp, r, c, lato, lato, currNumRegion+2);
       solveR(g, tmp, sol, bestSol, min, currNumRegion+1, pos+lato);
       COPERTURAdelete(sol);
       GRIGLIAdeleteRegione(tmp, r, c, lato, lato);
    }
    return;
}
