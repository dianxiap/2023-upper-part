#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

namespace dianxia
{
	template <class K>
	struct BSTreeNode
	{
		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}
	};

	template <class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
	public:
		//强制编译器生成构造函数
		BSTree() = default;
		//拷贝构造
		BSTree(const BSTree<K>& t)
		{
			_root = Copy(t._root);
		}
		//复制重载
		BSTree<k>& operator=(BSTree<K> t)
		{
			swap(_root, t._root);
			return *this;
		}
		~BSTree()
		{
			Destroy(_root);
		}
		//插入节点
		bool Insert(const K& key)
		{
			//直接插入根
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					returen false;
				}
			}

			cur = new Node(key);
			if (parent->_key < key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}

		bool Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else
				{
					returen true;
				}
			}
			return false;
		}
		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					//1.左为空
					if (cur->_left == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right == cur->_right;
							}
						}
						delete cur;
					}

					//2.右为空
					else if (cur->_right == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right == cur->_left;
							}
						}
						delete cur;
					}

					//3.左右都不为空，找右树最小节点或左树最大节点替代cur
					else
					{
						Node* pminRight = cur;
						Node* minRight = cur->_right;

						while (minRight->_left)
						{
							pminRight = minRight;
							minRight = minRight->_left;
						}
						cur->_key = minRight->_key;
						if (pminRight->_left == minRight)
						{
							pminRight->_left = minRight->_right;
						}
						else
						{
							pminRight->_right = minRight->_right;

						}
						delete minRight
					}
					return true;
				}
			}
			return false;
		}
		//递归版
		bool FindR(const K& key)
		{
			return _FindR(_root, key);
		}
		bool InsertR(const K& key)
		{
			return _InsertR(_root, key);
		}
		bool Erase(const K& key)
		{
			return _Erase(_root, key);
		}
		bool Insorder()
		{
			_Insorder(_root);
			cout << endl;
		}
	protected:
		Node* Copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;
			Node* newRoot = new Node(root->_key);
			newRoot->_left = Copy(root->_left);
			newRoot->_right = Copy(root->_right);
			return newRoot;
		}
		void Destroy(Node*& root)
		{
			if (root == nullptr)
				return;
			Destroy(root->_left);
			Destroy(root->_right);

			delete root;
			root = nullptr;
		}

		bool _FindR(Node* root, const K& key)
		{
			if (root == nullptr)
				return false;
			if (root->_key == key)
				return true;
			if (root->_key < key)
				return _FindR(root->_right, key);
			else 
				return _FindR(root->_left, key);
		}
		bool _InsertR(Node*& root, const K& key)
		{
			if (root == nullptr)
			{
				root = new Node(key);
				return true;
			}
			if (root->_key < key)
			{
				return _InsertR(root->_right, key);
			}
			else if (root->_key > key)
			{
				return _InsertR(root->_left, key);
			}
			else
			{
				return false;
			}
		}
		bool _EraseR(Node*& root, const K& key)
		{
			if (root == nullptr)return false;

			if (root->_key < key)
				return _EraseR(root->_right, key);
			else if(root->_key>key)
				return _EraseR(root->_left, key);
			else
			{
				Node* del = root;
				//1.右为空
				if (root->_right == nullptr)
					root = root->_left;
				//2.左为空
				else if (root->_left)
					root = root->_right;
				//3.左右都不为空
				else
				{
					//找左子树最大节点交换
					Node* maxleft = root->_left;
					while (maxleft->_right)
						maxleft = maxleft->_right;
					
					//找到后先交换要删除的值与左子树最大节点的值
					swap(root->_key, maxleft->_key);
					//再递归到左子树中去删除
					return _EraseR(root->_left, key);
				}
				delete del;

				return true;
			}
		}
	
	private:
		Node* _root;
	};
}