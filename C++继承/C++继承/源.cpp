#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//class 子类 ：继承方式 父类

//class bass1
//{
//public: 
//	bass1()
//	{
//	};
//	int a;
//	~bass1()
//	{
//	};
//protected:
//	int b;
//private:
//	int c;
//};
//
//class son1 :public bass1
//{
//public:
//	void fun()
//	{
//		a = 10;
//		b = 5;
//	}
//};
//
//class son2 :protected bass1
//{
//public:
//	void fun()
//	{
//		a = 10;
//		b = 20;
//	}
//};
//
//
//class son3 :private bass1
//{
//public:
//	void fun()
//	{
//		a = 100;
//		b = 100;
//	}
//};
//
//class grandson3 :public son3
//{
//public:
//	void fun()
//	{
//		
//	}
//};


//class bass
//{
//public:
//	bass()
//	{
//		cout << "bass()" << endl;
//	}
//	~bass()
//	{
//		cout << "~bass()" << endl;
//	}
//};
//
//class son1 :public bass
//{
//public: 
//	son1()
//	{
//		cout << "son1()" << endl;
//	}
//	~son1()
//	{
//		cout << "~son1()" << endl;
//	}
//};
//void test1()
//{
//
//	son1 s2;
//}

//
//class bass {
//public:
//	bass()
//	{
//		a = 200;
//	}
//	~bass()
//	{
//
//	}
//	void func()
//	{
//		cout << "bass::func" << endl;
//	}
//	void func(int a)
//	{
//		cout << "bass::func" << endl;
//	}
//	int a;
//
//};
//
//class son1 :public bass
//{
//public:
//	son1()
//	{
//		a = 100;
//	}
//	void func()
//	{
//		cout << "son::func" << endl;
//	}
//
//};

//void test1()
//{
//	son1 s;
//	cout << s.a << endl;
//	cout << s.bass::a << endl;
//	s.func();
//	s.bass::func();
//	s.bass::func(10);
//}

//class bass1
//{
//public:
//	int a;
//	bass1()
//	{
//		a = 100;
//	}
//};
//
//class bass2
//{
//public:
//	int b;
//	bass2()
//	{
//		b = 200;
//	}
//};
//
//class son :public bass1, public bass2
//{
//public:
//	son()
//	{
//		c = 300;
//		d = 400;
//	}
//	int c;
//	int d;
//};
//
//void test()
//{
//	son s;
//
//}

class anmial
{
public:
	void speak()
	{

	}
};
int main()
{
	test();
	return 0;
}