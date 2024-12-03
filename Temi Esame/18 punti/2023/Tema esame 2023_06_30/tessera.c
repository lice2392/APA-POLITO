#include "tessera.h"

Tessera TESSERAread(FILE *f){
    Tessera t;
    fscanf(f, "%d %d %d %d", &t.nord, &t.sud, &t.ovest, &t.est);
    return t;
}




void TESSERAprint(Tessera t, FILE *f){
    fprintf(f, "%d %d %d %d", t.nord, t.sud, t.ovest, t.est);
    return;
}




Boolean TESSERAisSorgenteODestinazione(Tessera t){
    if(t.nord==1 && t.sud==0 && t.ovest==0 && t.est==0)
        return VERO;
    if(t.nord==0 && t.sud==1 && t.ovest==0 && t.est==0)
        return VERO;
    if(t.nord==0 && t.sud==0 && t.ovest==1 && t.est==0)
        return VERO;
    if(t.nord==0 && t.sud==0 && t.ovest==0 && t.est==1)
        return VERO;
    return FALSO;
}




Boolean TESSERAisBuco(Tessera t){
    if(t.nord==0 && t.sud==0 && t.ovest==0 && t.est==0)
        return VERO;
    return FALSO;
}




Simboli TESSERAcompare(Tessera t1, Tessera t2){
    if(t1.nord==t2.nord && t1.sud==t2.sud && t1.ovest==t2.ovest && t1.est==t2.est)
        return VERO;
    return FALSO;
}
