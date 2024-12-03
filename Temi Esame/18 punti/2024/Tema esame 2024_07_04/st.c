#include "st.h"

struct table{
    Vertice *vertici;
    int size, maxEl;
};


ST STinit(int maxEl){
    ST s;

    s=(ST)malloc(sizeof(struct table));
    if(s==NULL) exit(EXIT_FAILURE);

    s->maxEl=maxEl;
    s->size=0;

    s->vertici=(Vertice*)malloc(maxEl*sizeof(Vertice));
    if(s->vertici==NULL) exit(EXIT_FAILURE);

    return s;
}




void STinsert(ST s, Vertice v){
    if(s->size==s->maxEl){
        s->maxEl=2*s->maxEl;
        s->vertici=(Vertice*)realloc(s->vertici, s->maxEl*sizeof(Vertice));
        if(s->vertici==NULL) exit(EXIT_FAILURE);
    }
    s->vertici[s->size]=v;
    (s->size)++;
    return;
}




int STsearch(ST s, Vertice v){
    int i;

    for(i=0; i<s->size; i++){
        if(VERTICEcompare(s->vertici[i], v)==UGUALE){
            return i;
        }
    }
    return -1;
}




Vertice STgetByIndex(ST s, int index){
    if(index>=0 && index<s->size){
        return s->vertici[index];
    }
    return VERTICEsetNull();
}




void STfree(ST s){
    if(s!=NULL){
        if(s->vertici!=NULL){
            free(s->vertici);
        }
        free(s);
    }
    return;
}
