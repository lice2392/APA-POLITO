#include "citta.h"

Citta CITTAread(FILE *f){
    Citta c;
    char name[200];

    fscanf(f, "%s", name);

    c.nome=strdup(name);
    return c;
}




void CITTAprint(Citta c, FILE *f){
    fprintf(f, "%s", c.nome);
}




void CITTAclear(Citta c){
    if(c.nome!=NULL)
        free(c.nome);
    return;
}
