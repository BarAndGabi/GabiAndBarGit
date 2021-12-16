#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "questions.h"
#include "stringFunc.h"


void q1()
{
	char str1[SIZE];
	char str2[SIZE];
	int cmp;

	printf("Lets play with two strings, who is longer who is 'bigger'\n");
	printf("enter a word up to %d chars\n", (SIZE - 1));
	scanf("%s", str1);
	printf("The string is:  %s \n", str1);

	getchar(); //clear the buffer from the '\n'

	printf("enter a word up to %d chars\n", (SIZE - 1));
	fgets(str2,sizeof(str2),stdin);
	puts(str2);

	puts("longer string is:");
	if (strlen(str1) > strlen(str2))
		puts(str1);
	else
		puts(str2);

	cmp = strcmp(str1, str2);
	if (cmp == 0)
		puts("strings are equals");
	else if (cmp < 0)
		printf("%s is smaller \n", str1);
	else
		printf("%s is smaller \n", str2);
}


void q2()
{

	char str[SIZE];
	char maxWord[SIZE];

	int count;

	printf("Please enter a sentence up to %d letters, you can use capital or small letters\n"
			"Will find the word with most capital letters\n", SIZE - 1);
	myGets(str,sizeof(str));

	count = mostCapitalCountWord(str,maxWord);
	if (!count)
		printf("No capital letter word\n");
	else
		printf("The word with most capital letters is %s\n", maxWord);

}

void q3()
{
	int i;

	char strMat[N][MAX_LENGTH];
	arrOfStrings((char*)strMat, N, MAX_LENGTH);

	puts("The strings in the array are:");
	for (i = 0; i < N; i++)
		printf("%s\n",strMat[i]);
}

void q4()
{
	char str[] = "What       a beautiful    day!";

	printf("Base string is: %s \n", str);
	fixString(str);

	printf("New string is: %s \n", str);
}
