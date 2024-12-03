#include "cliente.h"

Cliente CLIENTEread(FILE *f){
    Cliente c;
    if(fscanf(f, "%s %d %d", c.id, &c.giornoArrivo, &c.giorniPernottamento)==3){
        return c;
    }
    return CLIENTEsetNull();
}




void CLIENTEprint(Cliente c, FILE *f){
    fprintf(f, "%s (%d %d)", c.id, c.giornoArrivo, c.giorniPernottamento);
    return;
}




Cliente CLIENTEsetNull(){
    Cliente c={"", -1, -1};
    return c;
}




Boolean CLIENTEisNull(Cliente c){
    if(strcmp(c.id, "")==0 && c.giorniPernottamento==-1 && c.giornoArrivo==-1)
        return VERO;
    return FALSO;
}
