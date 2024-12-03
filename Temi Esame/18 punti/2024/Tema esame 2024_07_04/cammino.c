#include "cammino.h"

struct cammino{
    int *vertici;
    Copertura copertura;
    int maxEl, dim, peso;
};


GraphPath GRAPHPATHinit(int nV){
    GraphPath p;

    p=(GraphPath)malloc(sizeof(struct cammino));
    if(p==NULL){
        exit(EXIT_FAILURE);
    }

    p->maxEl=1;
    p->dim=0;
    p->peso=0;
    p->copertura=COPERTURAinit(nV);

    p->vertici=(int*)malloc(p->maxEl*sizeof(int));
    if(p->vertici==NULL){
        exit(EXIT_FAILURE);
    }
    return p;
}




GraphPath GRAPHPATHread(Graph g, FILE *f){
    GraphPath p;
    int nV, idW, idV, width;
    Vertice w;

    nV=GRAPHgetNumVertici(g);

    p=GRAPHPATHinit(nV);

    w=VERTICEread(f);
    while(VERTICEisNull(w)==FALSO){
        idW=GRAPHgetIndexVertice(g, w);
        if(p->dim>0){
            idV=p->vertici[p->dim-1];
            width=GRAPHgetPesoArco(g, idV, idW);
            p->peso+=width;
        }
        GRAPHPATHaddVertice(p, idW);
        w=VERTICEread(f);
    }
    return p;
}




void GRAPHPATHaddVertice(GraphPath p, int vertice){
    if(p->maxEl==p->dim){
        p->maxEl=2*p->maxEl;
        p->vertici=(int*)realloc(p->vertici, p->maxEl*sizeof(int));
        if(p->vertici==NULL){
            exit(EXIT_FAILURE);
        }
    }
    p->vertici[p->dim++]=vertice;
    COPERTURAmarca(p->copertura, vertice);
    return;
}




Boolean GRAPHPATHisEmpty(GraphPath p){
    if(p->dim==0)
        return VERO;
    return FALSO;
}




Copertura GRAPHPATHgetCopertura(GraphPath p){
    return p->copertura;
}




int GRAPHPATHgetFirst(GraphPath p){
    if(p->dim>0)
        return p->vertici[0];
    return -1;
}




int GRAPHPATHgetLast(GraphPath p){
    if(p->dim>0)
        return p->vertici[p->dim-1];
    return -1;
}




void GRAPHPATHprint(GraphPath p, Graph g, FILE *f){
    int i, idV;
    Vertice v;

    for(i=0; i<p->dim; i++){
        idV=p->vertici[i];
        v=GRAPHgetVertice(g, idV);
        VERTICEprint(v, f);
        fprintf(f, " ");
    }
    fprintf(f, " [peso: %d]", p->peso);
    return;
}




Boolean GRAPHPATHisCamminoSemplice(GraphPath p){
    int *mark, i, vertice;
    Boolean ret=VERO;

    mark=(int*)calloc(COPERTURAgetNumVertici(p->copertura), sizeof(int));
    if(mark==NULL){
        exit(EXIT_FAILURE);
    }

    for(i=0; i<p->dim; i++){
        vertice=p->vertici[i];
        if(mark[vertice]==COPERTO){
            if(i!=p->dim-1){
                ret=FALSO;
                break;
            }
            if(i==p->dim-1 && vertice!=p->vertici[0]){
                ret=FALSO;
                break;
            }
        }
        mark[vertice]=COPERTO;
    }

    free(mark);
    return ret;
}




int GRAPHPATHgetPeso(GraphPath p){
    return p->peso;
}




int GRAPHPATHgetNumVertici(GraphPath p){
    return p->dim;
}




Boolean GRAPHPATHisCiclo(GraphPath p){
    if(p->vertici[0]==p->vertici[p->dim-1])
        return VERO;
    return FALSO;
}




void GRAPHPATHfree(GraphPath p){
    if(p!=NULL){
        COPERTURAfree(p->copertura);
        if(p->vertici!=NULL){
            free(p->vertici);
        }
        free(p);
    }
    return;
}
