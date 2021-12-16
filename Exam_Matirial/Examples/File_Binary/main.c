#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"




void main()
{
	example1();
	example2();
	example3();
	example4();
	system("pause");
}

void example1()
{
	Person p1 = { "momo", 1111, 23.5F }, p2 = { "gogo", 2222, 24.8F }, p3, p4;

	FILE* f = fopen("persons.bin", "wb");
	if (!f)
		return;

	if (fwrite(&p1, sizeof(Person), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	if (fwrite(&p2, sizeof(Person), 1, f) != 1)
	{
	fclose(f);
	return;
	}

	fclose(f);

	f = fopen("persons.bin", "rb");
	if (!f)
		return;

	if (fread(&p3, sizeof(Person), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	if (fread(&p4, sizeof(Person), 1, f) != 1)
	{
		fclose(f);
		return;
	}
	fclose(f);

	printf("p3: name: %s\t id: %ld\t age: %.2f\n", p3.name, p3.id, p3.age);
	printf("p4: name: %s\t id: %ld\t age: %.2f\n", p4.name, p4.id, p4.age);

}

void example2()
{
	Person arr[] = { {"momo", 1111, 23.5F},{ "gogo", 2222, 24.8F } };
	int count = sizeof(arr) / sizeof(arr[0]);

	FILE* f = fopen("persons.bin", "wb");
	if (!f)
		return;

	if (fwrite(&count, sizeof(int),1, f) != 1)
	{
		fclose(f);
		return;
	}

	if (fwrite(arr, sizeof(Person), count, f) != count)
	{
		fclose(f);
		return;
	}

	fclose(f);

	f = fopen("persons.bin", "rb");
	if (!f)
		return;

	int size;
	if (fread(&size, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	Person* readArr = (Person*)malloc(size * sizeof(Person));
	if (!readArr)
	{
		fclose(f);
		return;
	}

	if (fread(readArr, sizeof(Person), size, f) != size)
	{
		fclose(f);
		return;
	}

	fclose(f);

	for (int i = 0; i < size; i++)
		printf("name: %s\t id: %ld\t age: %.2f\n", readArr[i].name, readArr[i].id, readArr[i].age);

	free(readArr);
}

//no write of count, calculating using ftell 
//will work since no pointers in struct
//each person of same size
void example3()
{
	Person arr[] = { {"momo", 1111, 23.5F},{ "gogo", 2222, 24.8F } };
	int count = sizeof(arr) / sizeof(arr[0]);

	FILE* f = fopen("persons.bin", "wb");
	if (!f)
		return;

	if (fwrite(arr, sizeof(Person), count, f) != count)
	{
		fclose(f);
		return;
	}

	fclose(f);

	f = fopen("persons.bin", "rb");
	if (!f)
		return;

	//calculate size of file
	fseek(f, 0, SEEK_END);
	long bytes = ftell(f);

	//calculate count of persons
	int countRead = bytes / sizeof(Person);

	Person* readArr = (Person*)malloc(countRead * sizeof(Person));
	if (!readArr)
	{
		fclose(f);
		return;
	}

	fseek(f, 0, SEEK_SET);
	//rewind(f);
	if (fread(readArr, sizeof(Person), countRead, f) != countRead)
	{
		fclose(f);
		return;
	}

	fclose(f);

	for (int i = 0; i < countRead; i++)
		printf("name: %s\t id: %ld\t age: %.2f\n", readArr[i].name, readArr[i].id, readArr[i].age);

	free(readArr);
}


void example4()
{

	Person_p pr1, pr2;
	initPerson(&pr1);

	FILE* f = fopen("persons_2.bin", "wb");
	if (!f)
		return;

	int length = strlen(pr1.name) + 1;
	if (fwrite(&length, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	if (fwrite(pr1.name, sizeof(char), length, f) != length)
	{
		fclose(f);
		return;
	}

	if (fwrite(&pr1.id, sizeof(long), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	if (fwrite(&pr1.age, sizeof(float), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	fclose(f);

	f = fopen("persons_2.bin", "rb");
	if (!f)
		return;

	int len;

	if (fread(&len, sizeof(int), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	pr2.name = (char*)malloc(len * sizeof(char));
	if (!pr2.name)
	{
		fclose(f);
		return;
	}

	if (fread(pr2.name, sizeof(char), len, f) != len)
	{
		fclose(f);
		return;
	}

	if (fread(&pr2.id, sizeof(long), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	if (fread(&pr2.age, sizeof(float), 1, f) != 1)
	{
		fclose(f);
		return;
	}

	fclose(f);

	printf("name: %s\t id: %ld\t age: %.2f\n", pr2.name,
		pr2.id, pr2.age);


	free(pr1.name);
	free(pr2.name);
}


void initPerson(Person_p* pPer)
{
	char temp[SIZE];
	printf("Enter person name\n");
	scanf("%s", temp);

	printf("enter person id and age\n");
	scanf("%ld %f", &pPer->id, &pPer->age);
	pPer->name = _strdup(temp);
}
