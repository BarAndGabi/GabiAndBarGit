#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "fileHelper.h"

void initFlight(Flight *pFlight, const AirportManager *pManager)
{
	Airport *pPortOr = setAiportToFlight(pManager, "Enter name of origin airport:");
	pFlight->nameSource = _strdup(pPortOr->name);
	int same;
	Airport *pPortDes;
	do
	{
		pPortDes = setAiportToFlight(pManager, "Enter name of destination airport:");
		same = isSameAirport(pPortOr, pPortDes);
		if (same)
			printf("Same origin and destination airport\n");
	} while (same);
	pFlight->nameDest = _strdup(pPortDes->name);
	initPlane(&pFlight->thePlane);
	getCorrectDate(&pFlight->date);
}

int isFlightFromSourceName(const Flight *pFlight, const char *nameSource)
{
	if (strcmp(pFlight->nameSource, nameSource) == 0)
		return 1;

	return 0;
}

int isFlightToDestName(const Flight *pFlight, const char *nameDest)
{
	if (strcmp(pFlight->nameDest, nameDest) == 0)
		return 1;

	return 0;
}

int isPlaneCodeInFlight(const Flight *pFlight, const char *code)
{
	if (strcmp(pFlight->thePlane.code, code) == 0)
		return 1;
	return 0;
}

int isPlaneTypeInFlight(const Flight *pFlight, ePlaneType type)
{
	if (pFlight->thePlane.type == type)
		return 1;
	return 0;
}

void printFlight(const Flight *pFlight)
{
	printf("Flight From %s To %s\t", pFlight->nameSource, pFlight->nameDest);
	printDate(&pFlight->date);
	printPlane(&pFlight->thePlane);
}

void printFlightV(const void *val)
{
	const Flight *pFlight = *(const Flight **)val;
	printFlight(pFlight);
}

Airport *setAiportToFlight(const AirportManager *pManager, const char *msg)
{
	char name[MAX_STR_LEN];
	Airport *port;
	do
	{
		printf("%s\t", msg);
		myGets(name, MAX_STR_LEN, stdin);
		port = findAirportByName(pManager, name);
		if (port == NULL)
			printf("No airport with this name - try again\n");
	} while (port == NULL);

	return port;
}

void freeFlight(Flight *pFlight)
{
	free(pFlight->nameSource);
	free(pFlight->nameDest);
	free(pFlight);
}

int saveFlightToFile(const Flight *pF, FILE *fp)
{
	if (!writeStringToFile(pF->nameSource, fp, "Error write flight source name\n"))
		return 0;

	if (!writeStringToFile(pF->nameDest, fp, "Error write flight destination name\n"))
		return 0;

	if (!savePlaneToFile(&pF->thePlane, fp))
		return 0;

	if (!saveDateToFile(&pF->date, fp))
		return 0;

	return 1;
}

int loadFlightFromFile(Flight *pF, const AirportManager *pManager, FILE *fp)
{

	pF->nameSource = readStringFromFile(fp, "Error reading source name\n");
	if (!pF->nameSource)
		return 0;

	if (findAirportByName(pManager, pF->nameSource) == NULL)
	{
		printf("Airport %s not in manager\n", pF->nameSource);
		free(pF->nameSource);
		return 0;
	}

	pF->nameDest = readStringFromFile(fp, "Error reading destination name\n");
	if (!pF->nameDest)
	{
		free(pF->nameSource);
		return 0;
	}

	if (findAirportByName(pManager, pF->nameDest) == NULL)
	{
		printf("Airport %s not in manager\n", pF->nameDest);
		free(pF->nameSource);
		free(pF->nameDest);
		return 0;
	}

	if (!loadPlaneFromFile(&pF->thePlane, fp))
	{
		free(pF->nameSource);
		free(pF->nameDest);
		return 0;
	}

	if (!loadDateFromFile(&pF->date, fp))
	{
		free(pF->nameSource);
		free(pF->nameDest);
		return 0;
	}

	return 1;
}

