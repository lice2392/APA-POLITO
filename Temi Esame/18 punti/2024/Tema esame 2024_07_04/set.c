#include "set.h"

struct set{
    GraphPath *cammini;
    int maxEl, dim;
};

static void bestPathR(GraphPathSet ps, int *sol, int*bestSol, int *mark, int *maxP, int *maxV, int *bestLun, int pesoTot, int nVerticiTot, int pos);
static Boolean isCiclo(GraphPathSet ps, int *sol, int dimS);
static Boolean checkCopertura(GraphPathSet ps, int *sol, int dimS, GraphPath scelta);


GraphPathSet GRAPHPATHSETinit(){
    GraphPathSet ps;

    ps=(GraphPathSet)malloc(sizeof(struct set));
    if(ps==NULL){
        exit(EXIT_FAILURE);
    }

    ps->maxEl=1;
    ps->dim=0;

    ps->cammini=(GraphPath*)malloc(ps->maxEl*sizeof(GraphPath));
    if(ps->cammini==NULL){
        exit(EXIT_FAILURE);
    }
    return ps;
}




GraphPathSet GRAPHPATHSETread(Graph g, FILE *f){
    GraphPathSet ps;
    GraphPath p;

    ps=GRAPHPATHSETinit();

    p=GRAPHPATHread(g, f);

    while(GRAPHPATHisEmpty(p)==FALSO){
        GRAPHPATHSETaddCammino(ps, p);
        p=GRAPHPATHread(g, f);
    }
    if(GRAPHPATHisEmpty(p)==VERO){
        GRAPHPATHfree(p);
    }
    return ps;
}




void GRAPHPATHSETprint(GraphPathSet ps, Graph g, FILE *f){
    int i;

    fprintf(f, "---SET CAMMINI---\n");
    for(i=0; i<ps->dim; i++){
        fprintf(f, "CAMMINO #%d: ", i+1);
        GRAPHPATHprint(ps->cammini[i], g, f);
        fprintf(f, "\n");
    }
    return;
}




void GRAPHPATHSETaddCammino(GraphPathSet ps, GraphPath p){
    if(ps->maxEl==ps->dim){
        ps->maxEl=2*ps->maxEl;
        ps->cammini=(GraphPath*)realloc(ps->cammini, ps->maxEl*sizeof(GraphPath));
        if(ps->cammini==NULL){
            exit(EXIT_FAILURE);
        }
    }
    ps->cammini[ps->dim++]=p;
    return;
}




Boolean GRAPHPATHSETcheck(GraphPathSet ps){
    Boolean ret=VERO;
    Copertura *unioni;
    Copertura *copCammini;
    int i, last, first;

    copCammini=(Copertura*)malloc(ps->dim*sizeof(Copertura));
    unioni=(Copertura*)malloc(ps->dim*sizeof(Copertura));
    if(copCammini==NULL || unioni==NULL){
        exit(EXIT_FAILURE);
    }

    for(i=0; i<ps->dim; i++){
       copCammini[i]=GRAPHPATHgetCopertura(ps->cammini[i]);
    }

    for(i=0; i<ps->dim; i++){
       unioni[i]=COPERTURAgetUnione(copCammini, ps->dim, i);
    }

    for(i=0; i<ps->dim; i++){
       first=GRAPHPATHgetFirst(ps->cammini[i]);
       last=GRAPHPATHgetLast(ps->cammini[i]);
       COPERTURAsmarca(copCammini[i], first);
       COPERTURAsmarca(copCammini[i], last);
       if(COPERTURAhaIntersezione(copCammini[i], unioni[i])==VERO){
          ret=FALSO;
          break;
       }
       COPERTURAmarca(copCammini[i], first);
       COPERTURAmarca(copCammini[i], last);
    }

    if(ret==FALSO){
       COPERTURAmarca(copCammini[i], first);
       COPERTURAmarca(copCammini[i], last);
    }

    free(copCammini);
    free(unioni);
    return ret;
}




void GRAPHPATHSETbestPath(GraphPathSet ps, Graph g){
    int *sol, *bestSol, maxP=0, maxV=0, bestLun;
    int *mark, i;

    sol=(int*)malloc(ps->dim*sizeof(int));
    bestSol=(int*)malloc(ps->dim*sizeof(int));
    mark=(int*)calloc(ps->dim, sizeof(int));
    if(sol==NULL || bestSol==NULL || mark==NULL){
        exit(EXIT_FAILURE);
    }

    bestPathR(ps, sol, bestSol, mark, &maxP, &maxV, &bestLun, 0, 0, 0);

    printf("Peso massimo: %d\n", maxP);
    printf("Numero vertici cammino: %d\n", maxV);
    printf("BEST SOLUTION: ");
    for(i=0; i<bestLun; i++){
        GRAPHPATHprint(ps->cammini[bestSol[i]], g, stdout);
        printf("%s", i==bestLun-1?"\n":" | ");
    }
    return;
}


