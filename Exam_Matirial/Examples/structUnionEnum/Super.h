#ifndef __SUPER__
#define __SUPER__

#include <stdio.h>
#define S_GOOD
#ifdef S_GOOD


struct Customer;

typedef enum {eFood, eClothes,eShoes,eDrugStore, eNofTypes} ShopType;
const char* ShopTypeStr[eNofTypes];

struct Super
{
	char		name[10];
	ShopType	type;
	struct Customer* pCust;
};

typedef struct Super Super_t;

void printSuper(const Super_t* pSuper);
ShopType getShopTypeFromUser();
#else

#include "Customer.h"
typedef struct 
{
	char name[10];
	Customer pCust;
}Super;


void printSuper(const Super* pSuper);


#endif
#endif
