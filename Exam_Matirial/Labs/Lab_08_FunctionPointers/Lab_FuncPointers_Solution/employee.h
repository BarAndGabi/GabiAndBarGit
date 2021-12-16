#ifndef __EMPLOYEE__
#define __EMPLOYEE__

#define MAX_LENGTH 21

typedef struct
{
	char	name[MAX_LENGTH];
	int		salary;
	float	seniority;
}Employee;

int compareEmployeesBySalary(const void* pE1, const void* pE2);
int compareEmployeesBySeniority(const void* pE1, const void* pE2);
int compareEmployeesByName(const void* pE1, const void* pE2);

void printEmployeeArr(const Employee* arr, int size);
void printEmployee(const Employee* pEmp);
#endif