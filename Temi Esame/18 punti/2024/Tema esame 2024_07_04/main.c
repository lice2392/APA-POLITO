#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "set.h"
#define FILEGRAFO "grafo.txt"
#define FILESET "set.txt" //SET con tutti cammini semplici, no cicli, non vertici interni comuni
#define FILESET2 "set2.txt" //SET i cui cammini non sono tutti semplici, no cicli, vertici interni comuni
#define FILESET3 "set3.txt" //SET con tutti cammini semplici, cicli, vertici interni non comuni
#define FILESET4 "set4.txt" //SET con tutti cammini semplici, no cicli, vertici interni comuni

int main()
{
    FILE *fg, *fs;
    Graph g;
    GraphPathSet ps;

    fg=fopen(FILEGRAFO, "r");
    if(fg==NULL){
        exit(EXIT_FAILURE);
    }

    g=GRAPHload(fg);
    GRAPHprint(g, stdout);

    fs=fopen(FILESET4, "r");
    if(fs==NULL){
        exit(EXIT_FAILURE);
    }

    ps=GRAPHPATHSETread(g, fs);
    printf("\n");
    GRAPHPATHSETprint(ps, g, stdout);

    printf("\n---PROBLEMA DI VERIFICA---\n");
    if(GRAPHPATHSETcheck(ps)==VERO){
        printf("Il set non contiene alcun cammino che abbia vertici interni comuni con gli altri cammini.\n");
    }
    else{
        printf("Il set contiene almeno un cammino con vertici interni comuni con gli altri cammini.\n");
    }

    printf("\n---PROBLEMA DI RICERCA E OTTIMIZZAZIONE---\n");
    GRAPHPATHSETbestPath(ps, g);
    return 0;
}
