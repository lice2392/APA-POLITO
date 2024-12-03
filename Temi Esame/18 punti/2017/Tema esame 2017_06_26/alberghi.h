#ifndef ALBERGHI_H_INCLUDED
#define ALBERGHI_H_INCLUDED
#include "albergo.h"

typedef struct alberghi *Alberghi;

Alberghi ALBERGHIinit(int N);
Alberghi ALBERGHIcrea(int N, int X, int *M);
Albergo ALBERGHIgetAlbergo(Alberghi a, int index);
int ALBERGHIgetNumAlberghi(Alberghi a);
void ALBERGHIreset(Alberghi a);
float ALBERGHIcalcoloFunzioneUtilizzoStrutture(Alberghi al, int a, int b);
void ALBERGHIfree(Alberghi a);

#endif // ALBERGHI_H_INCLUDED
