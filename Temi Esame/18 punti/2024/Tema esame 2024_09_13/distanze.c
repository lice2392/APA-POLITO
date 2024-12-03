#include "distanze.h"

struct dist{
    int **mat;
    int N;
};

static int**MATRIXinit(int nr, int nc);
static void MATRIXfree(int **mat, int nr);


Distanze DISTANZEinit(int N){
    Distanze d;

    d=(Distanze)malloc(sizeof(struct dist));
    if(d==NULL){
        exit(EXIT_FAILURE);
    }

    d->N=N;
    d->mat=MATRIXinit(N, N);
    return d;
}


int **MATRIXinit(int nr, int nc){
    int **mat;
    int i;

    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL){
        exit(EXIT_FAILURE);
    }

    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL){
            exit(EXIT_FAILURE);
        }
    }
    return mat;
}




Distanze DISTANZEread(FILE *f, int N){
    Distanze d;
    int i, j;

    d=DISTANZEinit(N);

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            fscanf(f, "%d", &d->mat[i][j]);
        }
    }
    return d;
}




int DISTANZEgetDistanza(Distanze d, int riga, int colonna){
    return d->mat[riga][colonna];
}




int DISTANZEgetNumCitta(Distanze d){
    return d->N;
}




void DISTANZEprint(Distanze d, FILE *f){
    for(int i=0; i<d->N; i++){
        for(int j=0; j<d->N; j++){
            fprintf(f, "%d ", d->mat[i][j]);
        }
        fprintf(f, "\n");
    }
    return;
}




void DISTANZEfree(Distanze d){
    if(d!=NULL){
        MATRIXfree(d->mat, d->N);
        free(d);
    }
    return;
}


static void MATRIXfree(int **mat, int nr){
    if(mat!=NULL){
        for(int i=0; i<nr; i++){
            if(mat[i]!=NULL){
                free(mat[i]);
            }
        }
        free(mat);
    }
    return;
}
