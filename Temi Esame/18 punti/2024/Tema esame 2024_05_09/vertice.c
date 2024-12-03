#include "vertice.h"

Vertice VERTICEread(FILE *f){
    Vertice v;

    if(fscanf(f, "%s", v.nome)==1){
        return v;
    }
    return VERTICEsetNull();
}




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




Boolean VERTICEisNull(Vertice v){
    if(strcmp(v.nome, "")==0){
        return VERO;
    }
    return FALSO;
}




Simbolo VERTICEcompare(Vertice v1, Vertice v2){
    if(strcmp(v1.nome, v2.nome)==0){
        return UGUALE;
    }
    return DIVERSO;
}
