#include "vertice.h"

Vertice VERTICEread(FILE *f){
    Vertice v;

    fscanf(f, "%s %d", v.nome, &v.val);
    return v;
}




void VERTICEprint(Vertice v, FILE *f){
    fprintf(f, "%s %d", v.nome, v.val);
    return;
}
