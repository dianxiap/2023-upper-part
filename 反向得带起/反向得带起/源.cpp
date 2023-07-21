#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

namespace dianxia
{
	template<class Iteartor,class Ref,class Ptr>
	struct ReverseIterator
	{
		typedef ReverseIterator<Iterator, Ref, Ptr> Self;
		Iterator _it;

		ReverseIterator(Iterator it)
			:it(it)
		{}
		Ref operator*()
		{
			Iterator tmp = _it;
			return *(--tmp);
		}
		Ptr operator->()
		{
			return &(operator*());
		}
		Self& operator++()
		{
			--_it;
			return *this;
		}
		Self operator--()
		{
			++_it;
			return *this;
		}
		bool operator!=(const Self& s)const
		{
			return _it != s._it;
		}
	};
}