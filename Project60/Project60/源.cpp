#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

// 统计一个创建了多少个子类对象
class Person
{
public:
	static int count;
protected:
	string _name;
};

int Person::count = 0;

class Student : public Person
{
public:
	Student()
	{
		count++;
	}
private:
	int _stuid;
};
int main()
{
	Student s1;
	Student s2;
	Student s3;
	Student s4;
	Student s5;

	cout << Person::count << endl;
	return 0;
}
