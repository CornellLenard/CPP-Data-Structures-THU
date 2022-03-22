/*********************************************************************************

  * FileName:       bin_node.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class BinNode
  * Project:        The Data Structures - Binary Tree
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <random>
#include <stack>
#include <deque>


// Defines the color of the nodes
typedef enum { RB_RED, RB_BLACK } RBColor;


template<typename T> class BinNode
{
public:
	// Stores the data
	T data_;
	// Points to the node's mother
	BinNode<T>* parent_;
	// Points to the node's left child
	BinNode<T>* lc_;
	// Points to the node's right child
	BinNode<T>* rc_;
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
	static bool IsRoot(const BinNode<T>& bn);

	/*
	* Judges whether the node bn is left child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn is left child node
	*/
	static bool IsLChild(const BinNode<T>& bn);

	/*
	* Judges whether the node bn is right child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn is right child node
	*/
	static bool IsRChild(const BinNode<T>& bn);

	/*
	* Judges whether the node bn has mother node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has mother node
	*/
	static bool HasParent(const BinNode<T>& bn);

	/*
	* Judges whether the node bn has left child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has left child node
	*/
	static bool HasLChild(const BinNode<T>& bn);

	/*
	* Judges whether the node bn has right child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has right child node
	*/
	static bool HasRChild(const BinNode<T>& bn);

	/*
	* Judges whether the node bn has child node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has child node
	*/
	static bool HasChild(const BinNode<T>& bn);

	/*
	* Judges whether the node bn has both children nodes
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn has both children nodes
	*/
	static bool HasBothChild(const BinNode<T>& bn);

	/*
	* Judges whether the node bn is leaf node
	* @ Parameter:
	*       bn:        The node
	* @ Return:
	*                  Whether the node bn is leaf node
	*/
	static bool IsLeaf(const BinNode<T>& bn);

	/*
	* Gets the sibling node of the node x
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  Points to the sibling node of the node x
	*/
	static BinNode<T>* GetSibling(BinNode<T>* x);

	/*
	* Gets the height of the node x
	* @ Parameter:
	*       x:         The node
	* @ Return:
	*                  The height of the node x
	*/
	static int GetStature(BinNode<T>* x);

	BinNode(T e = static_cast<T>(0), BinNode<T>* p = nullptr, BinNode<T>* l = nullptr, BinNode<T>* r = nullptr, int h = 0, int n = 1, RBColor c = RB_RED);

	/*
	* Gets the size of the tree whose root node is the current node
	* @ Return:
	*                  The size of the tree whose root node is the current node
	*/
	int GetSize();

	/*
	* Inserts a new node as the current nodes' left child
	* @ Parameter:
	*       e:         The node value
	* @ Return:
	*                  Points to the new node
	*/
	BinNode<T>* InsertAsLC(const T& e);

	/*
	* Inserts a new node as the current nodes' right child
	* @ Parameter:
	*       e:         The node value
	* @ Return:
	*                  Points to the new node
	*/
	BinNode<T>* InsertAsRC(const T& e);

	/*
	* Gets the successor of the current node by means of inorder traversal
	* @ Return:
	*                  Points to the successor of the current node by means of inorder traversal
	*/
	BinNode<T>* GetSucc();

	/*
	* Level order traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraverseLevel(VST& visit);

	/*
	* Preorder traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraversePre(VST& visit);

	/*
	* Inorder traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraverseIn(VST& visit);

	/*
	* Postorder traversal algorithm
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void TraversePost(VST& visit);

	/*
	* Overloads <
	* @ Parameter:
	*       bn:        The node bn
	* @ Return:
	*                  Whether the current node < node bn
	*/
	bool operator<(const BinNode<T>& bn);

	/*
	* Overloads ==
	* @ Parameter:
	*       bn:        The node bn
	* @ Return:
	*                  Whether the current node == node bn
	*/
	bool operator==(const BinNode<T>& bn);

