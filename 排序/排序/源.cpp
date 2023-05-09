#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"

void Swap(int* p1, int* p2)
{
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}
int GetMidNumi(int* a, int left, int right)
{
	int mid = left + right >> 1;
	if (a[mid] < a[left])
	{
		if (a[left] < a[right])return left;
		else if (a[mid] > a[right])return mid;
		else return right;
	}
	else
	{
		if (a[left] > a[right])return left;
		else if (a[mid] < a[right])return mid;
		else right;
	}
}

int PartSort1(int* a, int left, int right)
{
	int mid = GetMidNumi(a, left, right);
	if (left != mid)Swap(&a[mid], &a[left]);

	int keyi = left;
	while (left < right)
	{
		while (left <= right && a[keyi] <= a[right])right--;
		while (left <= right && a[keyi] >= a[left])left++;

		Swap(&a[left], &a[right]);
	}
	Swap(&a[left], &a[keyi]);
	keyi = left;

	return keyi;

}
int PartSort2(int* a, int left, int right)
{
	int mid = GetMidNumi(a, left, right);
	if (mid != left)Swap(&a[mid], &a[left]);

	int key = a[left];
	int hole = left;

	while (left < right)
	{
		while (left <= right && key <= a[right])
			--right;
		a[hole] = a[right];
		hole = right;

		while (left <= right && key >= a[left])
			++left;
		a[hole] = a[left];
		hole = left;

	}
	a[hole] = key;
	return hole;
}
int PartSort3(int* a, int left, int right)
{
	int mid = GetMidNumi(a, left, right);
	if (mid != left)Swap(&a[left], &a[mid]);

	int keyi = left;
	
	int prev = left;
	int cur = left + 1;

	while (cur <= right)
	{
		if (a[cur] < a[keyi] && ++prev != cur)
			Swap(&a[cur], &a[prev]);
		++cur;
	}
	Swap(&a[prev], &a[keyi]);
	keyi = prev;
	return keyi;
}

void QuickSort(int* a, int left, int right)
{
	if (left >= right)return;
	int keyi = PartSort1(a, left, right);

	QuickSort(a, left, keyi - 1);
	QuickSort(a, keyi+1, right);

}

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

		int keyi = PartSort2(a, begin, end);

		if (keyi + 1 < end)
		{
			s.push(end);
			s.push(keyi + 1);
		}
		if (begin < keyi - 1)
		{
			s.push(keyi - 1);
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
	int i = begin;

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

	if (tmp == NULL)
	{
		perror("malloc fail");
		return;
	}
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
}

void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);

	if (tmp == NULL)
	{
		perror("malloc fail");
		return;
	}
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			if (end1 >= n || begin2 >= n)break;
			if (end2 >= n)end2 = n - 1;
			int j = i;

			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] <= a[begin2])tmp[j++] = a[begin1++];
				else tmp[j++] = a[begin2++];

			}
			while (begin1 <= end1)tmp[j++] = a[begin1++];
			while (begin2 <= end2)tmp[j++] = a[begin2++];

			memcpy(a + i, tmp + i, sizeof(int) * (end2 - i + 1));
		}
	}
}

void CountSort(int* a, int n)
{
	int max = a[0], min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)max = a[i];
		if (a[i] < min)min = a[i];
	}
	int range = max - min + 1;
	int* countA = (int*)malloc(sizeof(int) * range);

	assert(countA);

	memset(countA, 0, sizeof(int) * range);

	for (int i = 0; i < n; i++)
	{
		countA[a[i] - min]++;
	}
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (countA[i]--)
		{
			a[j++] = i + min;
		}
	}
	free(countA);
}