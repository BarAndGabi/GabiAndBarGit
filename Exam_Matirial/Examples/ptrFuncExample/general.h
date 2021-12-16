#pragma once

void filter(int arr[], int size, int(*foo)(int));
int isOdd(int x);
int isPositive(int x);


void printArr(const void* arr, int size, int typeSize, void(*print)(const void*));
void swap(void* a, void* b, int typeSize);
void sort(void* arr, int size, int typeSize, int(*compare)(const void*, const void*));