int loadFlightFromFileCompressed(Flight* pFlight, const AirportManager *pManager, FILE *fp)
{
	char add = 65;
	BYTE bytes1[2];
	BYTE bytes2[3];
	BYTE bytes3[1];
	if (fread(&bytes1, sizeof(BYTE), 2, fp) != 2)
	{
		fclose(fp);
		return 0;
	}
	if (fread(&bytes2, sizeof(BYTE), 3, fp) != 3)
	{
		fclose(fp);
		return 0;
	}
	if (fread(&bytes3, sizeof(BYTE), 1, fp) != 1)
	{
		fclose(fp);
		return 0;
	}
	int sourceNameLen = bytes1[0] >> 3 & 0x1F;
	pFlight->nameSource = readStringFromFile2(fp, sourceNameLen);
	if (findAirportByName(pManager, pFlight->nameSource) == NULL)
	{
		printf("Airport %s not in manager\n", pFlight->nameSource);
		free(pFlight->nameSource);
		return 0;
	}
	int destNameLen = (bytes1[0] << 2 | bytes1[1] >> 6) & 0x1F;
	pFlight->nameDest = readStringFromFile2(fp, destNameLen);
	if (findAirportByName(pManager, pFlight->nameDest) == NULL)
	{
		printf("Airport %s not in manager\n", pFlight->nameDest);
		free(pFlight->nameDest);
		return 0;
	}
	pFlight->thePlane.type = (bytes1[1] >> 4) & 0x3;
	pFlight->date.month = bytes1[1] & 0xF;
	pFlight->date.day = bytes3[0] & 0x1F;
	pFlight->date.year = (bytes2[2] & 0xF) + 2021;
	pFlight->thePlane.code[0] = ((bytes2[0] >> 3) & 0x1F) + add;
	pFlight->thePlane.code[1] = ((bytes2[0] << 2 | bytes2[1] >> 6) & 0x1F) + add;
	pFlight->thePlane.code[2] = ((bytes2[1] >> 1) & 0x1F) + add;
	pFlight->thePlane.code[3] = ((bytes2[1] << 4 | bytes2[2] >> 4) & 0x1F) + add;
	return 1;
}

int saveFlightToFileCompressed( Flight *pFlight, FILE *fp)
{
	BYTE bytes1[2] = { 0 };
	BYTE bytes2[3] = { 0 };
	BYTE bytes3[1] = { 0 };
	int sourceLen = (int)strlen(pFlight->nameSource);
	int destLen = (int)strlen(pFlight->nameDest);
	bytes1[0] = sourceLen << 3 | destLen >> 2;
	bytes1[1] = destLen << 6 | pFlight->thePlane.type << 4 | pFlight->date.month;
	if (fwrite(&bytes1, sizeof(BYTE), 2, fp) != 2) {
		fclose(fp);
		return 0;
	}
	for (size_t i = 0; i < 4; i++)
	{
		pFlight->thePlane.code[i]= pFlight->thePlane.code[i]-65;
	}
	pFlight->date.year += (-2021);
	bytes2[0] = pFlight->thePlane.code[0] << 3 | pFlight->thePlane.code[1] >> 2;
	bytes2[1] = pFlight->thePlane.code[1] << 6 | pFlight->thePlane.code[2] << 1 | pFlight->thePlane.code[3] >> 4;
	bytes2[2] = pFlight->thePlane.code[3] << 4 | pFlight->date.year;
	if (fwrite(&bytes2, sizeof(BYTE), 3, fp) !=3) {
		fclose(fp);
		return 0;
	}
	bytes3[0] = pFlight->date.day;
	if (fwrite(&bytes3, sizeof(BYTE), 1, fp) != 1) {
		fclose(fp);
		return 0;
	}
	if (fwrite(pFlight->nameSource, sizeof(char), sourceLen, fp) != sourceLen) {
		fclose(fp);
		return 0;
	}
	if (fwrite(pFlight->nameDest, sizeof(char), destLen, fp) != destLen) {
		fclose(fp);
		return 0;
	}
	return 1;
}

int compareFlightBySourceName(const void *flight1, const void *flight2)
{
	const Flight *pFlight1 = *(const Flight **)flight1;
	const Flight *pFlight2 = *(const Flight **)flight2;
	return strcmp(pFlight1->nameSource, pFlight2->nameSource);
}

int compareFlightByDestName(const void *flight1, const void *flight2)
{
	const Flight *pFlight1 = *(const Flight **)flight1;
	const Flight *pFlight2 = *(const Flight **)flight2;
	return strcmp(pFlight1->nameDest, pFlight2->nameDest);
}

int compareFlightByPlaneCode(const void *flight1, const void *flight2)
{
	const Flight *pFlight1 = *(const Flight **)flight1;
	const Flight *pFlight2 = *(const Flight **)flight2;
	return strcmp(pFlight1->thePlane.code, pFlight2->thePlane.code);
}

int compareFlightByDate(const void *flight1, const void *flight2)
{
	const Flight *pFlight1 = *(const Flight **)flight1;
	const Flight *pFlight2 = *(const Flight **)flight2;

	return compareDate(&pFlight1->date, &pFlight2->date);

	return 0;
}
