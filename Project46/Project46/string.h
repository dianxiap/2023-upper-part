#pragma once
#include <iostream>
#include <algorithm>
#include <string.h>
#include <assert.h>

using namespace std;

namespace dianxia
{
	class string
	{
		friend ostream& operator<<(ostream& out, const dianxia::string& s);
		friend istream& operator>>(istream& in, dianxia::string& s);
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const iterator begin()const
		{
			return _str;
		}
		const iterator end()const
		{
			return _str + _size;
		}
		//构造
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			memcpy(_str, str, _size + 1);
		}
		//拷贝构造
		string(const string& s)
		{
			_size = s._size;
			_capacity = s._capacity;
			_str = new char[s._capacity + 1];
			memcpy(_str, s._str, s._size + 1);
		}
		//复制重载
		void swap(string& s)
		{
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
			std::swap(_str, s._str);
		}
		string& operator=(string tmp)
		{
			swap(tmp);
			return *this;
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		const char* c_str()const
		{
			return _str;
		}
		size_t size()const
		{
			return _size;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos)const
		{
			assert(pos < _size);
			return _str[pos];

		}
		//扩容
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				memcpy(tmp, _str, _size + 1);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}
		//扩容加赋值
		void resize(size_t n, char ch = '\0')
		{
			if (n < _size)
			{
				_size = n;
				_str[_size] = '\0';
			}
			else
			{
				reserve(n);
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}

		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 4);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			
			if (len + _size > _capacity)
			{
				reserve(_size + len);
			}

			memcpy(_str + _size, str, len + 1);
			_size += len;
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		void insert(size_t pos, size_t n, char ch)
		{
			assert(pos <= _size);

			if (_size + n > _capacity)
			{
				reserve(_size + n);
			}

			size_t end = _size;
			while (end >= pos && end != npos)
			{
				_str[end + n] = _str[end];
				--end;
			}

			for (size_t i = 0; i < n; i++)
			{
				_str[pos + i] = ch;
			}
			_size += n;
		}

		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			size_t end = _size;
			while (end >= pos && end != npos)
			{
				_str[pos + len] = _str[end];
				--end;
			}
			for (size_t i = 0; i < len; i++)
			{
				_str[pos + i] = str[i];
			}
			_size += len;
		}

		void erase(size_t pos, size_t len = npos)
		{
			assert(pos <= _size);
			
			if (len == npos || pos + len >= _size)
			{
				_size = pos;
				_str[_size] = '\0';
			}
			else
			{
				size_t end = pos + len;
				while (end <= _size)
				{
					_str[pos++] = _str[end++];
				}
				_size -= len;
			}
		}
		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);

			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* str, size_t pos = 0)
		{
			assert(pos < _size);

			const char* ptr = strstr(_str + pos, str);
			if (ptr)
			{
				return ptr - _str;
			}
			else
			{
				return npos;
			}
		}
		string substr(size_t pos, size_t len = npos)
		{
			assert(pos < _size);

			size_t n = len;
			if (len == npos || pos + len > _size)
			{
				n = _size - pos;
			}

			string tmp;
			tmp.reserve(n);
			for (size_t i = pos; i < pos + n; i++)
			{
				tmp += _str[i];
			}
			return tmp;
		}
		void clear()
		{
			_str[0] = '0';
			_size = 0;
		}

		bool operator<(const string& s)const
		{
			int ret = memcmp(_str, s._str, _size < s._size ? _size : s._size);
			return ret == 0 ? _size < s._size : ret < 0;
		}
		bool operator==(const string& s)const
		{
			return _size == s._size &&
				memcpy(_str, s._str, _size) == 0;
		}
		bool operator<=(const string& s)const
		{
			return *this < s || *this == s;
		}
		bool operator>(const string& s)const
		{
			return !(*this <= s);
		}
		bool operator>=(const string& s)const
		{
			return !(*this < s);
		}
		bool operator!=(const string& s)const
		{
			return !(*this == s);
		}
	private:
		size_t _size;
		size_t _capacity;
		char* _str;
	public:
		const static size_t npos;
	};

	const size_t string::npos = -1;
	ostream& operator<<(ostream& out, const dianxia::string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}
	istream& operator>>(istream& in, dianxia::string& s)
	{
		s.clear();
		char buff[128];
		int i = 0;
		char ch = in.get();
		while (ch == ' ' || ch == '\n')
			ch = in.get();

		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == 127)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}
			ch = in.get();
		}
		if (i != 0)
		{
			buff[i] = '\0';
			s += buff;
		}
		return in;
	}
};