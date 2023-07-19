#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;

namespace dianxia
{
	template<class T>
	struct list_node
	{
		list_node<T>* _next;
		list_node<T>* _prev;
		T _val;

		list_node(const T& val = T())
			:_next(nullptr)
			,_prev(nullptr)
			,_val(val)

		{}
	};

	template<class T,class Ref,class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;
		Node* _node;

		__list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->_val;
		}

		Ptr operator->()
		{
			return &_node->_val;
		}

		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		bool operator!=(const self& it)const
		{
			return _node != it._node;
		}

		bool operator==(const self& it)const
		{
			return _node == it._node;
		}
	};

		template<class T>
		class list
		{
			typedef list_node<T> Node;
		public:
			typedef __list_iterator<T, T&, T*> iterator;
			typedef __list_iterator<T, const T&, const T*> const_iterator;
			
			iterator begin()
			{
				return iterator(_head->_next);
			}
			iterator end()
			{
				return _head;
			}
			const_iterator begin()const
			{
				return const_iterator(_head->_next);
			}
			const_iterator end()const
			{
				return _head;
			}
			void empty_init()
			{
				_head = new Node;
				_head->_prev = _head;
				_head->_next = _head;

				_size = 0;
			}
			list()
			{
				empty_init();
			}
			list(const list<T>& lt)
			{
				empty_init();

				for (auto& e : lt)
				{
					push_back(e);
				}
			}

			void swap(list<T>& lt)
			{
				std::swap(_head, lt._head);
				std::swap(_size, lt._size);
			}

			list<T>& operator=(list<T> lt)
			{
				swap(lt);
				return *this;
			}

			~list()
			{
				clear();
				delete _head;
				_head = nullptr;
			}

			void clear()
			{
				iterator lt = begin();
				while (lt != end())
				{
					lt = erase(lt);
				}
				_size = 0;
			}

			void push_back(const T& x)
			{
				insert(end(), x);
			}
			void push_front(const T& x)
			{
				insert(begin(), x);
			}

			void pop_back()
			{
				erase(--end());
			}

			void pop_front()
			{
				erase(begin());
			}

			iterator insert(iterator pos, const T& x)
			{
				Node* cur = pos._node;
				Node* prev = cur->_prev;
				Node* newnode = new Node(x);

				prev->_next = newnode;
				newnode->_prev = prev;

				cur->_prev = newnode;
				newnode->_next = cur;

				++_size;

				return newnode;
			}

			iterator erase(iterator pos)
			{
				assert(pos != end());

				Node* cur = pos._node;
				Node* prev = cur->_prev;
				Node* next = cur->_next;

				prev->_next = next;
				next->_prev = prev;

				delete cur;

				--_size;

				return next;
			}

			size_t size()
			{
				return _size;
			}
		private:
			Node* _head;
			size_t _size;
		};
	
}


int main()
{
	dianxia::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	dianxia::list<int> lt1(lt);
	for (auto e : lt1)
	{
		cout << e << " ";
	}
	cout << endl;
	dianxia::list<int> lt2;
	lt2.push_back(10);
	lt2.push_back(20);
	lt2.push_back(30);
	lt2.push_back(40);

	for (auto e : lt2)
	{
		cout << e << " ";
	}
	cout << endl;

	lt1 = lt2;

	for (auto e : lt1)
	{
		cout << e << " ";
	}
	cout << endl;
}