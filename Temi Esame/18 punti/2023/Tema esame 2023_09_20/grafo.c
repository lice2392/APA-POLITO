#include "grafo.h"
#include <limits.h>

struct grafo{
   int V, E;
   int **matAdj;
};


//funzioni statiche
static int **MATRIXinit(int nr, int nc, int value);
static void MATRIXfree(int **mat, int nr);
static Boolean isKCapacitatedTreePartition(Grafo g, int *proposta, int *occ);
static Boolean isConnesso(Grafo g, int *proposta, int sottoinsieme);
static void dfsConnessione(Grafo g, int v, int *proposta, int sottoinsieme, int *visited);
static Boolean isDAG(Grafo g, int *proposta, int sottoinsieme);
static Boolean dfsArchiBack(Grafo g, int prec, int v, int *proposta, int sottoinsieme, int *pre, int *post, int *time);
static void dispRip(Grafo g, int k, int *sol, int *bestSol, int *occ, int *min, int pos);
static Boolean checkSol(Grafo g, int k, int *sol, int *occ);
static int getPesiTot(Grafo g, int *sol, int *occ);
static int pesiSott(Grafo g, int *sol, int sottoinsieme);
static void dfsPesi(Grafo g, int v, int *sol, int sottoinsieme, int *visited, int *peso);




Grafo GRAFOinit(int V){
    Grafo g;
    g=(Grafo)malloc(sizeof(struct grafo));
    if(g==NULL) exit(EXIT_FAILURE);
    g->V=V;
    g->E=0;
    g->matAdj=MATRIXinit(g->V, g->V, -1);
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
        for(j=0; j<nc; j++)
            mat[i][j]=value;
    }
    return mat;
}




Grafo GRAFOread(FILE *f){
   Grafo g;
   int V, id1, id2, w;

   fscanf(f, "%d", &V);

   g=GRAFOinit(V);

   while(fscanf(f, "%d %d %d", &id1, &id2, &w)==3){
      GRAFOinsertE(g, id1, id2, w);
   }
   return g;
}




void GRAFOinsertE(Grafo g, int id1, int id2, int w){
    if(g->matAdj[id1][id2]==-1){
       g->matAdj[id1][id2]=w;
       g->matAdj[id2][id1]=w;
       (g->E)++;
    }
    return;
}




//prima riga: numero N di sottoinsiemi che compongono la partizione
//seguono N righe (ogni riga i-esima rappresenta la i-esima partizione).
//Ogni riga contiene come primo elemento il numero di vertici che appartengono al sottoinsieme e, successivamente, i vertici che appartiene al sottoinsieme della partizione.
Boolean GRAFOverifica(char *nomeFile, Grafo g, int k){
   FILE *f;
   int n, sottoinsieme, i, nVertici, v;
   int *proposta, *occ;

   proposta=(int*)malloc(g->V*sizeof(int));
   if(proposta==NULL) exit(EXIT_FAILURE);

   occ=(int*)calloc(g->V, sizeof(int));
   if(occ==NULL) exit(EXIT_FAILURE);

   for(i=0; i<g->V; i++)
      proposta[i]=-1;

   f=fopen(nomeFile, "r");
   if(f==NULL) exit(EXIT_FAILURE);

   fscanf(f, "%d", &n);
   for(sottoinsieme=0; sottoinsieme<n; sottoinsieme++){
      fscanf(f, "%d", &nVertici);
      if(nVertici<k)
         return FALSO;
      for(i=0; i<nVertici; i++){
         fscanf(f, "%d", &v);
         //vertice non appartiene al grafo
         if(v<0|| v>=g->V)
            return FALSO;
         //vertice appartiene già ad un sottoinsieme
         if(proposta[v]!=-1)
            return FALSO;
         proposta[v]=sottoinsieme+1;
         occ[sottoinsieme]++;
      }
   }

   for(i=0; i<g->V; i++){
      //non tutti i vertici del grafo sono stati considerati
      if(proposta[i]==-1)
         return FALSO;
   }
   return isKCapacitatedTreePartition(g, proposta, occ);
}


static Boolean isKCapacitatedTreePartition(Grafo g, int *proposta, int *occ){
   int sottoinsieme, i;

   for(i=0; i<g->V; i++){
      if(occ[i]!=0){
        sottoinsieme=i+1;
        if(isConnesso(g, proposta, sottoinsieme)==FALSO) return FALSO;
        if(isDAG(g, proposta, sottoinsieme)==FALSO) return FALSO;
      }
   }
   return VERO;
}


static Boolean isConnesso(Grafo g, int *proposta, int sottoinsieme){
   int *visited, i;

   visited=(int*)calloc(g->V, sizeof(int));
   if(visited==NULL) exit(EXIT_FAILURE);

   for(i=0; i<g->V && proposta[i]!=sottoinsieme; i++);

   dfsConnessione(g, i, proposta, sottoinsieme, visited);

   for(i=0; i<g->V; i++)
      if(proposta[i]==sottoinsieme && visited[i]==0)
         return FALSO;
   return VERO;
}


static void dfsConnessione(Grafo g, int v, int *proposta, int sottoinsieme, int *visited){
   int w;
   visited[v]=1;
   for(w=0; w<g->V; w++){
      if(proposta[w]==sottoinsieme && g->matAdj[v][w]!=-1 && visited[w]==0){
         dfsConnessione(g, w, proposta, sottoinsieme, visited);
      }
   }
}


