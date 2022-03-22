/*********************************************************************************

  * FileName:       bst_map.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class BinarySearchTreeMap
  * Project:        The Data Structures - Binary Search Tree Map
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "bst_node.h"


template<typename K, typename V> class BinarySearchTreeMap
{
protected:
	// The size of the binary search tree
	int size_;
	// Points to the root node of the binary search tree
	BSTNode<K, V>* root_;
	// The mother node of the search-hit node
	BSTNode<K, V>* hot_;

	/*
	* Updates the height of the node x
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The new height of the node x
	*/
	int UpdateHeight(BSTNode<K, V>* x);

	/*
	* Updates the height of the node x and its ancestors
	* @ Parameter:
	*       x:         The node x
	*/
	void UpdateHeightAbove(BSTNode<K, V>* x);

	/*
	* Searches a node with key == k
	* @ Parameter:
	*       v:         The starting node
	*       k:         The key
	*       hot:       The mother node of the search-hit node
	* @ Return:
	*                  If there's a node whose key = k, returns the pointer poting to this node,
	*                  else returns the pointer pointing to the position where the node should be inserted if it is going to be inserted
	*/
	BSTNode<K, V>*& SearchIn(BSTNode<K, V>*& v, const K& k, BSTNode<K, V>*& hot);

	/*
	* Removes the node x
	* @ Parameter:
	*       x:         The node
	*       hot:       The mother node of the node x
	* @ Return:
	*                  Points to the new child of the node hot
	*/
	BSTNode<K, V>* RemoveAt(BSTNode<K, V>*& x, BSTNode<K, V>*& hot);

	/*
	* Removes the tree whose root node is x
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The size of the removed tree
	*/
	int RemoveForDestructor(BSTNode<K, V>* x);

	/*
	* Removes the node x and its successors
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The size of the removed nodes
	*/
	int RemoveAtForDestructor(BSTNode<K, V>* x);

	/*
	* Gets the pointer from the node bn's mother node that points to the node bn
	* @ Parameter:
	*       bn:        The node bn
	* @ Return:
	*                  The pointer from the node bn's mother node that points to the node bn
	*/
	BSTNode<K, V>*& FromParentTo(const BSTNode<K, V>& bn);

public:
	BinarySearchTreeMap();
	~BinarySearchTreeMap();

	/*
	* Gets the size of the binary search tree
	* @ Return:
	*                  The size of the binary search tree
	*/
	int GetSize() const;

	/*
	* Whether the binary search tree is empty
	* @ Return:
	*                  Whether the binary search tree is empty
	*/
	bool IsEmpty() const;

	/*
	* Gets the root node
	* @ Return:
	*                  Points to the root node
	*/
	BSTNode<K, V>* GetRoot() const;

	/*
	* Binary search tree search algorithm
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  The reference of the pointer
	*/
	BSTNode<K, V>*& Search(const K& k);

	/*
	* Inserts a new node
	* @ Parameter:
	*       k:         The key
	*       v:         The value
	* @ Return:
	*                  Points to the new node
	*/
	BSTNode<K, V>* Insert(const K& k, const V& v);

	/*
	* Removes the node with key == k
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  Whether removes successfully
	*/
	bool Remove(const K& k);

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
};


template<typename K, typename V> int BinarySearchTreeMap<K, V>::UpdateHeight(BSTNode<K, V>* x)
{
	int max = (BSTNode<K, V>::GetStature(x->lc_) > BSTNode<K, V>::GetStature(x->rc_) ? BSTNode<K, V>::GetStature(x->lc_) : BSTNode<K, V>::GetStature(x->rc_));
	return x->height_ = 1 + max;
}


template<typename K, typename V> void BinarySearchTreeMap<K, V>::UpdateHeightAbove(BSTNode<K, V>* x)
{
	while (x != nullptr)
	{
		UpdateHeight(x);
		x = x->parent_;
	}
}


template<typename K, typename V> BSTNode<K, V>*& BinarySearchTreeMap<K, V>::SearchIn(BSTNode<K, V>*& v, const K& k, BSTNode<K, V>*& hot)
{
	if (v == nullptr || v->key_ == k)
		return v;

	hot = v;

	while (true)
	{
		BSTNode<K, V>*& c = (k < hot->key_) ? hot->lc_ : hot->rc_;

		if (c == nullptr || c->key_ == k)
			return c;

		hot = c;
	}
}


