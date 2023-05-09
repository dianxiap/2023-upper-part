#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

class Date
{
public:
	//...
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	void print()
	{
		cout << _year << "Äê" << _month << "ÔÂ" << _day << "ÈÕ" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

void Test3()
{
	Date d1(2023, 4, 1);
	d1.print();
	const Date d2(2022, 3, 1);
	d2.print();
}

int main()
{
	Test3();
	return 0;
}