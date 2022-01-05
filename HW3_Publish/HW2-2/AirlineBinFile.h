#ifndef _AIRLINE_BIN_
#define _AIRLINE_BIN_

#include "Airline.h"
int readAirlineFromFile(char *fileName, Airline *a);
void writeAirlineToFile(const char *fileName, Airline *pComp);
#endif
