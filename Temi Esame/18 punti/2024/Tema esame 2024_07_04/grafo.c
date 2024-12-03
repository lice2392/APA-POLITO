#include "grafo.h"

struct grafo{
    int nV, nE;
    ST table;
    int **matAdj;
};

static int **MATRIXinit(int nr, int nc, int value);
static void MATRIXfree(int **mat, int nr);


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




void GRAPHprint(Graph g, FILE *f){
    int v, w;
    Vertice ve, we;

    fprintf(f, "---VERICI---\n");
    for(v=0; v<g->nV; v++){
        ve=STgetByIndex(g->table, v);
        VERTICEprint(ve, f);
        fprintf(f, "%s", (v==g->nV-1)?"\n":", ");
    }

    fprintf(f, "\n---ARCHI---\n");
    for(v=0; v<g->nV; v++){
        ve=STgetByIndex(g->table, v);
        for(w=0; w<g->nV; w++){
            if(g->matAdj[v][w]!=-1){
                we=STgetByIndex(g->table, w);
                VERTICEprint(ve, f);
                fprintf(f, " ");
                VERTICEprint(we, f);
                fprintf(f, " %d\n", g->matAdj[v][w]);
            }
        }
    }
    return;
}




int GRAPHgetNumVertici(Graph g){
    return g->nV;
}




int GRAPHgetIndexVertice(Graph g, Vertice v){
    return STsearch(g->table, v);
}




Vertice GRAPHgetVertice(Graph g, int index){
    return STgetByIndex(g->table, index);
}




int GRAPHgetPesoArco(Graph g, int v, int w){
    return g->matAdj[v][w];
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
