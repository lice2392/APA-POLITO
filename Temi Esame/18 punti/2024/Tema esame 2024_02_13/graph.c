#include "graph.h"

struct grafo{
    int V, E;
    int **matAdj;
    ST table;
    Nomi nomiVertici;
};


static int **MATRIXinit(int nr, int nc, int value);
static void MATRIXfree(int **mat, int nr);
static Boolean checkR(Graph g, char *stringa, int lunStringa, int v, char *cammino, int index, int lun);
static void copiaStringa(char *nomeV, char*cammino, int start, int lun);
static void bestPathR(Graph g, int M, int v, int *ripetizioni, int *sol, int nVerticiCammino, int *bestSol, int *bestLun, int *max, int currentVal);
static Boolean isVocale(char c);


Graph GRAPHinit(int V){
    Graph g;

    g=(Graph)malloc(sizeof(struct grafo));
    if(g==NULL) exit(EXIT_FAILURE);

    g->V=V;
    g->E=0;

    g->matAdj=MATRIXinit(V, V, -1);

    g->table=STinit(V);

    g->nomiVertici=NOMIinit();

    return g;
}


static int **MATRIXinit(int nr, int nc, int value){
    int i, j;
    int **mat;

    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);

    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }

    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            mat[i][j]=value;
        }
    }
    return mat;
}




Graph GRAPHload(FILE *f){
    int V, E;
    Graph g;
    int i;
    Vertice v;
    int id1, id2, indexNome;

    fscanf(f, "%d %d", &V, &E);
    g=GRAPHinit(V);
    g->E=E;

    for(i=0; i<V; i++){
        fscanf(f, "%*d");
        v=VERTICEread(f);
        STinsert(g->table, v);
        indexNome=NOMIsearch(g->nomiVertici, v.nome);
        if(indexNome==-1){
            NOMIinsert(g->nomiVertici, NOMEcreate(v.nome));
        }
    }

    for(i=0; i<E; i++){
        fscanf(f, "%d %d", &id1, &id2);
        if(id1>=0 && id1<V && id2>=0 && id2<V){
           g->matAdj[id1][id2]=1;
           g->matAdj[id2][id1]=1;
        }
    }
    return g;
}




Boolean GRAPHcheckString(Graph g, char *stringa){
    char *cammino;
    int lunghezzaStringa;
    int vertice, lun, index, start;
    Vertice v;

    lunghezzaStringa=strlen(stringa);

    cammino=(char*)malloc(lunghezzaStringa+1*sizeof(char));
    if(cammino==NULL) exit(EXIT_FAILURE);

    lun=0;
    index=0;
    start=-1;
    for(vertice=0; vertice<g->V; vertice++){
        v=STgetByIndex(g->table, vertice);
        if(strncmp(stringa, v.nome, strlen(v.nome))==0){
            start=vertice;
            copiaStringa(v.nome, cammino, index, strlen(v.nome));
            lun+=strlen(v.nome);
            index=lun;
            break;
        }
    }
    if(start==-1){
        return FALSO;
    }
    return checkR(g, stringa, lunghezzaStringa, start, cammino, index, lun);
}


static Boolean checkR(Graph g, char *stringa, int lunStringa, int v, char *cammino, int index, int lun){
    int w;
    Vertice vertice;
    Boolean fine=VERO;

    for(w=0; w<g->V; w++){
        if(g->matAdj[v][w]==-1){
            continue;
        }
        vertice=STgetByIndex(g->table, w);
        if(strncmp(stringa+index, vertice.nome, strlen(vertice.nome))!=0){
            continue;
        }
        if((strlen(vertice.nome)+lun)>lunStringa){
            continue;
        }
        copiaStringa(vertice.nome, cammino, index, strlen(vertice.nome));
        lun+=strlen(vertice.nome);
        index=lun;
        if(checkR(g, stringa, lunStringa, w, cammino, index, lun)==VERO){
            return VERO;
        }
        fine=FALSO;
        lun-=strlen(vertice.nome);
        index=lun;
        cammino[index]='\0';
    }

    if(fine==VERO){
        if(lun==lunStringa && strcmp(cammino, stringa)==0){
            return VERO;
        }
        return FALSO;
    }
    return FALSO;
}


