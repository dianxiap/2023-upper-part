#pragma once
#include <assert.h>
#include <string.h>
#include <iostream>

namespace dianxia
{
	class string
	{
	public:
		//迭代器
		typedef char* iterator;
		typedef const char* const_iterator;

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
			_str = new char[s._capacity + 1];
			memcpy(_str, s._str, s._size + 1);
			_size = s._size;
			_capacity = s._capacity;
		}
		//交换
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
		//赋值运算符重载
		string& operator=(string tmp)
		{
			swap(tmp);

			return *this;
		}
		//析构
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		//底层的字符串
		const char* c_str()const
		{
			return _str;
		}
		//大小
		size_t size()const
		{
			return _size;
		}
		//容量
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		//修改容量
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

		//修改大小
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
				_str[_size] = '0';
			}
		}
		//尾插字符
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}

			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		//追加字符串
		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
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

		//插入
		void insert(size_t pos, size_t n, char ch)
		{
			assert(pos <= _size);

			if (_size + n > _capacity)
			{
				reserve(_size + n);
			}

			//end是无符号整型
			size_t end = _size;
			//end大于pos位置坐标和end不等于最大值时
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
				_str[end + len] = _str[end];
				--end;
			}
			for (size_t i = 0; i < len; i++)
			{
				_str[pos + i] = str[i];
			}
			_size += len;
		}
		//清理
		void erase(size_t pos, size_t len = npos)
		{
			assert(pos <= _size);

			if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
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
			else return npos;
		}

		string substr(size_t pos = 0, size_t len = npos)
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
			_str[0] = '\0';
			_size = 0;
		}

		bool operator<(const string& s)const
		{
			int ret = memcmp(_str, s._str, _size < s._size ? _size : s._size);

			//"hello" "hello"     false
			//"helloxx" "hello"   false
			//"hello" "helloxx"   true
			return ret == 0 ? _size < s._size : ret < 0;
		}

		bool operator==(const string& s)const
		{
			return _size == s._size && memcpy(_str, s._str, _size) == 0;
		}
		bool operator<=(const string& s)const
		{
			return *this < s || *this == s;
		}
		bool operator>(const string& s)const
		{
			return !(*this <= s);
		}
		bool operator>=(const string & s)const
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

	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}
	std::istream& operator>>(std::istream& in, string& s)
	{
		s.clear();

		//直接使用in会跳过空格与回车
		//使用in.get()可以获取空格和回车
		char ch = in.get();

		while (ch == ' ' || ch == '\n')
		{
			ch = in.get();
		}

		char buff[128];
		int i = 0;

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
	
}