#include "cella.h"

Cella CELLAread(FILE *f){
    Cella c;
    fscanf(f, "%d %d", &c.riga, &c.colonna);
    return c;
}




void CELLAprint(Cella c, FILE *f){
    fprintf(f, "(%d, %d)", c.riga, c.colonna);
    return;
}




Cella CELLAcreate(int riga, int colonna){
    Cella c;
    c.riga=riga;
    c.colonna=colonna;
    return c;
}
