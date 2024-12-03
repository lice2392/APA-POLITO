#include "grafo.h"

typedef struct node *link;

struct node{
    int val;
    link next;
};

struct grafo{
    int V, E;
    ST table;
    int **matAdj;
    link *cricche;
    int nCricche;
    int *nVerticiCricche;
};


static int **MATRIXinit(int nr, int nc, int value);
static void MATRIXfree(int **mat, int nr);
link *CRICCHEinit(int n);
void CRICCHEfree(link *cricche, int n);
static Boolean isCriccaMassimale(Grafo g, int *proposta, int nVerticiCricca);
static void findCricche(Grafo g, int *sol, int pos);
static link CRICCAinsert(link head, int v);
static link NEWNODE(int val, link next);
static int getNumVerticiCricca(int *sol, int dim);
static void CRICCAprint(Grafo g, int indexCricca, FILE *f);
static void findCicloHamilton(Grafo g, int indexCricca);
static void findCicloHamiltonR(Grafo g, int indexCricca, int v, int start, int *visited, int *sol, int *bestSol, int *max, int pesoAttuale, int lun);


Grafo GRAFOinit(){
    Grafo g;

    g=(Grafo)malloc(sizeof(struct grafo));
    if(g==NULL) exit(EXIT_FAILURE);

    g->V=0;
    g->E=0;

    g->matAdj=NULL;

    g->table=STinit(1);

    g->cricche=NULL;

    g->nVerticiCricche=NULL;

    g->nCricche=0;

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


link *CRICCHEinit(int n){
    link *vett;
    int i;

    vett=(link*)malloc(n*sizeof(link));
    if(vett==NULL) exit(EXIT_FAILURE);

    for(i=0; i<n; i++){
        vett[i]=NULL;
    }
    return vett;
}




Grafo GRAFOload(FILE *f){
    char label1[MAX], label2[MAX];
    int id1, id2, w;
    Grafo g;

    g=GRAFOinit();

    while(fscanf(f, "%s %s %*d", label1, label2)==2){
        id1=STsearch(g->table, label1);
        id2=STsearch(g->table, label2);
        if(id1==-1){
            STinsert(g->table, VERTICEcrea(label1));
            g->V++;
        }
        if(id2==-1){
            STinsert(g->table, VERTICEcrea(label2));
            g->V++;
        }
    }

    g->matAdj=MATRIXinit(g->V, g->V, -1);
    g->cricche=CRICCHEinit(g->V);

    g->nVerticiCricche=(int*)malloc(g->V*sizeof(int));
    if(g->nVerticiCricche==NULL) exit(EXIT_FAILURE);

    rewind(f);

    while(fscanf(f, "%s %s %d", label1, label2, &w)==3){
        id1=STsearch(g->table, label1);
        id2=STsearch(g->table, label2);
        if(id1!=-1 && id2!=-1){
            g->matAdj[id1][id2]=w;
            g->matAdj[id2][id1]=w;
            g->E++;
        }
    }
    return g;
}




Boolean GRAFOcheck(Grafo g, FILE *f){
    int *cricca;
    int nVertici, i, idV;
    char label[MAX];

    cricca=(int*)calloc(g->V, sizeof(int));
    if(cricca==NULL) exit(EXIT_FAILURE);

    fscanf(f, "%d", &nVertici);

    if(nVertici<0 || nVertici>g->V){
        return FALSO;
    }

    for(i=0; i<nVertici; i++){
        fscanf(f, "%s", label);
        idV=STsearch(g->table, label);
        if(idV==-1){
            return FALSO;
        }
        if(cricca[idV]==1){
            return FALSO;
        }
        cricca[idV]=1;
    }
    return isCriccaMassimale(g, cricca, nVertici);
}


static Boolean isCriccaMassimale(Grafo g, int *proposta, int nVerticiCricca){
    int v, w;
    int nArchi;

    //E' sottografo completo
    for(v=0; v<g->V; v++){
        if(proposta[v]==1){
            for(w=v+1; w<g->V; w++){
                if(proposta[w]==1 && g->matAdj[v][w]==-1){
                    return FALSO;
                }
            }
        }
    }

    //Cerco l'esistenza di almeno un vertice ad esterno al sottografo completo adiacente a tutti i suoi vertici
    for(v=0; v<g->V; v++){
        nArchi=0;
        if(proposta[v]==0){
            for(w=0; w<g->V; w++){
                if(proposta[w]==1 && g->matAdj[v][w]!=-1){
                    nArchi++;
                }
            }
            if(nArchi==nVerticiCricca){
                return FALSO;
            }
        }
    }
    return VERO;
}




void GRAFOsearch(Grafo g){
    int *sol, i, max, indexMax;

    sol=(int*)malloc(g->V*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    findCricche(g, sol, 0);

    printf("Le cricche massimali del grafo sono %d:\n", g->nCricche);
    for(i=0; i<g->nCricche; i++){
        printf("%d) ", i+1);
        CRICCAprint(g, i, stdout);
        printf("\n");
    }

    max=0;
    for(i=0; i<g->nCricche; i++){
        if(g->nVerticiCricche[i] > max){
            max=g->nVerticiCricche[i];
            indexMax=i;
        }
    }
    printf("\nLa cricca massimale con il massimo numero di vertici (MAX = %d) e':\n", g->nVerticiCricche[indexMax]);
    CRICCAprint(g, indexMax, stdout);
    printf("\n");

    for(i=0; i<g->nCricche; i++){
        findCicloHamilton(g, i);
    }

    free(sol);
    return;
}


static void findCricche(Grafo g, int *sol, int pos){
    int nVertici, i;

    if(pos>=g->V){
        nVertici=getNumVerticiCricca(sol, g->V);
        if(isCriccaMassimale(g, sol, nVertici)==VERO){
            for(i=0; i<g->V; i++){
                if(sol[i]==1){
                    g->cricche[g->nCricche]=CRICCAinsert(g->cricche[g->nCricche], i);
                }
            }
            g->nVerticiCricche[g->nCricche]=nVertici;
            (g->nCricche)++;
        }
        return;
    }
    sol[pos]=1;
    findCricche(g, sol, pos+1);
    sol[pos]=0;
    findCricche(g, sol, pos+1);
    return;
}


static link CRICCAinsert(link head, int v){
    link x;

    if(head==NULL){
        return NEWNODE(v, NULL);
    }

    for(x=head; x->next!=NULL; x=x->next);

    x->next=NEWNODE(v, NULL);
    return head;
}


static link NEWNODE(int val, link next){
    link x=malloc(sizeof(*x));

    x->val=val;
    x->next=next;
    return x;
}


static int getNumVerticiCricca(int *sol, int dim){
    int count=0, i;

    for(i=0; i<dim; i++){
        if(sol[i]==1){
            count++;
        }
    }
    return count;
}


static void CRICCAprint(Grafo g, int indexCricca, FILE *f){
    link x;
    for(x=g->cricche[indexCricca]; x!=NULL; x=x->next){
        VERTICEprint(STgetByIndex(g->table, x->val), f);
        fprintf(f, " ");
    }
    return;
}


static void findCicloHamilton(Grafo g, int indexCricca){
    int *visited, *sol, *bestSol;
    int max=0, i;

    sol=(int*)malloc(g->nVerticiCricche[indexCricca]*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(int*)malloc(g->nVerticiCricche[indexCricca]*sizeof(int));
    if(bestSol==NULL) exit(EXIT_FAILURE);

    visited=(int*)calloc(g->V, sizeof(int));
    if(visited==NULL) exit(EXIT_FAILURE);

    findCicloHamiltonR(g, indexCricca, g->cricche[indexCricca]->val, g->cricche[indexCricca]->val, visited, sol, bestSol, &max, 0, 0);

    printf("\nBest ciclo hamiltoniano per la cricca { ");
    CRICCAprint(g, indexCricca, stdout);
    printf("}:\n");
    printf("Peso massimo: %d\n", max);
    VERTICEprint(STgetByIndex(g->table, g->cricche[indexCricca]->val), stdout);
    printf(" ");
    for(i=0; i<g->nVerticiCricche[indexCricca]; i++){
        VERTICEprint(STgetByIndex(g->table, bestSol[i]), stdout);
        printf(" ");
    }
    printf("\n");

    free(sol);
    free(bestSol);
    free(visited);
    return;
}


static void findCicloHamiltonR(Grafo g, int indexCricca, int v, int start, int *visited, int *sol, int *bestSol, int *max, int pesoAttuale, int lun){
    int i;
    link x;

    if(v==start && lun==g->nVerticiCricche[indexCricca]){
        if(pesoAttuale > (*max)){
            (*max) = pesoAttuale;
            for(i=0; i<lun; i++){
                bestSol[i]=sol[i];
            }
        }
        return;
    }

    visited[v]=1;

    for(x=g->cricche[indexCricca]; x!=NULL; x=x->next){
        if(visited[x->val]==0 || (visited[x->val]==1 && x->val==start && lun==(g->nVerticiCricche[indexCricca]-1))){
            pesoAttuale+=g->matAdj[v][x->val];
            sol[lun]=x->val;
            findCicloHamiltonR(g, indexCricca, x->val, start, visited, sol, bestSol, max, pesoAttuale, lun+1);
            pesoAttuale-=g->matAdj[v][x->val];
        }
    }
    return;
}




void GRAFOfree(Grafo g){
    if(g!=NULL){
        STfree(g->table);
        MATRIXfree(g->matAdj, g->V);
        CRICCHEfree(g->cricche, g->nCricche);
        if(g->nVerticiCricche!=NULL){
            free(g->nVerticiCricche);
        }
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


void CRICCHEfree(link *cricche, int n){
    int i;
    link x, t, head;

    if(cricche!=NULL){
        for(i=0; i<n; i++){
            if(cricche[i]!=NULL){
                head=cricche[i];
                for(x=head; x!=NULL; x=t){
                    t=x->next;
                    free(x);
                }
            }
        }
        free(cricche);
    }
    return;
}
