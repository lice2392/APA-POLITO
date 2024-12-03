#include "sedi.h"

struct pronto{
    int *citta;
    int M;
};


Sedi SEDIinit(int M){
    Sedi s;

    s=(Sedi)malloc(sizeof(struct pronto));
    if(s==NULL){
        exit(EXIT_FAILURE);
    }

    s->M=M;

    s->citta=(int*)malloc(M*sizeof(int));
    if(s->citta==NULL){
        exit(EXIT_FAILURE);
    }
    return s;
}




Sedi SEDIread(char *nomeFile, Elenco e){
    FILE *f;
    int dim, i;
    Citta c;
    Sedi s;

    f=fopen(nomeFile, "r");
    if(f==NULL){
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", &dim);

    s=SEDIinit(dim);

    for(i=0; i<dim; i++){
        c=CITTAread(f);
        s->citta[i]=ELENCOsearch(e, c);
        CITTAclear(c);
    }
    return s;
}




void SEDIprint(Sedi s, FILE *f, Elenco e){
    Citta c;
    int i;

    fprintf(f, "{ ");
    for(i=0; i<s->M; i++){
        c=ELENCOgetCittaByIndex(e, s->citta[i]);
        CITTAprint(c, f);
        fprintf(f, " ");
    }
    fprintf(f, "}");
    return;
}




int SEDIgetSede(Sedi s, int index){
    return s->citta[index];
}




int SEDIgetNumSedi(Sedi s){
    return s->M;
}




void SEDIfree(Sedi s){
    if(s!=NULL){
        if(s->citta!=NULL){
            free(s->citta);
        }
        free(s);
    }
    return;
}
