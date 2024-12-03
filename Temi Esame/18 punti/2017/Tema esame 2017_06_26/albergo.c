#include "albergo.h"
#define EMPTY -1

typedef enum{VERO, FALSO}Boolean;

int **malloc2D(int nr, int nc, int value);
void free2D(int **mat, int nr);


Albergo ALBERGOinit(int nCamere, int nGiorniEvento){
    Albergo a;

    a.nCamere=nCamere;
    a.nGiorniEvento=nGiorniEvento;
    a.prenotazioni=malloc2D(nCamere, nGiorniEvento, EMPTY);

    a.nCamereOccupate=calloc(nGiorniEvento, sizeof(int));
    if(a.nCamereOccupate==NULL) exit(EXIT_FAILURE);
    return a;
}


int **malloc2D(int nr, int nc, int value){
    int  **mat;
    int i, j;

    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);

    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }

    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            mat[i][j]=value;
        }
    }
    return mat;
}




int ALBERGOisThereFreeRoom(Albergo a, int arrivo, int nGiorniPernottamento){
    int camera, giorno;
    Boolean trovato;

    for(camera=0; camera<a.nCamere; camera++){
        trovato=VERO;
        for(giorno=arrivo; giorno<arrivo+nGiorniPernottamento && giorno<a.nGiorniEvento; giorno++){
            if(a.prenotazioni[camera][giorno]!=EMPTY){
                trovato=FALSO;
                break;
            }
        }
        if(trovato==VERO){
            return camera;
        }
    }
    return -1;
}




void ALBERGOinsertPrenotazione(Albergo *a, int idCliente, int camera, int arrivo, int nGiorniPernottamento){
    int giorno;

    for(giorno=arrivo; giorno<arrivo+nGiorniPernottamento && giorno<a->nGiorniEvento; giorno++){
        a->prenotazioni[camera][giorno]=idCliente;
        a->nCamereOccupate[giorno]++;
    }
    return;
}




void ALBERGOdeletePrenotazione(Albergo *a, int camera, int arrivo, int nGiorniPernottamento){
    int giorno;

    for(giorno=arrivo; giorno<arrivo+nGiorniPernottamento && giorno<a->nGiorniEvento; giorno++){
        a->prenotazioni[camera][giorno]=EMPTY;
        a->nCamereOccupate[giorno]--;
    }
    return;
}




void ALBERGOreset(Albergo *a){
    int i, j;

    for(i=0; i<a->nCamere; i++){
        for(j=0; j<a->nGiorniEvento; j++){
            a->prenotazioni[i][j]=EMPTY;
        }
    }

    for(i=0; i<a->nGiorniEvento; i++){
        a->nCamereOccupate[i]=0;
    }
    return;
}




float ALBERGOgetRiempimentoMedio(Albergo a){
    int somma, i;
    float ret;

    somma=0;
    for(i=0; i<a.nGiorniEvento; i++){
        somma+=a.nCamereOccupate[i];
    }

    ret=(float)somma / ((float)(a.nCamere*a.nGiorniEvento));
    return ret;
}




void ALBERGOclear(Albergo *a){
    if(a->nCamereOccupate!=NULL){
        free(a->nCamereOccupate);
    }
    free2D(a->prenotazioni, a->nCamere);
}


void free2D(int **mat, int nr){
    int i;

    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL){
                free(mat[i]);
            }
        }
        free(mat);
    }
    return;
}