static void copiaStringa(char *nomeV, char*cammino, int start, int lun){
    int i;

    for(i=start; i<start+lun; i++){
        cammino[i]=nomeV[i-start];
    }
    cammino[i]='\0';
    return;
}




void GRAPHbestPath(Graph g, int M){
    int *ripetizioni;
    int v, max, maxLunSol, bestLun;
    int *sol, *bestSol;
    Vertice vertice;
    int idNome, i;

    maxLunSol=NOMIgetCount(g->nomiVertici)*M;

    sol=(int*)malloc(maxLunSol*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(int*)malloc(maxLunSol*sizeof(int));
    if(bestSol==NULL) exit(EXIT_FAILURE);

    max=0;
    for(v=0; v<g->V; v++){
        ripetizioni=calloc(NOMIgetCount(g->nomiVertici), sizeof(int));
        if(ripetizioni==NULL) exit(EXIT_FAILURE);
        vertice=STgetByIndex(g->table, v);
        idNome=NOMIsearch(g->nomiVertici, vertice.nome);
        sol[0]=v;
        ripetizioni[idNome]++;
        bestPathR(g, M, v, ripetizioni, sol, 1, bestSol, &bestLun, &max, vertice.val);
        free(ripetizioni);
    }

    printf("Best Solution:\n");
    printf("Valore massimo: %d\n", max);
    printf("Cammino con nomi ripetuti al massimo M = %d volte:\n", M);
    for(i=0; i<bestLun; i++){
        vertice=STgetByIndex(g->table, bestSol[i]);
        VERTICEprint(vertice, stdout);
        printf("%s", i==(bestLun-1)?"\n":" - ");
    }
    free(sol);
    free(bestSol);
    return;
}


static void bestPathR(Graph g, int M, int v, int *ripetizioni, int *sol, int nVerticiCammino, int *bestSol, int *bestLun, int *max, int currentVal){
    Boolean fine=VERO;
    int w, idNome, i, lunV;
    Vertice vertice, precedente;

    for(w=0; w<g->V; w++){
        if(g->matAdj[v][w]==-1){
            continue;
        }
        vertice=STgetByIndex(g->table, w);
        idNome=NOMIsearch(g->nomiVertici, vertice.nome);
        if(ripetizioni[idNome]==M){
            continue;
        }
        precedente=STgetByIndex(g->table, v);
        lunV=strlen(precedente.nome);
        if(isVocale(precedente.nome[lunV-1])==VERO && isVocale(vertice.nome[0])==VERO){
            continue;
        }
        if(isVocale(precedente.nome[lunV-1])==FALSO && isVocale(vertice.nome[0])==FALSO){
            continue;
        }
        ripetizioni[idNome]++;
        currentVal+=vertice.val;
        sol[nVerticiCammino]=w;
        bestPathR(g, M, w, ripetizioni, sol, nVerticiCammino+1, bestSol, bestLun, max, currentVal);
        fine=FALSO;
        currentVal-=vertice.val;
        ripetizioni[idNome]--;
    }

    if(fine==VERO){
        if(currentVal > (*max)){
            (*max) = currentVal;
            (*bestLun) = nVerticiCammino;
            for(i=0; i<nVerticiCammino; i++){
                bestSol[i]=sol[i];
            }
        }
        return;
    }
    return;
}


static Boolean isVocale(char c){
    c=tolower(c);

    if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
        return VERO;
    }
    return FALSO;
}




void GRAPHfree(Graph g){
    if(g!=NULL){
        STfree(g->table);
        MATRIXfree(g->matAdj, g->V);
        NOMIfree(g->nomiVertici);
        free(g);
    }
    return;
}


static void MATRIXfree(int **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL){
                free(mat[i]);
            }
        }
        free(mat);
    }
    return;
}
