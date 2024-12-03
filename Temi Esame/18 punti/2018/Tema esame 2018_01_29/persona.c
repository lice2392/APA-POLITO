#include "persona.h"

Persona PERSONAread(FILE *f){
    Persona p;
    fscanf(f, "%s", p.nome);
    return p;
}




void PERSONAprint(Persona p, FILE *f){
    fprintf(f, "%s", p.nome);
    return;
}




Persona PERSONAcrea(char *nome){
    Persona p;
    strcpy(p.nome, nome);
    return p;
}