static Boolean isDAG(Grafo g, int *proposta, int sottoinsieme){
   int time, *pre, *post, i;

   time=0;

   pre=(int*)malloc(g->V*sizeof(int));
   if(pre==NULL) exit(EXIT_FAILURE);

   post=(int*)malloc(g->V*sizeof(int));
   if(post==NULL) exit(EXIT_FAILURE);

   for(i=0; i<g->V; i++){
      pre[i]=-1;
      post[i]=-1;
   }

   for(i=0; i<g->V && proposta[i]!=sottoinsieme; i++);

   return dfsArchiBack(g, -1, i, proposta, sottoinsieme, pre, post, &time);
}


static Boolean dfsArchiBack(Grafo g, int prec, int v, int *proposta, int sottoinsieme, int *pre, int *post, int *time){
   int w;
   pre[v]=(*time)++;
   for(w=0; w<g->V; w++){
      if(proposta[w]==sottoinsieme && w!= prec && g->matAdj[v][w]!=-1 && pre[w]==-1){
         if(dfsArchiBack(g, v, w, proposta, sottoinsieme, pre, post, time)==FALSO)
            return FALSO;
      }
      else if(proposta[w]==sottoinsieme && w!= prec && g->matAdj[v][w]!=-1 && post[w]==-1)
         return FALSO;
   }
   post[v]=(*time)++;
   return VERO;
}




void GRAFOsolve(Grafo g, int k){
   int *sol, *bestSol, min=INT_MAX;
   int sottoinsieme, i, *occ, j;

   sol=(int*)malloc(g->V*sizeof(int));
   if(sol==NULL) exit(EXIT_FAILURE);

   bestSol=(int*)malloc(g->V*sizeof(int));
   if(bestSol==NULL) exit(EXIT_FAILURE);

   occ=(int*)calloc(g->V, sizeof(int));
   if(occ==NULL) exit(EXIT_FAILURE);

   dispRip(g, k, sol, bestSol, occ, &min, 0);

   for(j=0; j<g->V; j++)
     occ[j]=0;

   for(j=0; j<g->V; j++)
     occ[bestSol[j]-1]++;

   printf("Best Solution:\n");
   for(j=0; j<g->V; j++){
      if(occ[j]>0){
         sottoinsieme=j+1;
         printf("E%d = { ", sottoinsieme);
         for(i=0; i<g->V; i++){
             if(bestSol[i]==sottoinsieme)
                printf("%d ", i);
          }
          printf("}\n");
      }
   }
   printf("Peso: %d\n", min);
   return;
}


static void dispRip(Grafo g, int k, int *sol, int *bestSol, int *occ, int *min, int pos){
   int sottoinsiemi, pesoTot, i;
   if(pos>=g->V){
      if(checkSol(g, k, sol, occ)==VERO){
         pesoTot=getPesiTot(g, sol, occ);
         if(pesoTot<(*min)){
            (*min)=pesoTot;
            for(i=0; i<g->V; i++){
                bestSol[i]=sol[i];
            }
         }
      }
      return;
   }
   for(sottoinsiemi=1; sottoinsiemi<=g->V; sottoinsiemi++){
      sol[pos]=sottoinsiemi;
      occ[sottoinsiemi-1]++;
      dispRip(g, k, sol, bestSol, occ, min, pos+1);
      occ[sottoinsiemi-1]--;
   }
}


static Boolean checkSol(Grafo g, int k, int *sol, int *occ){
   int i;

   for(i=0; i<g->V; i++){
      if(occ[i]>0 && occ[i]<k)
         return FALSO;
   }
   return isKCapacitatedTreePartition(g, sol, occ);
}


static int getPesiTot(Grafo g, int *sol, int *occ){
   int sottoinsieme, pesoTot=0, i;

   for(i=0; i<g->V; i++){
      if(occ[i]>0){
        sottoinsieme=i+1;
        pesoTot+=pesiSott(g, sol, sottoinsieme);
      }
   }
   return pesoTot;
}


static int pesiSott(Grafo g, int *sol, int sottoinsieme){
   int *visited, i, peso=0;

   visited=(int*)calloc(g->V, sizeof(int));
   if(visited==NULL) exit(EXIT_FAILURE);

   for(i=0; i<g->V && sol[i]!=sottoinsieme; i++);

   dfsPesi(g, i, sol, sottoinsieme, visited, &peso);
   return peso;
}


static void dfsPesi(Grafo g, int v, int *sol, int sottoinsieme, int *visited, int *peso){
   int w;
   visited[v]=1;
   for(w=0; w<g->V; w++){
      if(sol[w]==sottoinsieme && g->matAdj[v][w]!=-1 && visited[w]==0){
         (*peso)+=g->matAdj[v][w];
         dfsPesi(g, w, sol, sottoinsieme, visited, peso);
      }
   }
}




void GRAFOfree(Grafo g){
    if(g!=NULL){
        MATRIXfree(g->matAdj, g->V);
        free(g);
    }
    return;
}


static void MATRIXfree(int **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL)
                free(mat[i]);
        }
        free(mat);
    }
}
