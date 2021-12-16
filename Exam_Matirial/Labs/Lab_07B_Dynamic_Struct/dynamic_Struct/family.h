#ifndef __FAMILY_H
#define __FAMILY_H

typedef struct 
{
	char* name;
	int   numOfPeople;
} Family;

int	 initFamily(Family* theFamily);
void printFamily(const Family* theFamily);
void freeFamily(Family* theFamily);

char*	createDynStr(const char* msg);

#endif // __FAMILY_H
