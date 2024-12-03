#include "clienti.h"

struct clienti{
    Cliente *clienti;
    int dim, maxEl;
};

Clienti CLIENTIinit(){
    Clienti c;
    c=(Clienti)malloc(sizeof(struct clienti));
    if(c==NULL) exit(EXIT_FAILURE);

    c->dim=0;

    c->maxEl=1;

    c->clienti=(Cliente *)malloc(c->maxEl*sizeof(Cliente));
    if(c->clienti==NULL) exit(EXIT_FAILURE);

    return c;
}




Clienti CLIENTIread(FILE *f){
    Clienti c;
    Cliente cl;

    c=CLIENTIinit();

    cl=CLIENTEread(f);
    while(CLIENTEisNull(cl)==FALSO){
        CLIENTIinsertCliente(c, cl);
        cl=CLIENTEread(f);
    }
    return c;
}




void CLIENTIinsertCliente(Clienti c, Cliente cl){
    if(c->dim==c->maxEl){
        c->maxEl=2*c->maxEl;
        c->clienti=realloc(c->clienti, c->maxEl*sizeof(Cliente));
        if(c->clienti==NULL) exit(EXIT_FAILURE);
    }
    c->clienti[c->dim]=cl;
    c->dim++;
    return;
}




Cliente CLIENTIgetCliente(Clienti c, int index){
    return c->clienti[index];
}




int CLIENTIsearch(Clienti c, char *id){
    int i;

    for(i=0; i<c->dim; i++){
        if(strcmp(c->clienti[i].id, id)==0){
            return i;
        }
    }
    return -1;
}




int CLIENTIgetNumClienti(Clienti c){
    return c->dim;
}




void CLIENTIprint(Clienti c, FILE *f){
    int i;

    for(i=0; i<c->dim; i++){
        CLIENTEprint(c->clienti[i], f);
        fprintf(f, "\n");
    }
    return;
}




void CLIENTIfree(Clienti c){
    if(c!=NULL){
        if(c->clienti!=NULL){
            free(c->clienti);
        }
        free(c);
    }
    return;
}