static void bestPathR(GraphPathSet ps, int *sol, int*bestSol, int *mark, int *maxP, int *maxV, int *bestLun, int pesoTot, int nVerticiTot, int pos){
    int i, j, last, first;

    if(pos>0 && pesoTot > (*maxP)){
        (*maxP)=pesoTot;
        (*maxV)=nVerticiTot+1;
        (*bestLun)=pos;
        for(j=0; j<pos; j++){
            bestSol[j]=sol[j];
        }
    }
    else if(pos>0 && pesoTot == (*maxP) && (nVerticiTot+1) > (*maxV)){
        (*maxV)=nVerticiTot+1;
        (*bestLun)=pos;
        for(j=0; j<pos; j++){
            bestSol[j]=sol[j];
        }
    }

    if(pos>=ps->dim || (pos>0 && isCiclo(ps, sol, pos)==VERO)){
        return;
    }

    for(i=0; i<ps->dim; i++){
        if(mark[i]==1){
            continue;
        }
        if(GRAPHPATHisCamminoSemplice(ps->cammini[i])==FALSO){
            continue;
        }
        if(pos>0){
            last=GRAPHPATHgetLast(ps->cammini[sol[pos-1]]);
            first=GRAPHPATHgetFirst(ps->cammini[i]);
            if(last!=first){
                continue;
            }
        }
        if(pos>0 && checkCopertura(ps, sol, pos, ps->cammini[i])==FALSO){
            continue;
        }
        sol[pos]=i;
        mark[i]=1;
        bestPathR(ps, sol, bestSol, mark, maxP, maxV, bestLun, pesoTot+GRAPHPATHgetPeso(ps->cammini[i]), nVerticiTot+GRAPHPATHgetNumVertici(ps->cammini[i])-1, pos+1);
        mark[i]=0;
    }
    return;
}


static Boolean isCiclo(GraphPathSet ps, int *sol, int dimS){
    int first, last;

    first=GRAPHPATHgetFirst(ps->cammini[sol[0]]);
    last=GRAPHPATHgetLast(ps->cammini[sol[dimS-1]]);

    if(first==last)
        return VERO;
    return FALSO;
}




static Boolean checkCopertura(GraphPathSet ps, int *sol, int dimS, GraphPath scelta){
    Copertura copScelta, copCamminoSol;
    int firstScelta, firstCamminoSol, i;
    Boolean ret=VERO;


    copScelta=GRAPHPATHgetCopertura(scelta);

    if(GRAPHPATHisCiclo(scelta)==FALSO){
        firstScelta=GRAPHPATHgetFirst(scelta);
        COPERTURAsmarca(copScelta, firstScelta);
    }

    for(i=0; i<dimS; i++){
        copCamminoSol=GRAPHPATHgetCopertura(ps->cammini[sol[i]]);
        if(GRAPHPATHisCiclo(ps->cammini[sol[i]])==FALSO){
            firstCamminoSol=GRAPHPATHgetFirst(ps->cammini[sol[i]]);
            COPERTURAsmarca(copCamminoSol, firstCamminoSol);
        }
        if(COPERTURAhaIntersezione(copCamminoSol, copScelta)==VERO){
            if(GRAPHPATHisCiclo(ps->cammini[sol[i]])==FALSO){
                COPERTURAmarca(copCamminoSol, firstCamminoSol);
            }
            ret=FALSO;
            break;
        }
        if(GRAPHPATHisCiclo(ps->cammini[sol[i]])==FALSO){
            COPERTURAmarca(copCamminoSol, firstCamminoSol);
        }
    }

    if(GRAPHPATHisCiclo(scelta)==FALSO){
        COPERTURAmarca(copScelta, firstScelta);
    }
    return ret;
}




void GRAPHPATHSETfree(GraphPathSet ps){
    if(ps!=NULL){
        if(ps->cammini!=NULL){
            for(int i=0; i<ps->dim; i++){
                GRAPHPATHfree(ps->cammini[i]);
            }
            free(ps->cammini);
        }
        free(ps);
    }
    return;
}
