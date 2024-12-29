#include "regione.h"

Regione REGIONEcrea(int riga, int colonna, int base, int altezza){
    Regione r;
    r.riga=riga;
    r.colonna=colonna;
    r.base=base;
    r.altezza=altezza;
    return r;
}


Regione REGIONEsetNull(){
    Regione r;
    r.riga=-1;
    r.colonna=-1;
    r.base=-1;
    r.altezza=-1;
    return r;
}


Regione REGIONEread(FILE *f){
    Regione r;
    if(fscanf(f, "%d %d %d %d", &r.riga, &r.colonna, &r.base, &r.altezza)==4)
       return r;
    return REGIONEsetNull();
}


Boolean REGIONEisNull(Regione r){
    if(r.riga==-1 && r.colonna==-1 &&r.base==-1 && r.altezza==-1)
       return VERO;
    return FALSO;
}


void REGIONEprint(Regione r, FILE *f){
    fprintf(f, "(%d, %d) %s- Lato: %d", r.riga, r.colonna, (r.riga>9 || r.colonna>9)?"":" ", r.base);
    return;
}