template<typename K, typename V> BSTNode<K, V>* BinarySearchTreeMap<K, V>::RemoveAt(BSTNode<K, V>*& x, BSTNode<K, V>*& hot)
{
	BSTNode<K, V>* w = x;
	BSTNode<K, V>* succ = nullptr;

	if (BSTNode<K, V>::HasLChild(*x) == false)
	{
		x = x->rc_;
		succ = x;
	}
	else if (BSTNode<K, V>::HasRChild(*x) == false)
	{
		x = x->lc_;
		succ = x;
	}
	else
	{
		w = w->GetSucc();
		x->key_ = w->key_;
		x->value_ = w->value_;
		BSTNode<K, V>* u = w->parent_;
		succ = w->rc_;
		(u == x ? u->rc_ : u->lc_) = succ;
	}

	hot = w->parent_;

	if (succ != nullptr)
		succ->parent_ = hot;

	delete w;
	w = nullptr;
	return succ;
}


template<typename K, typename V> int BinarySearchTreeMap<K, V>::RemoveForDestructor(BSTNode<K, V>* x)
{
	FromParentTo(*x) = nullptr;
	UpdateHeightAbove(x->parent_);
	int count = RemoveAtForDestructor(x);
	size_ -= count;
	return count;
}


template<typename K, typename V> int BinarySearchTreeMap<K, V>::RemoveAtForDestructor(BSTNode<K, V>* x)
{
	if (x == nullptr)
		return 0;

	int count = 1 + RemoveAtForDestructor(x->lc_) + RemoveAtForDestructor(x->rc_);
	//release(x->data);
	//release(x);
	delete x;
	x = nullptr;
	return count;
}


template<typename K, typename V> BSTNode<K, V>*& BinarySearchTreeMap<K, V>::FromParentTo(const BSTNode<K, V>& bn)
{
	return (BSTNode<K, V>::IsRoot(bn) == true) ? root_ : ((BSTNode<K, V>::IsLChild(bn) == true) ? (bn.parent_)->lc_ : (bn.parent_)->rc_);
}


template<typename K, typename V> BinarySearchTreeMap<K, V>::BinarySearchTreeMap()
{
	size_ = 0;
	root_ = nullptr;
	hot_ = nullptr;
}


template<typename K, typename V> BinarySearchTreeMap<K, V>::~BinarySearchTreeMap()
{
	if (GetSize() > 0)
		RemoveForDestructor(root_);
}


template<typename K, typename V> int BinarySearchTreeMap<K, V>::GetSize() const
{
	return size_;
}


template<typename K, typename V> bool BinarySearchTreeMap<K, V>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename K, typename V> BSTNode<K, V>* BinarySearchTreeMap<K, V>::GetRoot() const
{
	return root_;
}


template<typename K, typename V> BSTNode<K, V>*& BinarySearchTreeMap<K, V>::Search(const K& k)
{
	return SearchIn(root_, k, hot_ = nullptr);
}


template<typename K, typename V> BSTNode<K, V>* BinarySearchTreeMap<K, V>::Insert(const K& k, const V& v)
{
	BSTNode<K, V>*& x = Search(k);

	if (x == nullptr)
	{
		x = new BSTNode<K, V>(k, v, hot_);
		size_++;
		UpdateHeightAbove(x);
	}

	return x;
}


template<typename K, typename V> bool BinarySearchTreeMap<K, V>::Remove(const K& k)
{
	BSTNode<K, V>*& x = Search(k);

	if (x == nullptr)
		return false;

	RemoveAt(x, hot_);
	size_--;
	UpdateHeightAbove(hot_);

	return true;
}


template<typename K, typename V> template<typename VST> void BinarySearchTreeMap<K, V>::TraverseLevel(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraverseLevel(visit);
}


template<typename K, typename V> template<typename VST> void BinarySearchTreeMap<K, V>::TraverseIn(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraverseIn(visit);
}


