#include "mossa.h"

static Direzione fromStringToEnum(char *direzione);
static void stringToUpper(char *str);
static char * fromEnumToString(Direzione direzione);

Mossa MOSSAcrea(Direzione dir, Cella *tessere, int nTessereMosse){
    Mossa m;
    int i;

    m.direzione=dir;
    m.nTessereMosse=nTessereMosse;

    m.tessereMosse=(Cella*)malloc(nTessereMosse*sizeof(Cella));
    if(m.tessereMosse==NULL) exit(EXIT_FAILURE);

    for(i=0; i<nTessereMosse; i++){
       m.tessereMosse[i]=tessere[i];
    }
    return m;
}




Mossa MOSSAread(FILE *f){
    Mossa m;
    char direzione[256];
    int i;

    fscanf(f, "%s", direzione);
    stringToUpper(direzione);
    m.direzione=fromStringToEnum(direzione);

    fscanf(f, "%d", &m.nTessereMosse);
    m.tessereMosse=(Cella*)malloc(m.nTessereMosse*sizeof(Cella));
    if(m.tessereMosse==NULL) exit(EXIT_FAILURE);

    for(i=0; i<m.nTessereMosse; i++){
       m.tessereMosse[i]=CELLAread(f);
    }
    return m;
}


static Direzione fromStringToEnum(char *direzione){
    if(strcmp(direzione, "NORD")==0)
        return NORD;
    if(strcmp(direzione, "SUD")==0)
        return SUD;
    if(strcmp(direzione, "EST")==0)
        return EST;
    if(strcmp(direzione, "OVEST")==0)
        return OVEST;
    return -1;
}


static void stringToUpper(char *str){
    int i;
    for(i=0; i<strlen(str); i++){
        str[i]=toupper(str[i]);
    }
    return;
}




void MOSSAprint(Mossa m, FILE *f){
    int i;

    fprintf(f, "%s: ", fromEnumToString(m.direzione));
    for(i=0; i<m.nTessereMosse; i++){
        CELLAprint(m.tessereMosse[i], f);
        fprintf(f, " ");
    }
    return;
}


static char * fromEnumToString(Direzione direzione){
    if(direzione==NORD)
        return "NORD";
    if(direzione==SUD)
        return "SUD";
    if(direzione==EST)
        return "EST";
    if(direzione==OVEST)
        return "OVEST";
    return "";
}




void MOSSAclear(Mossa *m){
    if(m->tessereMosse!=NULL)
        free(m->tessereMosse);
    return;
}
