#include "vertexSeq.h"

struct sequenza{
    Vertice *vertici;
    int size, maxEl;
};


vertexSeq VERTEXSEQinit(){
    vertexSeq s;

    s=(vertexSeq)malloc(sizeof(struct sequenza));
    if(s==NULL) exit(EXIT_FAILURE);

    s->maxEl=1;
    s->size=0;

    s->vertici=(Vertice*)malloc(s->maxEl*sizeof(Vertice));
    if(s->vertici==NULL) exit(EXIT_FAILURE);
    return s;
}




vertexSeq VERTEXSEQread(FILE *fp){
    vertexSeq vs;
    Vertice v;

    vs=VERTEXSEQinit();

    v=VERTICEread(fp);

    while(VERTICEisNull(v)==FALSO){
        VERTEXSEQinsert(vs, v);
        v=VERTICEread(fp);
    }
    return vs;
}




void VERTEXSEQinsert(vertexSeq vs, Vertice v){
    if(vs->size==vs->maxEl){
        vs->maxEl=2*vs->maxEl;
        vs->vertici=(Vertice*)realloc(vs->vertici, vs->maxEl*sizeof(Vertice));
        if(vs->vertici==NULL) exit(EXIT_FAILURE);
    }
    vs->vertici[vs->size]=v;
    (vs->size)++;
    return;
}




int VERTEXSEQsearch(vertexSeq vs, Vertice v){
    int i;

    for(i=0; i<vs->size; i++){
        if(VERTICEcompare(vs->vertici[i], v)==UGUALE){
            return i;
        }
    }
    return -1;
}




Vertice VERTEXSEQgetByIndex(vertexSeq vs, int index){
    if(index>=0 && index<vs->size){
        return vs->vertici[index];
    }
    return VERTICEsetNull();
}




int VERTEXSEQgetSize(vertexSeq vs){
    return vs->size;
}




void VERTEXSEQprint(vertexSeq vs, FILE *f){
    int i;

    for(i=0; i<vs->size; i++){
        fprintf(f, "\t");
        VERTICEprint(vs->vertici[i], f);
        fprintf(f, "\n");
    }
    return;
}




void VERTEXSEQfree(vertexSeq vs){
    if(vs!=NULL){
        if(vs->vertici!=NULL){
            free(vs->vertici);
        }
        free(vs);
    }
    return;
}
