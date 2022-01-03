#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"

int compareFlightBySourceName(const void **f1, const void **f2)
{
	const Flight *flight1 = *(const Flight **)f1;
	const Flight *flight2 = *(const Flight **)f2;
	return strcmp(flight1->nameSource, flight2->nameSource);
}
int compareFlightByDestName(const void **f1, const void **f2)
{

	const Flight *flight1 = *(const Flight **)f1;
	const Flight *flight2 = *(const Flight **)f2;
	return strcmp(flight1->nameDest, flight2->nameDest);
}

int compareFlightByPlainCode(const void **f1, const void **f2)
{
	const Flight *flight1 = *(const Flight **)f1;
	const Flight *flight2 = *(const Flight **)f2;
	return strcmp(flight1->thePlane.code, flight2->thePlane.code);
}
int compareFlightByDate(const void **f1, const void **f2)
{
	const Flight *flight1 = *(const Flight **)f1;
	const Flight *flight2 = *(const Flight **)f2;

	return compareDate(&flight1->date, &flight2->date);
}