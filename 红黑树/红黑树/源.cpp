#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;

namespace dianxia
{
	enum Colour
	{
		Red,
		Black
	};

	template<class K,class V>
	struct RBTreeNode
	{
		RBTreeNode<K, V>* _left;
		RBTreeNode<K, V>* _right;
		RBTreeNode<K, V>* _parent;

		pair<K, V> _kv;
		Colour _col;  //节点颜色

		RBTreeNode(const pair<K, V>& kv)
			:_left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _kv(kv)
		{}
	};

	template<class K,class V>
	class RBTree
	{
		typedef RBTreeNode<K,V> Node;
	public:
		bool Insert(const pair<K, V>& kv)
		{
			//直接插入根节点
			if (_root == nullptr)
			{
				_root = new Node(kv);
				_root->_col = Black;
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;

			while(cur)
			{
				if (cur->_kv.first < kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_kv.first > kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			//找到新结点
			cur = new Node(kv);
			cur->_col = Red;

			//连接节点
			if (parent->_kv.first < kv.first)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}

			cur->_parent = parent;

			//检查是否满足红黑树的要求
			while (parent && parent->_col == Red)
			{
				//p为红则gp一定存在且为黑
				Node* grandparent = parent->_parent;
				assert(grandparent);
				assert(grandparent->_col==Black);

				if (parent == grandparent->_left)
				{
					Node* uncle = grandparent->_right;
					//1.u存在且为红，变色并继续向上更新
					if (uncle && uncle->_col == Red)
					{
						parent->_col = uncle->_col = Black;
						grandparent->_col = Red;
						cur = grandparent;
						parent = cur->_parent;
					}
					//2.u不存在或u为黑  变色加旋转
					else
					{
						if (cur == parent->_left)
						{
							//	    g
							//    p   u
							//  c
							//右旋
							RotateR(grandparent);
							parent->_col = Black;
							grandparent->_col = Red;
						}
						else
						{
							//		g
							//	  p	  u
							//		c
							//先左旋再右旋
							RotateL(parent);
							RotateR(grandparent);
							cur->_col = Black;
							grandparent->_col = Red;
						}
						break;
					}
				}
				else //grandparent->_right==parent
				{
					Node* uncle = grandparent->_left;
					//1.u存在且为红，变色并继续向上更新
					if (uncle && uncle->_col == Red)
					{
						parent->_col = uncle->_col = Black;
						grandparent->_col = Red;
						cur = grandparent;
						parent = cur->_parent;
					}
					//2.u不存在或u为黑  变色加旋转
					else
					{
						if (cur == parent->_right)
						{
							//	    g
							//    u   p
							//		    c
							//左
							RotateL(grandparent);
							parent->_col = Black;
							grandparent->_col = Red;
						}
						else
						{
							//		g
							//	  u	  p
							//		c
							//先右旋再左旋
							RotateR(parent);
							RotateL(grandparent);
							cur->_col = Black;
							grandparent->_col = Red;
						}
						break;
					}
				}
			}
			_root->_col = Black;
			return true;
		}
		~RBTree()
		{
			_Destroy(_root);
			_root = nullptr;
		}
		void Inorder()
		{
			 _InOrder(_root);
		}
		//检查红黑树：1.检查以根节点为根的每条路径黑色节点的数目是否都相等
		//			2.检查某条路径上是否有连续的红色节点
		bool Isbalance()
		{
			if (_root && _root->_col == Red)
			{
				cout << "根节点是红色的" << endl;
				return false;
			}

			int benchmark = 0;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_col == Black)
					++benchmark;
				cur = cur->_left;
			}
			return _Check(_root, 0, benchmark);
		}
		int Height()
		{
			return _Height(_root);
		}
	private:
		void _Destroy(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_Destroy(root->_left);
			_Destroy(root->_right);
			delete root;
		}

		int _Height(Node* root)
		{
			if (root == nullptr)
				return 0;
			int leftH = _Height(root->_left);
			int rightH = _Height(root->_right);
			return leftH > rightH ? leftH + 1 : rightH + 1;
		}
		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_InOrder(root->_left);
			cout << root->_kv.first << " ";
			_InOrder(root->_right);
		}
		bool _Check(Node* root, int blacknum, int benchmark)
		{
			if (root == nullptr)
			{
				if (benchmark != blacknum)
				{
					cout << "某条路径黑色节点的数量不相等" << endl;
					return false;
				}
				return true;
			}
			if (root->_col == Black)
				++blacknum;
			if (root->_col == Red && root->_parent && root->_parent->_col == Red)
			{
				cout << "某条路径存在连续的红色节点" << endl;
				return false;
			}

			return _Check(root->_left, blacknum, benchmark)
				&& _Check(root->_right, blacknum, benchmark);
		}
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
}


int main()
{
	srand(time(0));
	const size_t N = 5000000;
	dianxia::RBTree<int, int> t;
	for (size_t i = 0; i < N; ++i)
	{
		size_t x = rand() + i;
		t.Insert(make_pair(x, x));
		//cout << t.IsBalance() << endl;
	}

	t.Inorder();

	cout << t.Isbalance() << endl;
	cout << t.Height() << endl;
}