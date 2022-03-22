/*********************************************************************************

  * FileName:       bst_node.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class BSTNode
  * Project:        The Data Structures - Binary Search Tree Map
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <random>
#include <stack>
#include <deque>


// Defines the color of the nodes
typedef enum { RB_RED, RB_BLACK } RBColor;


template<typename K, typename V> class BSTNode
{
public:
	// Stores the key
	K key_;
	// Stores the value
	V value_;
	// Points to the node's mother
	BSTNode<K, V>* parent_; 
	// Points to the node's left child
	BSTNode<K, V>* lc_;
	// Points to the node's right child
	BSTNode<K, V>* rc_;
	// The height of the node
	int height_;
	// Null path length, for leftist heaps
	int npl_;
	// Color of the node, for red black tree
	RBColor color_;

	/*
	* Judges whether the node bn is root node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn is root node
	*/
	static bool IsRoot(const BSTNode<K, V>& bn);

	/*
	* Judges whether the node bn is left child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn is left child node
	*/
	static bool IsLChild(const BSTNode<K, V>& bn);

	/*
	* Judges whether the node bn is right child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn is right child node
	*/
	static bool IsRChild(const BSTNode<K, V>& bn);

	/*
	* Judges whether the node bn has mother node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has mother node
	*/
	static bool HasParent(const BSTNode<K, V>& bn);

	/*
	* Judges whether the node bn has left child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has left child node
	*/
	static bool HasLChild(const BSTNode<K, V>& bn);

	/*
	* Judges whether the node bn has right child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has right child node
	*/
	static bool HasRChild(const BSTNode<K, V>& bn);

	/*
	* Judges whether the node bn has child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has child node
	*/
	static bool HasChild(const BSTNode<K, V>& bn);

	/*
	* Judges whether the node bn has both children nodes
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has both children nodes
	*/
	static bool HasBothChild(const BSTNode<K, V>& bn);

	/*
	* Judges whether the node bn is leaf node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn is leaf node
	*/
	static bool IsLeaf(const BSTNode<K, V>& bn);

	/*
	* Gets the sibling node of the node x
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  Points to the sibling node of the node x
	*/
	static BSTNode<K, V>* GetSibling(BSTNode<K, V>* x);

	/*
	* Gets the height of the node x
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  The height of the node x
	*/
	static int GetStature(BSTNode<K, V>* x);

	BSTNode(K k, V v = static_cast<V>(0), BSTNode<K, V>* p = nullptr, BSTNode<K, V>* l = nullptr, BSTNode<K, V>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);

	/*
	* Gets the size of the tree whose root node is the current node
	* @ Return:
	*                  The size of the tree whose root node is the current node
	*/
	int GetSize();

	/*
	* Gets the successor of the current node by means of inorder traversal
	* @ Return:
	*                  Points to the successor of the current node by means of inorder traversal
	*/
	BSTNode<K, V>* GetSucc();

	/*
	* Level order traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraverseLevel(VST& visit);

	/*
	* Inorder traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraverseIn(VST& visit);

	/*
	* Overloads <
	* @ Parameter:
	*       bn:        The node bn
	* @ Return:
	*                  Whether the current node < node bn
	*/
	bool operator<(const BSTNode<K, V>& bn);

	/*
	* Overloads ==
	* @ Parameter:
	*       bn:        The node bn
	* @ Return:
	*                  Whether the current node == node bn
	*/
	bool operator==(const BSTNode<K, V>& bn);

