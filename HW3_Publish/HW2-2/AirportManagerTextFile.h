#ifndef _AIRPORTMANAGER_TEXT_
#define _AIRPORTMANAGER_TEXT_

#include "AirportManager.h"

int readAirportsFromFile(const char *fileName, AirportManager *pManager);
void writeAirportsToFile(const char *fileName, AirportManager *pManager);

#endif