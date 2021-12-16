#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <stdio.h>
#include <stdlib.h>


size_t getAsciiSum(const char* str);
size_t sum(const char* str, size_t(*getSum)(const char* str));
int* createArrayByRule(const int* arr, int size, int* newSize, int(*rule)(int));

int isOdd(int val);
int isPositive(int val);
int isDevideBy3(int val);
#endif