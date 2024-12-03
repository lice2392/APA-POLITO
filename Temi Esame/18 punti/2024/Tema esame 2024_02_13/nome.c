#include "nome.h"

Nome NOMEcreate(char *nome){
    Nome n;

    strcpy(n.nome, nome);

    return n;
}
