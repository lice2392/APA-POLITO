#include "famiglie.h"

struct famiglie{
    Famiglia *famiglie;
    int dim;
};


Famiglie FAMIGLIEinit(int S){
    Famiglie f;

    f=(Famiglie)malloc(sizeof(struct famiglie));
    if(f==NULL) exit(EXIT_FAILURE);

    f->dim=S;

    f->famiglie=(Famiglia*)malloc(S*sizeof(Famiglia));
    if(f->famiglie==NULL) exit(EXIT_FAILURE);

    return f;
}




Famiglie FAMIGLIEread(Koalas k, FILE *f, int N, int S){
    Famiglie fa;
    int i;

    fa=FAMIGLIEinit(S);

    for(i=0; i<S; i++){
        fa->famiglie[i]=FAMIGLIAread(k, f, N, S, i);
    }
    return fa;
}




void FAMIGLIEreadNemici(Famiglie fa, FILE *f){
    char famiglia1[MAXC], famiglia2[MAXC];
    int id1, id2;

    while(fscanf(f, "%s %s", famiglia1, famiglia2)==2){
        id1=FAMIGLIEsearch(fa, famiglia1);
        id2=FAMIGLIEsearch(fa, famiglia2);
        FAMIGLIAaddNemico(&fa->famiglie[id1], id2);
        FAMIGLIAaddNemico(&fa->famiglie[id2], id1);
    }
    return;
}




int FAMIGLIEsearch(Famiglie f, char *nome){
    int i;

    for(i=0; i<f->dim; i++){
        if(strcmp(f->famiglie[i].nome, nome)==0){
            return i;
        }
    }
    return -1;
}




Famiglia *FAMIGLIEgetFamigliaByIndex(Famiglie f, int index){
    return &f->famiglie[index];
}




void FAMIGLIEfree(Famiglie f){
    int i;

    if(f!=NULL){
        if(f->famiglie!=NULL){
            for(i=0; i<f->dim; i++){
                FAMIGLIAclear(&f->famiglie[i]);
            }
            free(f->famiglie);
        }
        free(f);
    }
    return;
}
