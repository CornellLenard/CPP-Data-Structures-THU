/*********************************************************************************

  * FileName:       splay_node.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class SplayNode
  * Project:        The Data Structures - Splay Tree Map
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <random>
#include <stack>
#include <deque>


// Defines the color of the nodes
typedef enum { RB_RED, RB_BLACK } RBColor;


template<typename K, typename V> class SplayNode
{
public:
	// Stores the key
	K key_;
	// Stores the value
	V value_;
	// Points to the node's mother
	SplayNode<K, V>* parent_;
	// Points to the node's left child
	SplayNode<K, V>* lc_;
	// Points to the node's right child
	SplayNode<K, V>* rc_;
	// The height of the node
	int height_;
	// Null path length, for leftist heaps
	int npl_;
	// Color of the node, for red black tree
	RBColor color_;

	/*
	* Judges whether the node sn is root node
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn is root node
	*/
	static bool IsRoot(const SplayNode<K, V>& sn);

	/*
	* Judges whether the node sn is left child node
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn is left child node
	*/
	static bool IsLChild(const SplayNode<K, V>& sn);

	/*
	* Judges whether the node sn is right child node
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn is right child node
	*/
	static bool IsRChild(const SplayNode<K, V>& sn);

	/*
	* Judges whether the node sn has mother node
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn has mother node
	*/
	static bool HasParent(const SplayNode<K, V>& sn);

	/*
	* Judges whether the node sn has left child node
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn has left child node
	*/
	static bool HasLChild(const SplayNode<K, V>& sn);

	/*
	* Judges whether the node sn has right child node
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn has right child node
	*/
	static bool HasRChild(const SplayNode<K, V>& sn);

	/*
	* Judges whether the node sn has child node
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn has child node
	*/
	static bool HasChild(const SplayNode<K, V>& sn);

	/*
	* Judges whether the node sn has both children nodes
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn has both children nodes
	*/
	static bool HasBothChild(const SplayNode<K, V>& sn);

	/*
	* Judges whether the node sn is leaf node
	* @ Parameter:
	*       sn:        The node
	* @ Return:
	*                  Whether the node sn is leaf node
	*/
	static bool IsLeaf(const SplayNode<K, V>& sn);

	/*
	* Gets the sibling node of the node x
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  Points to the sibling node of the node x
	*/
	static SplayNode<K, V>* GetSibling(SplayNode<K, V>* x);

	/*
	* Gets the height of the node x
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  The height of the node x
	*/
	static int GetStature(SplayNode<K, V>* x);

	SplayNode(K k, V v = static_cast<V>(0), SplayNode<K, V>* p = nullptr, SplayNode<K, V>* l = nullptr, SplayNode<K, V>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);

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
	SplayNode<K, V>* GetSucc();

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
	*       sn:        The node sn
	* @ Return:
	*                  Whether the current node < node sn
	*/
	bool operator<(const SplayNode<K, V>& sn);

	/*
	* Overloads ==
	* @ Parameter:
	*       sn:        The node sn
	* @ Return:
	*                  Whether the current node == node sn
	*/
	bool operator==(const SplayNode<K, V>& sn);

