#pragma once
#include <iostream>
using namespace std;

enum Colour
{
	RED,
	BLACK,
};
template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _data;
	Colour _col;

	RBTreeNode(const T& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _col(RED)
	{}
};
template<class T, class Ref, class Ptr>
class __RBTreeItreator
{
	typedef RBTreeNode<T> Node;
	typedef __RBTreeIterator<T, Ref, Ptr> Self;

	Node* _node;

	__RBTreeItreator(Node* node)
		:_node(node)
	{}

	__RBTreeItreator(const __RBTreeIterator<T, T&, T*>& it)
		:_node(it._node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &_node->_data;
	}
	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}

	Self& operator++()
	{
		//1.右子树不为空，下一个是右子树的最左节点
		if (_node->_right)
		{
			Node* subLeft = _node->_right;
			while (subLeft->_left)
			{
				subLeft = subLeft->_left;
			}
			_node = subLeft;
		}
		//2.右子树为空，沿着跟的路径，找孩子是父亲左孩子的那个祖先节点
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	Self& operator--()
	{
		//1.左不为空，找左子树的最右节点
		if (_node->_left)
		{
			Node* subright = _node->_left;
			while (subright->_right)
			{
				subright = subright->_right;
			}
			_node = subright;
		}
		//2.左为空，找孩子是父亲右孩子的那个祖先节点
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}
};

template<class K, class T, class Keyoft>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	~RBTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}
public:
	typedef __RBTreeIterator<T, T&, T*> itertaor;
	typedef __RBTreeIterator<T, const T&, const T*> const_itertaor;
	iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return iterator(cur);
	}
	iterator end()
	{
		return iterator(nullptr);
	}
	const_itertaor begin()const
	{
		Node* cur = _root;
		while (cur && cur->_left)
		{
			cur = cur->_left;
		}
		return const_itertaor(cur);
	}
	const_itertaor end()const
	{
		return const_itertaor(nullptr);
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		KeyOfT kot;
		while (cur)
		{
			if (kot(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else if (kot(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return nullptr;
	}
	pair<itertaor, bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;

			return make_pair(itertaor(_root), true);
		}

		KeyOfT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(itertaor(cur), false);
			}
		}

		cur = new Node(data);
		Node* newnode = cur;
		if (kot(parent->_data) > kot(data))
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				// 情况1：u存在且为红，变色处理，并继续往上处理
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上调整
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 情况2+3：u不存在/u存在且为黑，旋转+变色
				{
					//     g
					//   p   u
					// c 
					if (cur == parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//     g
						//   p   u
						//     c
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						//parent->_col = RED;
						grandfather->_col = RED;
					}

					break;
				}
			}
			else // (grandfather->_right == parent)
			{
				//    g
				//  u   p
				//        c
				Node* uncle = grandfather->_left;
				// 情况1：u存在且为红，变色处理，并继续往上处理
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					// 继续往上调整
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 情况2+3：u不存在/u存在且为黑，旋转+变色
				{
					//    g
					//  u   p
					//        c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else
					{
						//    g
						//  u   p
						//    c
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
		}

		_root->_col = BLACK;

		return make_pair(itertaor(newnode), true);;
	}
private:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* ppnode = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (ppnode == nullptr)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = subR;
			}
			else
			{
				ppnode->_right = subR;
			}

			subR->_parent = ppnode;
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* ppnode = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = subL;
			}
			else
			{
				ppnode->_right = subL;
			}
			subL->_parent = ppnode;
		}
	}
private:
	Node* _root = nullptr;
};