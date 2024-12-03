#include "grafo.h"

struct grafo{
    int nV, nE;
    ST table;
    int **matAdj;
};

static int **MATRIXinit(int nr, int nc, int value);
static void MATRIXfree(int **mat, int nr);
static Boolean isCorrectPath(Graph g, vertexSeq vs);
static void bestPathR(Graph g, vertexSeq S1, vertexSeq S2, int v, int *sol, int *visited, int *bestSol, int peso, int *max, int *bestLun, int pos);
int getNumVerticiIntersezione(Graph g, vertexSeq S1, vertexSeq S2, int *sol, int dim);


Graph GRAPHinit(int V){
    Graph g;

    g=(Graph)malloc(sizeof(struct grafo));
    if(g==NULL) exit(EXIT_FAILURE);

    g->nV=V;
    g->nE=0;
    g->table=STinit(V);
    g->matAdj=MATRIXinit(g->nV, g->nV, -1);
    return g;
}


static int **MATRIXinit(int nr, int nc, int value){
    int **mat, i, j;

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
    Graph g;
    int V, i, wt, id1, id2;
    Vertice vertice;
    char label1[MAX], label2[MAX];

    fscanf(f, "%d", &V);

    g=GRAPHinit(V);

    for(i=0; i<V; i++){
        vertice=VERTICEread(f);
        STinsert(g->table, vertice);
    }

    while(fscanf(f, "%s %s %d", label1, label2, &wt)==3){
        id1=STsearch(g->table, VERTICEcrea(label1));
        id2=STsearch(g->table, VERTICEcrea(label2));
        if(id1!=-1 && id2!=-1){
            GRAPHinsertEdge(g, id1, id2, wt);
        }
    }
    return g;
}




void GRAPHinsertEdge(Graph g, int id1, int id2, int wt){
    g->matAdj[id1][id2]=wt;
    (g->nE)++;
    return;
}




int checkCommonPath(Graph g, vertexSeq p1, vertexSeq p2, int min){
    int i, nVerticiComuni;
    Vertice v;

    if(isCorrectPath(g, p1)==FALSO || isCorrectPath(g, p2)==FALSO){
        return FALSO;
    }

    nVerticiComuni=0;
    for(i=0; i<VERTEXSEQgetSize(p1); i++){
        v=VERTEXSEQgetByIndex(p1, i);
        if(VERTEXSEQsearch(p2, v)!=-1){
            nVerticiComuni++;
            if(i==(VERTEXSEQgetSize(p1)-1)){
               if((nVerticiComuni-1)>=min){
                    return VERO;
               }
            }
        }
        else{
            if((nVerticiComuni-1)>=min){
                return VERO;
            }
            nVerticiComuni=0;
        }

    }
    printf("\nI cammini sono corretti ma non hanno un sottocammino comune lungo almeno %d\n", min);
    return FALSO;
}


static Boolean isCorrectPath(Graph g, vertexSeq vs){
    int i, idPrec, id;
    Vertice v;

    v=VERTEXSEQgetByIndex(vs, 0);
    idPrec=STsearch(g->table, v);
    if(idPrec==-1){
        printf("\nCammino non corretto: ");
        VERTICEprint(v, stdout);
        printf(" non e' un vertice del grafo.\n");
        return FALSO;
    }
    for(i=1; i<VERTEXSEQgetSize(vs); i++){
        v=VERTEXSEQgetByIndex(vs, i);
        id=STsearch(g->table, v);
        if(id==-1){
            printf("\nCammino non corretto: ");
            VERTICEprint(v, stdout);
            printf(" non e' un vertice del grafo.\n");
            return FALSO;
        }
        if(g->matAdj[idPrec][id]==-1){
            printf("\nCammino non corretto: i vertici ");
            VERTICEprint(STgetByIndex(g->table, idPrec), stdout);
            printf(" e ");
            VERTICEprint(v, stdout);
            printf(" non sono connessi.\n");
            return FALSO;
        }
        idPrec=id;
    }
    return VERO;
}




void bestPath(Graph g, vertexSeq S1, vertexSeq S2){
    int *sol, *bestSol, *visited;
    int start, max=0, bestLun=0, i;
    Vertice v;

    sol=(int*)malloc(g->nV*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(int*)malloc(g->nV*sizeof(int));
    if(bestSol==NULL) exit(EXIT_FAILURE);

    for(start=0; start<g->nV; start++){
        v=STgetByIndex(g->table, start);
        if(VERTEXSEQsearch(S1, v)==-1 && VERTEXSEQsearch(S2, v)==-1){
            continue;
        }
        visited=(int*)calloc(g->nV, sizeof(int));
        if(visited==NULL) exit(EXIT_FAILURE);
        sol[0]=start;
        bestPathR(g, S1, S2, start, sol, visited, bestSol, 0, &max, &bestLun, 1);
        free(visited);
    }

    if(max==0){
        printf("\nNon e' stato possibile trovare il cammino ottimo che rispetti le condizioni date.\n");
    }
    else{
        printf("\n---BEST SOLUTION---\n");
        printf("Peso massimo: %d\n", max);
        printf("Cammino:\n");
        for(i=0; i<(bestLun-1); i++){
            printf("\t");
            VERTICEprint(STgetByIndex(g->table, bestSol[i]), stdout);
            printf(" ");
            VERTICEprint(STgetByIndex(g->table, bestSol[i+1]), stdout);
            printf(" %d\n", g->matAdj[bestSol[i]][bestSol[i+1]]);
        }
    }
    free(sol);
    free(bestSol);
    return;
}


static void bestPathR(Graph g, vertexSeq S1, vertexSeq S2, int v, int *sol, int *visited, int *bestSol, int peso, int *max, int *bestLun, int pos){
    Boolean fine=VERO;
    int w, i;
    Vertice vertice;

    visited[v]=1;

    for(w=0; w<g->nV; w++){
        vertice=STgetByIndex(g->table, w);
        if(visited[w]==1){
            continue;
        }
        if(g->matAdj[v][w]==-1){
            continue;
        }
        if(VERTEXSEQsearch(S1, vertice)==-1 && VERTEXSEQsearch(S2, vertice)==-1){
            continue;
        }
        sol[pos]=w;
        peso+=g->matAdj[v][w];
        bestPathR(g, S1, S2, w, sol, visited, bestSol, peso, max, bestLun, pos+1);
        peso-=g->matAdj[v][w];
        fine=FALSO;
    }

    if(fine==VERO){
        if(peso > (*max) && getNumVerticiIntersezione(g, S1, S2, sol, pos) >= (pos/2)){
            (*max)=peso;
            (*bestLun)=pos;
            for(i=0; i<pos; i++){
                bestSol[i]=sol[i];
            }
        }
    }
    visited[v]=0;
    return;
}


int getNumVerticiIntersezione(Graph g, vertexSeq S1, vertexSeq S2, int *sol, int dim){
    int count, i;
    Vertice vertice;

    count=0;
    for(i=0; i<dim; i++){
        vertice=STgetByIndex(g->table, sol[i]);
        if(VERTEXSEQsearch(S1, vertice)!=-1 && VERTEXSEQsearch(S2, vertice)!=-1){
            count++;
        }
    }
    return count;
}




void GRAPHfree(Graph g){
    if(g!=NULL){
        STfree(g->table);
        MATRIXfree(g->matAdj, g->nV);
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