protected:
	/*
	* Goes along left branch, used in inorder traversal
	* @ Parameter:
	*       x:         The starting node
	*       s:         The stack to assist
	*/
	void GoAlongLeftBranch(BSTNode<K, V>* x, std::stack<BSTNode<K, V>*>& s);

	/*
	* Inorder traversal algorithm, iterative version 1, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI1(BSTNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, iterative version 2, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI2(BSTNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, iterative version 3, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI3(BSTNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, recursive version, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInR(BSTNode<K, V>* x, VST& visit);
};


template<typename K, typename V> bool BSTNode<K, V>::IsRoot(const BSTNode<K, V>& bn)
{
	return bn.parent_ == nullptr;
}


template<typename K, typename V> bool BSTNode<K, V>::IsLChild(const BSTNode<K, V>& bn)
{
	return (IsRoot(bn) == false) && ((bn.parent_)->lc_ == &bn);
}


template<typename K, typename V> bool BSTNode<K, V>::IsRChild(const BSTNode<K, V>& bn)
{
	return (IsRoot(bn) == false) && ((bn.parent_)->rc_ == &bn);
}


template<typename K, typename V> bool BSTNode<K, V>::HasParent(const BSTNode<K, V>& bn)
{
	return IsRoot(bn) == false;
}


template<typename K, typename V> bool BSTNode<K, V>::HasLChild(const BSTNode<K, V>& bn)
{
	return bn.lc_ != nullptr;
}


template<typename K, typename V> bool BSTNode<K, V>::HasRChild(const BSTNode<K, V>& bn)
{
	return bn.rc_ != nullptr;
}


template<typename K, typename V> bool BSTNode<K, V>::HasChild(const BSTNode<K, V>& bn)
{
	return HasLChild(bn) == true || HasRChild(bn) == true;
}


template<typename K, typename V> bool BSTNode<K, V>::HasBothChild(const BSTNode<K, V>& bn)
{
	return HasLChild(bn) == true && HasRChild(bn) == true;
}


template<typename K, typename V> bool BSTNode<K, V>::IsLeaf(const BSTNode<K, V>& bn)
{
	return HasChild(bn) == false;
}


template<typename K, typename V> BSTNode<K, V>* BSTNode<K, V>::GetSibling(BSTNode<K, V>* x)
{
	return (IsLChild(*x) == true) ? x->parent_->rc_ : x->parent_->lc_;
}


template<typename K, typename V> int BSTNode<K, V>::GetStature(BSTNode<K, V>* x)
{
	return (x != nullptr) ? x->height_ : -1;
}


template<typename K, typename V> BSTNode<K, V>::BSTNode(K k, V v, BSTNode<K, V>* p, BSTNode<K, V>* l, BSTNode<K, V>* r, int h, int n, RBColor c):
	key_(k), value_(v), parent_(p), lc_(l), rc_(r), height_(h), npl_(n), color_(c)
{
}


template<typename K, typename V> int BSTNode<K, V>::GetSize()
{
	int count = 1;
	if (lc_ != nullptr)
		count += lc_->GetSize();
	if (rc_ != nullptr)
		count += rc_->GetSize();
	return count;
}


template<typename K, typename V> BSTNode<K, V>* BSTNode<K, V>::GetSucc()
{
	BSTNode<K, V>* s = this;

	if (rc_ != nullptr)
	{
		s = rc_;
		while (BSTNode<K, V>::HasLChild(*s) == true)
			s = s->lc_;
	}
	else
	{
		while (BSTNode<K, V>::IsRChild(*s) == true)
			s = s->parent_;
		s = s->parent_;
	}

	return s;
}


template<typename K, typename V> template<typename VST> void BSTNode<K, V>::TraverseLevel(VST& visit)
{
	std::deque<BSTNode<K, V>*> q;
	q.push_back(this);
	BSTNode<K, V>* x = nullptr;

	while (q.empty() == false)
	{
		x = q.pop_front();
		visit(x->value_);

		if (BSTNode<K, V>::HasLChild(*x) == true)
			q.push_back(x->lc_);

		if (BSTNode<K, V>::HasRChild(*x) == true)
			q.push_back(x->rc_);
	}
}


template<typename K, typename V> template<typename VST> void BSTNode<K, V>::TraverseIn(VST& visit)
{
	std::uniform_int_distribution<int> u(0, 3);
	std::default_random_engine e;

	switch (u(e))
	{
		case 0: TraverseInI1(this, visit); break;
		case 1: TraverseInI2(this, visit); break;
		case 2: TraverseInI3(this, visit); break;
		case 3: TraverseInR(this, visit); break;
	}
}


template<typename K, typename V> bool BSTNode<K, V>::operator<(const BSTNode<K, V>& bn)
{
	return key_ < bn.key_;
}


template<typename K, typename V> bool BSTNode<K, V>::operator==(const BSTNode<K, V>& bn)
{
	return key_ == bn.key_;
}


template<typename K, typename V> void BSTNode<K, V>::GoAlongLeftBranch(BSTNode<K, V>* x, std::stack<BSTNode<K, V>*>& s)
{
	while (x != nullptr)
	{
		s.push(x);
		x = x->lc_;
	}
}


template<typename K, typename V> template<typename VST> void BSTNode<K, V>::TraverseInI1(BSTNode<K, V>* x, VST& visit)
{
	std::stack<BSTNode<K, V>*> s;

	while (true)
	{
		GoAlongLeftBranch(x, s);

		if (s.empty() == true)
			break;

		x = s.top();
		s.pop();
		visit(x->value_);
		x = x->rc_;
	}
}


template<typename K, typename V> template<typename VST> void BSTNode<K, V>::TraverseInI2(BSTNode<K, V>* x, VST& visit)
{
	std::stack<BSTNode<K, V>*> s;

	while (true)
	{
		if (x != nullptr)
		{
			s.push(x);
			x = x->lc_;
		}
		else if (s.empty() == false)
		{
			x = s.top();
			s.pop();
			visit(x->value_);
			x = x->rc_;
		}
		else
			break;
	}
}


template<typename K, typename V> template<typename VST> void BSTNode<K, V>::TraverseInI3(BSTNode<K, V>* x, VST& visit)
{
	bool backtrack = false;

	while (true)
	{
		if ((backtrack == false) && (BSTNode<K, V>::HasLChild(*x) == true))
			x = x->lc_;
		else
		{
			visit(x->value_);
			if (BSTNode<K, V>::HasRChild(*x) == true)
			{
				x = x->rc_;
				backtrack = false;
			}
			else
			{
				x = x->GetSucc();

				if (x == nullptr)
					break;

				backtrack = true;
			}
		}
	}
}


template<typename K, typename V> template<typename VST> void BSTNode<K, V>::TraverseInR(BSTNode<K, V>* x, VST& visit)
{
	if (x == nullptr)
		return;

	TraverseInR(x->lc_, visit);
	visit(x->value_);
	TraverseInR(x->rc_, visit);
}


