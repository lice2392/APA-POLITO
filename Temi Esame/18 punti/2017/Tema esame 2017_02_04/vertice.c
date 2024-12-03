#include "vertice.h"

Vertice VERTICEcrea(char *nome){
    Vertice v;
    strcpy(v.nome, nome);
    return v;
}




void VERTICEprint(Vertice v, FILE *f){
    fprintf(f, "%s", v.nome);
    return;
}




Vertice VERTICEsetNull(){
    Vertice v;
    strcpy(v.nome, "");
    return v;
}
