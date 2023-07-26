#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

namespace key
{
	template<class K>
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

	template<class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
	public:
		BSTree() = default;

		BSTree(const BSTree<K>& t)
		{
			_root = Copy(t._root);
		}
		BSTree<K>& operator=(BSTree<K> t)
		{
			swap(_root, t._root);
			return *this;
		}
		~BSTree()
		{
			Destroy(_root);
		}
		bool Insert(const K& key)
		{
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
				else return false;
			}

			cur = new Node(key);

			if (parent->_key < key)
				parent->_right = cur;
			else
				parent->_left = cur;
			return true;	
		}
		bool Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
					cur = cur->_right;
				else if (cur->_key > key)
					cur = cur->_left;
				else return true;
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
					//1.左位空
					if (cur->_left == nullptr)
					{
						//删除跟节点
						if (cur == _root)
							_root = cur->_right;
						else
						{
							if (parent->_left == cur)
								parent->_left = cur->_right;
							else
								parent->_right = cur->_right;
						}
						delete cur;
					}

					//2.右为空
					else if (cur->_right == nullptr)
					{
						//删除跟节点
						if (cur == _root)
							_root = cur->_left;
						else
						{
							if (parent->_left == cur)
								parent->_left = cur->_left;
							else
								parent->_right = cur->_left;
						}
						delete cur;
					}

					else
					{
						// 找右树最小节点（左）替代，也可以是左树最大（右）节点替代
						Node* pminRight = cur;
						Node* minRight = cur->_right;

						while (minRight->_left)
						{
							pminRight = minRight;
							minRight = minRight->_left;
						}
						cur->_key = minRight->_key;
						if (pminRight->_left == minRight)
							pminRight->_left = minRight->_right;
						else 
							pminRight->_right = minRight->_right;
						delete minRight;
					}
					return true;
				}
			}
			return false;

		}
		bool FindR(const K& key)
		{
			return _FindR(_root, key);
		}
		bool InsertR(const K& key)
		{
			return _InsertR(_root, key);
		}
		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}
	protected:
		Node* Copy(Code* root)
		{
			if (root == nullptr)
				return nullptr;
			Node* newRoot = new Node(root->key);
			newRoot->_left = Copy(root->_left);
			newRoot->_right = Copy(root->_right);
			return newRoot;
		}
		void Destroy(Node*& root)
		{
			if (root = nullptr)
				return;
			Destroy(root->_left);
			Destroy(root->_right);

			delete root;
			root = nullptr;
		}
		bool _FindR(Node* root, const K& key)
		{
			if (root == nullptr)return false;

			if (root->_key == key)return true;
			if (root->_key < key)return _FindR(root->_right,key);
			if (root->_key > key)return _FindR(root->_left, key);
		}
		bool _InsertR(Node*& root, const K& key)
		{
			if (root == nullptr)
			{
				root = new Node(key);
				return true;
			}
			if (root->_key < key)return _InsertR(root->_right, key);
			if (root->_key > key)return _InsertR(root->_left, key);
			else return false;
		}
		bool _EraseR(Node*& root, const K& key)
		{
			if (root == nullptr)
				return false;
			if (root->_key < key)return _EraseR(root->_right, key);
			if (root->_key > key)return _InsertR(root->_left, key);
			else
			{
				Node* del = root;
				
				if (root->_right == nullptr)
					root = root->_left;
				else if(root->_left == nullptr)
					root = root->_right;
				else
				{
					Node* maxleft = root->_left;
					while (maxleft->_right)
					{
						maxleft = maxleft->_right;
					}
					swap(root->_key, maxleft->_key);
					return _EraseR(root->_left, key);
				}
				delete del;
				return true;
			}
		}
	private:
		Node* _root = nullptr;
	};
}