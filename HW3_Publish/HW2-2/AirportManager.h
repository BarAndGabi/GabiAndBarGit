#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"

typedef struct
{
	Airport*	airportsArr;
	int			airportsCount;
}AirportManager;

int		initManager(AirportManager* pManager);
int		addAirport(AirportManager* pManager);
void	initAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByName(const AirportManager* pManager, const char* name);
int		checkUniqeName(const char* name, const AirportManager* pManager);
void	printAirports(const AirportManager* pManager);
void    writeAirportsToFile(const char* fileName, AirportManager* pManager);
Airport*    readAirportsFromFile(const char* fileName, int* size);
void	freeManager(AirportManager* pManager);
void    freeAirportsArr(Airport* ports,int size);
#endif