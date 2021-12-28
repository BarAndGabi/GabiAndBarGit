#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"

int compareFlightBySourceName(const Flight * f1, const Flight* f2)
{
	const Flight* flight1 =(const Flight*)f1;
	const Flight* flight2 = (const Flight*)f2;
	if (flight1->nameSource < flight2->nameSource)
		return -1;
	else
		if (flight1->nameSource > flight2->nameSource)
			return 1;
		else
			return 0;

}
int compareFlightByDestName(const void * f1, const void* f2)
{

	const Flight* flight1 = (const Flight*)f1;
	const Flight* flight2 = (const Flight*)f2;
	if (flight1->nameDest < flight2->nameDest)
		return -1;
	else
		if (flight1->nameDest > flight2->nameDest)
			return 1;
		else
			return 0;


}

int compareFlightByPlainCode(const void * f1, const void* f2)
{
	const Flight* flight1 = (const Flight*)f1;
	const Flight* flight2 = (const Flight*)f2;
	if (flight1->thePlane.code < flight2->thePlane.code)
		return -1;
	else
		if (flight1->thePlane.code > flight2->thePlane.code)
			return 1;
		else
			return 0;
}
int compareFlightByDate(const void * f1, const void* f2)
{
	const Flight* flight1 = (const Flight*)f1;
	const Flight* flight2 = (const Flight*)f2;

	return compare_dates(&flight1->date, &flight2->date);
}