protected:
	/*
	* Goes along left branch, used in inorder traversal
	* @ Parameter:
	*       x:         The starting node
	*       s:         The stack to assist
	*/
	void GoAlongLeftBranch(SplayNode<K, V>* x, std::stack<SplayNode<K, V>*>& s);

	/*
	* Inorder traversal algorithm, iterative version 1, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI1(SplayNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, iterative version 2, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI2(SplayNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, iterative version 3, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI3(SplayNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, recursive version, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInR(SplayNode<K, V>* x, VST& visit);
};


template<typename K, typename V> bool SplayNode<K, V>::IsRoot(const SplayNode<K, V>& sn)
{
	return sn.parent_ == nullptr;
}


template<typename K, typename V> bool SplayNode<K, V>::IsLChild(const SplayNode<K, V>& sn)
{
	return (IsRoot(sn) == false) && ((sn.parent_)->lc_ == &sn);
}


template<typename K, typename V> bool SplayNode<K, V>::IsRChild(const SplayNode<K, V>& sn)
{
	return (IsRoot(sn) == false) && ((sn.parent_)->rc_ == &sn);
}


template<typename K, typename V> bool SplayNode<K, V>::HasParent(const SplayNode<K, V>& sn)
{
	return IsRoot(sn) == false;
}


template<typename K, typename V> bool SplayNode<K, V>::HasLChild(const SplayNode<K, V>& sn)
{
	return sn.lc_ != nullptr;
}


template<typename K, typename V> bool SplayNode<K, V>::HasRChild(const SplayNode<K, V>& sn)
{
	return sn.rc_ != nullptr;
}


template<typename K, typename V> bool SplayNode<K, V>::HasChild(const SplayNode<K, V>& sn)
{
	return HasLChild(sn) == true || HasRChild(sn) == true;
}


template<typename K, typename V> bool SplayNode<K, V>::HasBothChild(const SplayNode<K, V>& sn)
{
	return HasLChild(sn) == true && HasRChild(sn) == true;
}


template<typename K, typename V> bool SplayNode<K, V>::IsLeaf(const SplayNode<K, V>& sn)
{
	return HasChild(sn) == false;
}


template<typename K, typename V> SplayNode<K, V>* SplayNode<K, V>::GetSibling(SplayNode<K, V>* x)
{
	return (IsLChild(*x) == true) ? x->parent_->rc_ : x->parent_->lc_;
}


template<typename K, typename V> int SplayNode<K, V>::GetStature(SplayNode<K, V>* x)
{
	return (x != nullptr) ? x->height_ : -1;
}


template<typename K, typename V> SplayNode<K, V>::SplayNode(K k, V v, SplayNode<K, V>* p, SplayNode<K, V>* l, SplayNode<K, V>* r, int h, int n, RBColor c):
	key_(k), value_(v), parent_(p), lc_(l), rc_(r), height_(h), npl_(n), color_(c)
{
}


template<typename K, typename V> int SplayNode<K, V>::GetSize()
{
	int count = 1;
	if (lc_ != nullptr)
		count += lc_->GetSize();
	if (rc_ != nullptr)
		count += rc_->GetSize();
	return count;
}


template<typename K, typename V> SplayNode<K, V>* SplayNode<K, V>::GetSucc()
{
	SplayNode<K, V>* s = this;

	if (rc_ != nullptr)
	{
		s = rc_;
		while (SplayNode<K, V>::HasLChild(*s) == true)
			s = s->lc_;
	}
	else
	{
		while (SplayNode<K, V>::IsRChild(*s) == true)
			s = s->parent_;
		s = s->parent_;
	}

	return s;
}


template<typename K, typename V> template<typename VST> void SplayNode<K, V>::TraverseLevel(VST& visit)
{
	std::deque<SplayNode<K, V>*> q;
	q.push_back(this);
	SplayNode<K, V>* x = nullptr;

	while (q.empty() == false)
	{
		x = q.pop_front();
		visit(x->value_);

		if (SplayNode<K, V>::HasLChild(*x) == true)
			q.push_back(x->lc_);

		if (SplayNode<K, V>::HasRChild(*x) == true)
			q.push_back(x->rc_);
	}
}


template<typename K, typename V> template<typename VST> void SplayNode<K, V>::TraverseIn(VST& visit)
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


template<typename K, typename V> bool SplayNode<K, V>::operator<(const SplayNode<K, V>& sn)
{
	return key_ < sn.key_;
}


template<typename K, typename V> bool SplayNode<K, V>::operator==(const SplayNode<K, V>& sn)
{
	return key_ == sn.key_;
}


template<typename K, typename V> void SplayNode<K, V>::GoAlongLeftBranch(SplayNode<K, V>* x, std::stack<SplayNode<K, V>*>& s)
{
	while (x != nullptr)
	{
		s.push(x);
		x = x->lc_;
	}
}


template<typename K, typename V> template<typename VST> void SplayNode<K, V>::TraverseInI1(SplayNode<K, V>* x, VST& visit)
{
	std::stack<SplayNode<K, V>*> s;

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


template<typename K, typename V> template<typename VST> void SplayNode<K, V>::TraverseInI2(SplayNode<K, V>* x, VST& visit)
{
	std::stack<SplayNode<K, V>*> s;

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


template<typename K, typename V> template<typename VST> void SplayNode<K, V>::TraverseInI3(SplayNode<K, V>* x, VST& visit)
{
	bool backtrack = false;

	while (true)
	{
		if ((backtrack == false) && (SplayNode<K, V>::HasLChild(*x) == true))
			x = x->lc_;
		else
		{
			visit(x->value_);
			if (SplayNode<K, V>::HasRChild(*x) == true)
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


template<typename K, typename V> template<typename VST> void SplayNode<K, V>::TraverseInR(SplayNode<K, V>* x, VST& visit)
{
	if (x == nullptr)
		return;

	TraverseInR(x->lc_, visit);
	visit(x->value_);
	TraverseInR(x->rc_, visit);
}


