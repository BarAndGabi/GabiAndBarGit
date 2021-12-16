#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "employee.h"

int compareEmployeesBySalary(const void* e1,const void* e2)
{
	const Employee* pE1 = (const Employee*)e1;
	const Employee* pE2 = (const Employee*)e2;

	return pE1->salary - pE2->salary;
}

int compareEmployeesBySeniority(const void* e1,const void* e2)
{
	const Employee* pE1 = (const Employee*)e1;
	const Employee* pE2 = (const Employee*)e2;

	if (pE1->seniority == pE2->seniority)  
		return 0;
	else if (pE1->seniority > pE2->seniority)
		return 1;
	else
		return -1;
	
}

int compareEmployeesByName(const void* e1,const void* e2)
{
	const Employee* pE1 = (const Employee*)e1;
	const Employee* pE2 = (const Employee*)e2;

	return strcmp(pE1->name,pE2->name);
}
 
void printEmployeeArr(const Employee* arr, int size)
{
	for (int i = 0; i < size; i++)
		printEmployee(&arr[i]);
}

void printEmployee(const Employee* pEmp)
{
	printf("Name %s\t Salary %d\t Seniority %10.2f\n",
		pEmp->name, pEmp->salary, pEmp->seniority);

}