protected:
	/*
	* Visits along left branch, used in preorder traversal
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*       s:         The stack to assist
	*/
	template<typename VST> void VisitAlongLeftBranch(BinNode<T>* x, VST& visit, std::stack<BinNode<T>*>& s);

	/*
	* Preorder traversal algorithm, iterative version, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraversePreI(BinNode<T>* x, VST& visit);

	/*
	* Preorder traversal algorithm, recursive version, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraversePreR(BinNode<T>* x, VST& visit);

	/*
	* Goes along left branch, used in inorder traversal
	* @ Parameter:
	*       x:         The starting node
	*       s:         The stack to assist
	*/
	void GoAlongLeftBranch(BinNode<T>* x, std::stack<BinNode<T>*>& s);

	/*
	* Inorder traversal algorithm, iterative version 1, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI1(BinNode<T>* x, VST& visit);

	/*
	* Inorder traversal algorithm, iterative version 2, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI2(BinNode<T>* x, VST& visit);

	/*
	* Inorder traversal algorithm, iterative version 3, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInI3(BinNode<T>* x, VST& visit);

	/*
	* Inorder traversal algorithm, recursive version, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraverseInR(BinNode<T>* x, VST& visit);

	/*
	* Goes to the HLVFL node
	* @ Parameter:
	*       s:         The stack to assist
	*/
	void GotoHLVFL(std::stack<BinNode<T>*>& s);

	/*
	* Postorder traversal algorithm, iterative version, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraversePostI(BinNode<T>* x, VST& visit);

	/*
	* Postorder traversal algorithm, recursive version, starting from node x
	* @ Parameter:
	*       x:         The starting node
	*       visit:     The function object
	*/
	template<typename VST> void TraversePostR(BinNode<T>* x, VST& visit);
};


template<typename T> bool BinNode<T>::IsRoot(const BinNode<T>& bn)
{
	return bn.parent_ == nullptr;
}


template<typename T> bool BinNode<T>::IsLChild(const BinNode<T>& bn)
{
	return (IsRoot(bn) == false) && ((bn.parent_)->lc_ == &bn);
}


template<typename T> bool BinNode<T>::IsRChild(const BinNode<T>& bn)
{
	return (IsRoot(bn) == false) && ((bn.parent_)->rc_ == &bn);
}


template<typename T> bool BinNode<T>::HasParent(const BinNode<T>& bn)
{
	return IsRoot(bn) == false;
}


template<typename T> bool BinNode<T>::HasLChild(const BinNode<T>& bn)
{
	return bn.lc_ != nullptr;
}


template<typename T> bool BinNode<T>::HasRChild(const BinNode<T>& bn)
{
	return bn.rc_ != nullptr;
}


template<typename T> bool BinNode<T>::HasChild(const BinNode<T>& bn)
{
	return HasLChild(bn) == true || HasRChild(bn) == true;
}


template<typename T> bool BinNode<T>::HasBothChild(const BinNode<T>& bn)
{
	return HasLChild(bn) == true && HasRChild(bn) == true;
}


template<typename T> bool BinNode<T>::IsLeaf(const BinNode<T>& bn)
{
	return HasChild(bn) == false;
}


template<typename T> BinNode<T>* BinNode<T>::GetSibling(BinNode<T>* x)
{
	return (IsLChild(*x) == true) ? x->parent_->rc_ : x->parent_->lc_;
}


template<typename T> int BinNode<T>::GetStature(BinNode<T>* x)
{
	return (x != nullptr) ? x->height_ : -1;
}


template<typename T> BinNode<T>::BinNode(T e, BinNode<T>* p, BinNode<T>* l, BinNode<T>* r, int h, int n, RBColor c):
	data_(e), parent_(p), lc_(l), rc_(r), height_(h), npl_(n), color_(c)
{
}


template<typename T> int BinNode<T>::GetSize()
{
	int count = 1;
	if (lc_ != nullptr)
		count += lc_->GetSize();
	if (rc_ != nullptr)
		count += rc_->GetSize();
	return count;
}


template<typename T> BinNode<T>* BinNode<T>::InsertAsLC(const T& e)
{
	return lc_ = new BinNode<T>(e, this);
}


template<typename T> BinNode<T>* BinNode<T>::InsertAsRC(const T& e)
{
	return rc_ = new BinNode<T>(e, this);
}


template<typename T> BinNode<T>* BinNode<T>::GetSucc()
{
	BinNode<T>* s = this;

	if (rc_ != nullptr)
	{
		s = rc_;
		while (BinNode<T>::HasLChild(*s) == true)
			s = s->lc_;
	}
	else
	{
		while (BinNode<T>::IsRChild(*s) == true)
			s = s->parent_;
		s = s->parent_;
	}

	return s;
}


template<typename T> template<typename VST> void BinNode<T>::TraverseLevel(VST& visit)
{
	std::deque<BinNode<T>*> q;
	q.push_back(this);
	BinNode<T>* x = nullptr;

	while (q.empty() == false)
	{
		x = q.pop_front();
		visit(x->data_);

		if (BinNode<T>::HasLChild(*x) == true)
			q.push_back(x->lc_);
		if (BinNode<T>::HasRChild(*x) == true)
			q.push_back(x->rc_);
	}
}


