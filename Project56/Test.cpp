#include<iostream>
#include<stack>
#include<queue>
using namespace std;

#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"


void test_stack_queue()
{
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);

	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;

	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;

	deque<int> dq;
	dq.push_back(1);
	dq.push_back(2);
	dq.push_back(3);
	dq.push_back(4);
	dq.push_back(5);
	dq.push_back(6);

	for (size_t i = 0; i < dq.size(); i++)
	{
		cout << dq[i] << " ";
	}
	cout << endl;
}

void test_op()
{
	srand(time(0));
	const int N = 1000000;
	vector<int> v1;
	vector<int> v2;
	v1.reserve(N);
	v2.reserve(N);

	deque<int> dq1;
	deque<int> dq2;


	for (int i = 0; i < N; ++i)
	{
		auto e = rand();
		//v1.push_back(e);
		//v2.push_back(e);
		dq1.push_back(e);
		dq2.push_back(e);
	}

	// 10:35继续
	// 拷贝到vector排序，排完以后再拷贝回来
	int begin1 = clock();
	// 先拷贝到vector
	for (auto e : dq1)
	{
		v1.push_back(e);
	}

	// 排序
	sort(v1.begin(), v1.end());

	// 拷贝回去
	size_t i = 0;
	for (auto& e : dq1)
	{
		e = v1[i++];
	}

	int end1 = clock();

	int begin2 = clock();
	//sort(v2.begin(), v2.end());
	sort(dq2.begin(), dq2.end());

	int end2 = clock();
	// 11:46继续
	printf("deque copy vector sort:%d\n", end1 - begin1);
	printf("deque sort:%d\n", end2 - begin2);
}

void test_priority_queue()
{
	// 默认是大堆 -- less
	//priority_queue<int> pq;

	// 仿函数控制实现小堆
	priority_queue<int, vector<int>, greater<int>> pq;

	pq.push(3);
	pq.push(5);
	pq.push(1);
	pq.push(4);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

int main()
{
	//test_stack_queue();
	//test_op();
	//test_priority_queue();


	//bit::test_stack();
	//bit::test_queue();

	// 仿函数/函数对象
	// 这个类对象可以像函数一样使用
	bit::test_priority_queue2();

	Less<int> lessfunc;
	cout << lessfunc(1, 2) << endl;
	cout << lessfunc.operator()(1, 2) << endl;

	return 0;
}