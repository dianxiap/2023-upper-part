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
		Colour _col;  //�ڵ���ɫ

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
			//ֱ�Ӳ�����ڵ�
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
			//�ҵ��½��
			cur = new Node(kv);
			cur->_col = Red;

			//���ӽڵ�
			if (parent->_kv.first < kv.first)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}

			cur->_parent = parent;

			//����Ƿ�����������Ҫ��
			while (parent && parent->_col == Red)
			{
				//pΪ����gpһ��������Ϊ��
				Node* grandparent = parent->_parent;
				assert(grandparent);
				assert(grandparent->_col==Black);

				if (parent == grandparent->_left)
				{
					Node* uncle = grandparent->_right;
					//1.u������Ϊ�죬��ɫ���������ϸ���
					if (uncle && uncle->_col == Red)
					{
						parent->_col = uncle->_col = Black;
						grandparent->_col = Red;
						cur = grandparent;
						parent = cur->_parent;
					}
					//2.u�����ڻ�uΪ��  ��ɫ����ת
					else
					{
						if (cur == parent->_left)
						{
							//	    g
							//    p   u
							//  c
							//����
							RotateR(grandparent);
							parent->_col = Black;
							grandparent->_col = Red;
						}
						else
						{
							//		g
							//	  p	  u
							//		c
							//������������
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
					//1.u������Ϊ�죬��ɫ���������ϸ���
					if (uncle && uncle->_col == Red)
					{
						parent->_col = uncle->_col = Black;
						grandparent->_col = Red;
						cur = grandparent;
						parent = cur->_parent;
					}
					//2.u�����ڻ�uΪ��  ��ɫ����ת
					else
					{
						if (cur == parent->_right)
						{
							//	    g
							//    u   p
							//		    c
							//��
							RotateL(grandparent);
							parent->_col = Black;
							grandparent->_col = Red;
						}
						else
						{
							//		g
							//	  u	  p
							//		c
							//������������
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
		//���������1.����Ը��ڵ�Ϊ����ÿ��·����ɫ�ڵ����Ŀ�Ƿ����
		//			2.���ĳ��·�����Ƿ��������ĺ�ɫ�ڵ�
		bool Isbalance()
		{
			if (_root && _root->_col == Red)
			{
				cout << "���ڵ��Ǻ�ɫ��" << endl;
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
					cout << "ĳ��·����ɫ�ڵ�����������" << endl;
					return false;
				}
				return true;
			}
			if (root->_col == Black)
				++blacknum;
			if (root->_col == Red && root->_parent && root->_parent->_col == Red)
			{
				cout << "ĳ��·�����������ĺ�ɫ�ڵ�" << endl;
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