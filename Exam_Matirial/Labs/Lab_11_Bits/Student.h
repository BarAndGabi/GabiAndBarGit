#pragma once

typedef unsigned char BYTE;


typedef enum {first, second, eNofTypes} eDegreeType;
static const char* DegreeStr[eNofTypes];

typedef struct {
	char* name;
	eDegreeType	type;
	int year;
	int grade;
}Student;


int		saveStudentArrToBinaryFile(const char* fileName, const Student* arr, int size);
Student* createStudentArrFromFile(const char* fileName, int* pSize);

int		saveStudentToBinaryFileCompressed(const Student* pSt, FILE* fp);
int		readStudentFromBinaryFileCompressed(Student* pSt, FILE* fp);

void	initStudentArr(Student* arr, int size);
void	showStudentArr(const Student* arr, int size);
void	freeStudentArr(Student* arr, int size);
void	showStudent(const Student* pSt);
void	initStudent(Student* pSt);
eDegreeType getStudentTypeFromUser();
char*	createDynStr(const char* msg);