template<typename T> template<typename VST> void BinNode<T>::TraversePre(VST& visit)
{
	std::uniform_int_distribution<int> u(0, 1);
	std::default_random_engine e;

	switch (u(e))
	{
		case 0: TraversePreI(this, visit); break;
		case 1: TraversePreR(this, visit); break;
	}
}


template<typename T> template<typename VST> void BinNode<T>::TraverseIn(VST& visit)
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


template<typename T> template<typename VST> void BinNode<T>::TraversePost(VST& visit)
{
	std::uniform_int_distribution<int> u(0, 1);
	std::default_random_engine e;

	switch (u(e))
	{
		case 0: TraversePostI(this, visit); break;
		case 1: TraversePostR(this, visit); break;
	}
}


template<typename T> bool BinNode<T>::operator<(const BinNode<T>& bn)
{
	return data_ < bn.data_;
}


template<typename T> bool BinNode<T>::operator==(const BinNode<T>& bn)
{
	return data_ == bn.data_;
}


template<typename T> template<typename VST> void BinNode<T>::VisitAlongLeftBranch(BinNode<T>* x, VST& visit, std::stack<BinNode<T>*>& s)
{
	while (x != nullptr)
	{
		visit(x->data_);
		s.push(x->rc_);
		x = x->lc_;
	}
}


template<typename T> template<typename VST> void BinNode<T>::TraversePreI(BinNode<T>* x, VST& visit)
{
	std::stack<BinNode<T>*> s;
	while (true)
	{
		VisitAlongLeftBranch(x, visit, s);

		if (s.empty() == true)
			break;

		x = s.pop();
	}
}


template<typename T> template<typename VST> void BinNode<T>::TraversePreR(BinNode<T>* x, VST& visit)
{
	if (x == nullptr)
		return;

	visit(x->data_);
	TraversePreR(x->lc_, visit);
	TraversePreR(x->rc_, visit);
}


template<typename T> void BinNode<T>::GoAlongLeftBranch(BinNode<T>* x, std::stack<BinNode<T>*>& s)
{
	while (x != nullptr)
	{
		s.push(x);
		x = x->lc_;
	}
}


template<typename T> template<typename VST> void BinNode<T>::TraverseInI1(BinNode<T>* x, VST& visit)
{
	std::stack<BinNode<T>*> s;
	while (true)
	{
		GoAlongLeftBranch(x, s);

		if (s.empty() == true)
			break;

		x = s.top();
		s.pop();
		visit(x->data_);
		x = x->rc_;
	}
}


template<typename T> template<typename VST> void BinNode<T>::TraverseInI2(BinNode<T>* x, VST& visit)
{
	std::stack<BinNode<T>*> s;
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
			visit(x->data_);
			x = x->rc_;
		}
		else
			break;
	}
}


template<typename T> template<typename VST> void BinNode<T>::TraverseInI3(BinNode<T>* x, VST& visit)
{
	bool backtrack = false;
	while (true)
	{
		if ((backtrack == false) && (BinNode<T>::HasLChild(*x) == true))
			x = x->lc_;
		else
		{
			visit(x->data_);
			if (BinNode<T>::HasRChild(*x) == true)
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


template<typename T> template<typename VST> void BinNode<T>::TraverseInR(BinNode<T>* x, VST& visit)
{
	if (x == nullptr)
		return;

	TraverseInR(x->lc_, visit);
	visit(x->data_);
	TraverseInR(x->rc_, visit);
}


template<typename T> void BinNode<T>::GotoHLVFL(std::stack<BinNode<T>*>& s)
{
	BinNode<T>* x = nullptr;

	while ((x = s.top()) != nullptr)
	{
		if (BinNode<T>::HasLChild(*x) == true)
		{
			if (BinNode<T>::HasRChild(*x) == true)
				s.push(x->rc_);
			s.push(x->lc_);
		}
		else
			s.push(x->rc_);
	}

	s.pop();
}


template<typename T> template<typename VST> void BinNode<T>::TraversePostI(BinNode<T>* x, VST& visit)
{
	std::stack<BinNode<T>*> s;

	if (x != nullptr)
		s.push(x);

	while (s.empty() == false)
	{
		if (s.top() != x->parent_)
			GotoHLVFL(s);

		x = s.top();
		s.pop();
		visit(x->data_);
	}
}


template<typename T> template<typename VST> void BinNode<T>::TraversePostR(BinNode<T>* x, VST& visit)
{
	if (x == nullptr)
		return;

	TraversePostR(x->lc_, visit);
	TraversePostR(x->rc_, visit);
	visit(x->data_);
}


