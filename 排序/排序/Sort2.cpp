#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort2.h"

int GetMidSort(int* a, int left, int right)
{
	int mid = left + right >> 1;
	if (a[mid] > a[left])
	{
		if (a[left] > a[right])return left;
		else if (a[mid] < a[right])return mid;
		else return right;
	}
	else
	{
		if (a[left] < a[right])return left;
		else if (a[mid] > a[right])return mid;
		else return right;
	}
}

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
int PartSort1(int* a, int left, int right)
{
	int mid = GetMidSort(a, left, right);
	if (mid != left)Swap(&a[mid], &a[left]);

	int key = left;
	while (left < right)
	{
		while (left < right && a[key] <= a[right])--right;
		while (left < right && a[key] >= a[left])++left;

		Swap(&a[left], &a[right]);
	}
	Swap(&a[left], &a[key]);
	key = left;
	return key;
}
int PartSort2(int* a, int left, int right)
{
	int mid = GetMidSort(a, left, right);
	if (mid != left)Swap(&a[left], &a[mid]);

	int key = a[left];
	int hole = left;

	while (left < right)
	{
		while (left < right && key <= a[right])--right;

		a[hole] = a[right];
		hole = right;

		while (left < right && key >= a[left])++left;
		a[hole] = a[left];
		hole=left;
	}
	a[hole] = key;

	return hole;
}
int PartSort3(int* a, int left, int right)
{
	int mid = GetMidSort(a, left, right);
	if (mid != left)Swap(&a[left], &a[mid]);

	int key = left;
	int prev = left;
	int cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] < a[key] && ++prev != cur)
			Swap(&a[cur], &a[prev]);
		++cur;
	}
	Swap(&a[prev], &a[key]);
	key = prev;

	return key;
}

void QuickSort(int* a, int left, int right);

void QuickSortNonR(int* a, int left, int right)
{
	stack<int> s;
	s.push(right);
	s.push(left);

	while (s.size())
	{
		int begin = s.top();
		s.pop();
		int end = s.top();
		s.pop();

		int key = PartSort1(a, begin, end);

		if (key + 1 < end);
		{
			s.push(end);
			s.push(key + 1);
		}
		if (begin < key - 1)
		{
			s.push(key - 1);
			s.push(begin);
		}

	}
}

void _MergeSort(int* a, int begin, int end, int* tmp)
{
	if (begin >= end)return;

	int mid = begin + end >> 1;
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;

	int i = 0;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] <= a[begin2])tmp[i++] = a[begin1++];
		else tmp[i++] = a[begin2++];
	}
	while (begin1 <= end1)tmp[i++] = a[begin1++];
	while (begin2 <= end2)tmp[i++] = a[begin2++];

	memcpy(a + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	assert(tmp);
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
}

void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	assert(tmp);

	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += gap * 2)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			if (end1 >= n || begin2 >= n)break;
			if (end2 >= n)end2 = n - 1;

			int j = i;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])tmp[j++] = a[begin1++];
				else tmp[j++] = a[begin2++];
			}
			while
		}
	}
}

void CountSort(int* a, int n);
