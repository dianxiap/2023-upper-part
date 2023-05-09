#pragma once
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stack>
#include <assert.h>

using namespace std;

int GetMidNumi(int* a, int left, int right);

int PartSort1(int* a, int left, int right);
int PartSort2(int* a, int left, int right);
int PartSort3(int* a, int left, int right);

void QuickSort(int* a, int left, int right);

void QuickSortNonR(int* a, int left, int right);

void _MergeSort(int* a, int begin, int end, int* tmp);
void MergeSort(int* a, int n);

void MergeSortNonR(int* a, int n);

void CountSort(int* a, int n);
