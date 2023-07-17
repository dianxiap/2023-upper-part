#pragma once
#include <iostream>
#include <assert.h>
namespace dianxia
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* constiterator;

		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		constiterator begin()const
		{
			return _start;
		}
		constiterator end()const
		{
			return _finish;
		}
		vector()
		{
		}
		vector(size_t n, const T& val = T())
		{
			resize(n, val);
		}
		vector(int n, const T& val = T())
		{
			resize(n, val);
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		vector(const vector<T>& v)
		{
			_start = new T[v.capacity()];

			for (size_t i = 0; i < v.size(); i++) 
			{
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_endofstorage = _start + v.capacity();
		}
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);

				while (_finish != _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}
		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start && pos <= _finish);

			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;

				reserve(newcapacity);
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end>=pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;

			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos <= _finish);

			iterator it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				++it;
			}
			--_finish;
			return pos;
		}
		size_t capacity()const
		{
			return _endofstorage - _start;
		}
		size_t size()const
		{
			return _finish - _start;
		}
		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void pop_back()
		{
			erase(--end());
		}
		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}
		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return _start[pos];
		}

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstorage = nullptr;
		
	};
}