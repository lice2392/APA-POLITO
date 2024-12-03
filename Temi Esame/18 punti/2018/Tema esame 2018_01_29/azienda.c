#include "azienda.h"

Azienda AZIENDAread(FILE *f){
    Azienda a;
    fscanf(f, "%s", a.nome);
    return a;
}




void AZIENDAprint(Azienda a, FILE *f){
    fprintf(f, "%s", a.nome);
    return;
}




Azienda AZIENDAcrea(char *nome){
    Azienda a;
    strcpy(a.nome, nome);
    return a;
}
