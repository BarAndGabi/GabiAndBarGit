#include <stdio.h>
#include <stdlib.h>
#include "Airline.h"
#include "AirportManager.h"
#include "AirportManagerTextFile.h"
#include "AirlineBinFile.h"
#include "General.h"
#define TEXT_FILE "airport_authority.txt"
#define BIN_FILE "airline.bin"

typedef enum
{
	eAddFlight,
	eAddAirport,
	ePrintCompany,
	ePrintAirports,
	ePrintNumFlightsOrig,
	ePrintFlightsPlaneCode,
	ePrintFlightsPlaneType,
	eSortFlights,
	eSearchFlight,
	eNofOptions
} eMenuOptions;

const char *str[eNofOptions] = {"Add Flight", "Add Airport",
								"Print Airline", "Print all Airports",
								"Print number of flights from origin airport name",
								"Print all flights with plane code",
								"Print all flights with plane type", "Sort flights", "Search flight"};

#define EXIT -1
int menu();

int main()
{
	AirportManager manager;
	Airline company;

	if (!readAirportsFromFile(TEXT_FILE, &manager))
	{
		initManager(&manager);
		initAirline(&company);
	}
	else
	{
		printf("sucsses manager from file\n");
		if (!readAirlineFromFile(BIN_FILE, &company))
		{
			printf("there is no airline binary file to read or there is an error with the file\n");
			initAirline(&company);
		}
		else
			printf("sucsses airline from file\n");
	}

	int option;
	int stop = 0;

	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;

		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintNumFlightsOrig:
			doCountFlightsFromName(&company);
			break;

		case ePrintFlightsPlaneCode:
			doPrintFlightsWithPlaneCode(&company);
			break;

		case ePrintFlightsPlaneType:
			doPrintFlightsWithPlaneType(&company);
			break;

		case eSortFlights:
			sortFlights(&company);
			break;
		case eSearchFlight:
			searchFlight(&company);
			break;
		case EXIT:
			printf("Bye bye\n");
			writeAirportsToFile(TEXT_FILE, &manager);
			writeAirlineToFile(BIN_FILE, &company);
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	freeManager(&manager);
	freeCompany(&company);
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}