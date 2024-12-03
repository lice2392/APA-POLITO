#ifndef ACTIVITIES_H_INCLUDED
#define ACTIVITIES_H_INCLUDED
#include "attivita.h"
#include <string.h>

typedef struct activities *ACT;


ACT ACTIVITIESinit(int maxN);
ACT ACTIVITIESread(FILE *f);
int ACTIVITIEScheckSelection(ACT a, char **selected, int nsel);
char** ACTIVITIESbestSelection(ACT a, int *nAtt, int *profittoMax);
void ACTIVITIESfree(ACT a);

#endif // ACTIVITIES_H_INCLUDED
