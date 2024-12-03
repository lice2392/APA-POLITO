#ifndef ALBERGO_H_INCLUDED
#define ALBERGO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int nCamere, nGiorniEvento;
    int **prenotazioni;
    int *nCamereOccupate;
}Albergo;

Albergo ALBERGOinit(int nCamere, int nGiorniEvento);
int ALBERGOisThereFreeRoom(Albergo a, int arrivo, int nGiorniPernottamento);
void ALBERGOinsertPrenotazione(Albergo *a, int idCliente, int camera, int arrivo, int nGiorniPernottamento);
void ALBERGOdeletePrenotazione(Albergo *a, int camera, int arrivo, int nGiorniPernottamento);
void ALBERGOreset(Albergo *a);
float ALBERGOgetRiempimentoMedio(Albergo a);
void ALBERGOclear(Albergo *a);

#endif // ALBERGO_H_INCLUDED
