#pragma once
#include<iostream>
#include<string>
using namespace std;

#define N 100;

template<class K, class V>
struct BSTreeNode  //二叉搜索树
{
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;
	K _key;
	V _value;

	BSTreeNode(const K& key, const V& value)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
		, _value(value)
	{}
};

template<class K, class V>
class BSTree  //二叉搜索树
{
	typedef BSTreeNode<K, V> Node;
public:
	bool Insert(const K& key, const V& value)
	{
		if (_root == nullptr)
		{
			_root = new Node(key, value);
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
				return false;  //树里已经有与插入值一样的数，无法插入
			}
		}

		cur = new Node(key, value);
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

	Node* Find(const K& key)
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
				return cur;
			}
		}

		return nullptr;
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
				//找到了，开始删除;分为如下3种情况：
				//1.左为空    2.右为空    3.左右都不为空
				if (cur->_left == nullptr)  //左为空，父亲指向我的右，删除自己
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_right == cur)
						{
							parent->_right = cur->_right;
						}
						else
						{
							parent->_left = cur->_right;
						}
					}

					delete cur;
				}
				else if (cur->_right == nullptr)  //右为空，父亲指向我的左，删除自己
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
							parent->_right = cur->_left;
						}
					}

					delete cur;
				}
				else  //左右都不为空，不能直接删除，使用替换法
				{
					Node* rightMinParent = cur;
					Node* rightMin = cur->_right;
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}

					//替换(用右子树最小节点替换要删除的节点)
					cur->_key = rightMin->_key;

					//转换成了删除rightMin(rightMin是左为空，父亲指向它的右)
					if (rightMin == rightMinParent->_left)
					{
						rightMinParent->_left = rightMin->_right;
					}
					else
					{
						rightMinParent->_right = rightMin->_right;
					}

					delete rightMin;
				}

				return true;
			}
		}

		return false;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		else
		{
			//中序遍历
			_InOrder(root->_left);
			cout << root->_key << ":" << root->_value << endl;
			_InOrder(root->_right);
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	Node* _root = nullptr;
};

void TestBSTree()
{
	BSTree<string, string>dict;
	dict.Insert("sort", "排序");
	dict.Insert("string", "字符串");
	dict.Insert("tree", "树");
	dict.Insert("insert", "插入");

	/*string str;
	while (cin >> str)
	{
		BSTreeNode<string, string>* ret = dict.Find(str);
		if (ret)
		{
			cout << ret->_value << endl;
		}
		else
		{
			cout << "无此单词" << endl;
		}
	}*/

	string strArr[] = { "西瓜", "苹果" ,"西瓜" ,"香蕉" ,"香蕉" ,"西瓜" ,"西瓜" ,"苹果" ,"桃子" ,"苹果" ,"西瓜" ,"葡萄" };
	BSTree<string, int>countTree;
	for (auto str : strArr)
	{
		BSTreeNode<string, int>* ret = countTree.Find(str);
		if (ret == nullptr)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}

	countTree.InOrder();
}


