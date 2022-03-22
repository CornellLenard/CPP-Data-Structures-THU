/*********************************************************************************

  * FileName:       avl_node.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class AVLNode
  * Project:        The Data Structures - AVL Tree Map
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <random>
#include <stack>
#include <deque>


// Defines the color of the nodes
typedef enum { RB_RED, RB_BLACK } RBColor;


template<typename K, typename V> class AVLNode
{
public:
	// Stores the key
	K key_;
	// Stores the value
	V value_;
	// Points to the node's mother
	AVLNode<K, V>* parent_;
	// Points to the node's left child
	AVLNode<K, V>* lc_;
	// Points to the node's right child
	AVLNode<K, V>* rc_;
	// The height of the node
	int height_;
	// Null path length, for leftist heaps
	int npl_;
	// Color of the node, for red black tree
	RBColor color_;

	/*
	* Judges whether the node avln is root node
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node bn is root node
	*/
	static bool IsRoot(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln is left child node
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln is left child node
	*/
	static bool IsLChild(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln is right child node
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln is right child node
	*/
	static bool IsRChild(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln has mother node
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln has mother node
	*/
	static bool HasParent(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln has left child node
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln has left child node
	*/
	static bool HasLChild(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln has right child node
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln has right child node
	*/
	static bool HasRChild(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln has child node
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln has child node
	*/
	static bool HasChild(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln has both children nodes
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln has both children nodes
	*/
	static bool HasBothChild(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln is leaf node
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln is leaf node
	*/
	static bool IsLeaf(const AVLNode<K, V>& avln);

	/*
	* Gets the sibling node of the node x
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  Points to the sibling node of the node x
	*/
	static AVLNode<K, V>* GetSibling(AVLNode<K, V>* x);

	/*
	* Gets the height of the node x
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  The height of the node x
	*/
	static int GetStature(AVLNode<K, V>* x);

	/*
	* Judges whether the node avln is ideally balanced
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln is ideally balanced
	*/
	static bool IsBalanced(const AVLNode<K, V>& avln);

	/*
	* Gets the balance factor of the node avln
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  The balance factor of the node avln
	*/
	static int GetBalanceFactor(const AVLNode<K, V>& avln);

	/*
	* Judges whether the node avln is AVL balanced
	* @ Parameter:
	*       avln:      The node
	* @ Return:
	*                  Whether the node avln is AVL balanced
	*/
	static bool IsAVLBalanced(const AVLNode<K, V>& avln);

	/*
	* Gets the higher child between two children, if the two children have same height, gets the one that is on the same side as mother node
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  The higher child
	*/
	static AVLNode<K, V>* GetHigherChild(AVLNode<K, V>* x);

	AVLNode(K k, V v = static_cast<V>(0), AVLNode<K, V>* p = nullptr, AVLNode<K, V>* l = nullptr, AVLNode<K, V>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);

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
	AVLNode<K, V>* GetSucc();

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
	*       avln:      The node avln
	* @ Return:
	*                  Whether the current node < node avln
	*/
	bool operator<(const AVLNode<K, V>& avln);

	/*
	* Overloads ==
	* @ Parameter:
	*       avln:      The node avln
	* @ Return:
	*                  Whether the current node == node avln
	*/
	bool operator==(const AVLNode<K, V>& avln);

protected:
	/*
	* Goes along left branch, used in inorder traversal
	* @ Parameter:
	*       x:         The starting node
	*       s:         The stack to assist
	*/
	void GoAlongLeftBranch(AVLNode<K, V>* x, std::stack<AVLNode<K, V>*>& s);

	/*
	* Inorder traversal algorithm, iterative version 1, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI1(AVLNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, iterative version 2, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI2(AVLNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, iterative version 3, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI3(AVLNode<K, V>* x, VST& visit);

	/*
	* Inorder traversal algorithm, recursive version, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInR(AVLNode<K, V>* x, VST& visit);
};


template<typename K, typename V> bool AVLNode<K, V>::IsRoot(const AVLNode<K, V>& avln)
{
	return avln.parent_ == nullptr;
}


template<typename K, typename V> bool AVLNode<K, V>::IsLChild(const AVLNode<K, V>& avln)
{
	return (IsRoot(avln) == false) && ((avln.parent_)->lc_ == &avln);
}


template<typename K, typename V> bool AVLNode<K, V>::IsRChild(const AVLNode<K, V>& avln)
{
	return (IsRoot(avln) == false) && ((avln.parent_)->rc_ == &avln);
}


template<typename K, typename V> bool AVLNode<K, V>::HasParent(const AVLNode<K, V>& avln)
{
	return IsRoot(avln) == false;
}


template<typename K, typename V> bool AVLNode<K, V>::HasLChild(const AVLNode<K, V>& avln)
{
	return avln.lc_ != nullptr;
}


template<typename K, typename V> bool AVLNode<K, V>::HasRChild(const AVLNode<K, V>& avln)
{
	return avln.rc_ != nullptr;
}


template<typename K, typename V> bool AVLNode<K, V>::HasChild(const AVLNode<K, V>& avln)
{
	return HasLChild(avln) == true || HasRChild(avln) == true;
}


template<typename K, typename V> bool AVLNode<K, V>::HasBothChild(const AVLNode<K, V>& avln)
{
	return HasLChild(avln) == true && HasRChild(avln) == true;
}


template<typename K, typename V> bool AVLNode<K, V>::IsLeaf(const AVLNode<K, V>& avln)
{
	return HasChild(avln) == false;
}


template<typename K, typename V> AVLNode<K, V>* AVLNode<K, V>::GetSibling(AVLNode<K, V>* x)
{
	return (IsLChild(*x) == true) ? x->parent_->rc_ : x->parent_->lc_;
}


template<typename K, typename V> int AVLNode<K, V>::GetStature(AVLNode<K, V>* x)
{
	return (x != nullptr) ? x->height_ : -1;
}


template<typename K, typename V> bool AVLNode<K, V>::IsBalanced(const AVLNode<K, V>& avln)
{
	return GetStature(avln.lc_) == GetStature(avln.rc_);
}


template<typename K, typename V> int AVLNode<K, V>::GetBalanceFactor(const AVLNode<K, V>& avln)
{
	return GetStature(avln.lc_) - GetStature(avln.rc_);
}


template<typename K, typename V> bool AVLNode<K, V>::IsAVLBalanced(const AVLNode<K, V>& avln)
{
	return (GetBalanceFactor(avln) >= -1) && (GetBalanceFactor(avln) <= 1);
}


template<typename K, typename V> AVLNode<K, V>* AVLNode<K, V>::GetHigherChild(AVLNode<K, V>* x)
{
	if (GetStature(x->lc_) > GetStature(x->rc_))
		return x->lc_;
	else if (GetStature(x->rc_) > GetStature(x->lc_))
		return x->rc_;
	else
		return (IsLChild(*x) == true) ? x->lc_ : x->rc_;
}


template<typename K, typename V> AVLNode<K, V>::AVLNode(K k, V v, AVLNode<K, V>* p, AVLNode<K, V>* l, AVLNode<K, V>* r, int h, int n, RBColor c):
	key_(k), value_(v), parent_(p), lc_(l), rc_(r), height_(h), npl_(n), color_(c)
{
}


template<typename K, typename V> int AVLNode<K, V>::GetSize()
{
	int count = 1;

	if (lc_ != nullptr)
		count += lc_->GetSize();

	if (rc_ != nullptr)
		count += rc_->GetSize();

	return count;
}


template<typename K, typename V> AVLNode<K, V>* AVLNode<K, V>::GetSucc()
{
	AVLNode<K, V>* s = this;

	if (rc_ != nullptr)
	{
		s = rc_;
		while (AVLNode<K, V>::HasLChild(*s) == true)
			s = s->lc_;
	}
	else
	{
		while (AVLNode<K, V>::IsRChild(*s) == true)
			s = s->parent_;
		s = s->parent_;
	}

	return s;
}


template<typename K, typename V> template<typename VST> void AVLNode<K, V>::TraverseLevel(VST& visit)
{
	std::deque<AVLNode<K, V>*> q;
	q.push_back(this);
	AVLNode<K, V>* x = nullptr;

	while (q.empty() == false)
	{
		x = q.pop_front();
		visit(x->value_);

		if (AVLNode<K, V>::HasLChild(*x) == true)
			q.push_back(x->lc_);

		if (AVLNode<K, V>::HasRChild(*x) == true)
			q.push_back(x->rc_);
	}
}


template<typename K, typename V> template<typename VST> void AVLNode<K, V>::TraverseIn(VST& visit)
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


template<typename K, typename V> bool AVLNode<K, V>::operator<(const AVLNode<K, V>& avln)
{
	return key_ < avln.key_;
}


template<typename K, typename V> bool AVLNode<K, V>::operator==(const AVLNode<K, V>& avln)
{
	return key_ == avln.key_;
}


template<typename K, typename V> void AVLNode<K, V>::GoAlongLeftBranch(AVLNode<K, V>* x, std::stack<AVLNode<K, V>*>& s)
{
	while (x != nullptr)
	{
		s.push(x);
		x = x->lc_;
	}
}


template<typename K, typename V> template<typename VST> void AVLNode<K, V>::TraverseInI1(AVLNode<K, V>* x, VST& visit)
{
	std::stack<AVLNode<K, V>*> s;

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


template<typename K, typename V> template<typename VST> void AVLNode<K, V>::TraverseInI2(AVLNode<K, V>* x, VST& visit)
{
	std::stack<AVLNode<K, V>*> s;

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


template<typename K, typename V> template<typename VST> void AVLNode<K, V>::TraverseInI3(AVLNode<K, V>* x, VST& visit)
{
	bool backtrack = false;

	while (true)
	{
		if ((backtrack == false) && (AVLNode<K, V>::HasLChild(*x) == true))
			x = x->lc_;
		else
		{
			visit(x->value_);

			if (AVLNode<K, V>::HasRChild(*x) == true)
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


template<typename K, typename V> template<typename VST> void AVLNode<K, V>::TraverseInR(AVLNode<K, V>* x, VST& visit)
{
	if (x == nullptr)
		return;

	TraverseInR(x->lc_, visit);
	visit(x->value_);
	TraverseInR(x->rc_, visit);
}


