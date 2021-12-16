#ifndef __CUSTOMER__
#define __CUSTOMER__

#include <stdio.h>
#define C_GOOD

#ifdef C_GOOD

struct Super;

struct Customer
{
	char name[10];
	struct Super* pSup;
};

typedef struct Customer Customer_t;

void printCustomer(const Customer_t* pCust);
#else

#include "Super.h"

typedef struct 
{
	char name[10];
	Super super;
}Customer;

void printCustomer(const Customer* pCust);

#endif
#endif
