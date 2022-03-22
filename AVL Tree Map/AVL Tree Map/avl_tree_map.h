/*********************************************************************************

  * FileName:       avl_tree_map.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class AVLTreeMap
  * Project:        The Data Structures - AVL Tree Map
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "avl_node.h"


template<typename K, typename V> class AVLTreeMap
{
protected:
	// The size of the AVL tree
	int size_;
	// Points to the root node of the AVL tree
	AVLNode<K, V>* root_;
	// The mother node of the search-hit node
	AVLNode<K, V>* hot_;

	/*
	* Updates the height of the node x
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The new height of the node x
	*/
	int UpdateHeight(AVLNode<K, V>* x);

	/*
	* Updates the height of the node x and its ancestors
	* @ Parameter:
	*       x:         The node x
	*/
	void UpdateHeightAbove(AVLNode<K, V>* x);

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
	AVLNode<K, V>*& SearchIn(AVLNode<K, V>*& v, const K& k, AVLNode<K, V>*& hot);

	/*
	* Removes the node x
	* @ Parameter:
	*       x:         The node
	*       hot:       The mother node of the node x
	* @ Return:
	*                  Points to the new child of the node hot
	*/
	AVLNode<K, V>* RemoveAt(AVLNode<K, V>*& x, AVLNode<K, V>*& hot);

	/*
	* Removes the tree whose root node is x
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The size of the removed tree
	*/
	int RemoveForDestructor(AVLNode<K, V>* x);

	/*
	* Removes the node x and its successors
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The size of the removed nodes
	*/
	int RemoveAtForDestructor(AVLNode<K, V>* x);

	/*
	* The 3+4 reconstruction algorithm
	* @ Parameter:
	*       t0:        The tree t0
	*       t1:        The tree t1
	*       t2:        The tree t2
	*       t3:        The tree t3
	*       a:         The node a
	*       b:         The node b
	*       c:         The node c
	* @ Return:
	*                  Points to the root node of the reconstructed tree
	*/
	AVLNode<K, V>* Connect34(AVLNode<K, V>* t0, AVLNode<K, V>* t1, AVLNode<K, V>* t2, AVLNode<K, V>* t3, AVLNode<K, V>* a, AVLNode<K, V>* b, AVLNode<K, V>* c);

	/*
	* The rotation algorithm
	* @ Parameter:
	*       v:         The unbalanced node
	* @ Return:
	*                  Points to the root node of the reconstructed tree
	*/
	AVLNode<K, V>* RotateAt(AVLNode<K, V>* v);

	/*
	* Gets the pointer from the node avln's mother node that points to the node avln
	* @ Parameter:
	*       avln:      The node avln
	* @ Return:
	*                  The pointer from the node avln's mother node that points to the node avln
	*/
	AVLNode<K, V>*& FromParentTo(const AVLNode<K, V>& avln);

public:
	AVLTreeMap();
	~AVLTreeMap();

	/*
	* Gets the size of the AVL tree
	* @ Return:
	*                  The size of the AVL tree
	*/
	int GetSize() const;

	/*
	* Whether the AVL tree is empty
	* @ Return:
	*                  Whether the AVL tree is empty
	*/
	bool IsEmpty() const;

	/*
	* Gets the root node
	* @ Return:
	*                  Points to the root node
	*/
	AVLNode<K, V>* GetRoot() const;

	/*
	* AVL tree search algorithm
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  The reference of the pointer
	*/
	AVLNode<K, V>*& Search(const K& k);

	/*
	* Inserts a new node
	* @ Parameter:
	*       k:         The key
	*       v:         The value
	* @ Return:
	*                  Points to the new node
	*/
	AVLNode<K, V>* Insert(const K& k, const V& v);

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


template<typename K, typename V> int AVLTreeMap<K, V>::UpdateHeight(AVLNode<K, V>* x)
{
	int max = (AVLNode<K, V>::GetStature(x->lc_) > AVLNode<K, V>::GetStature(x->rc_) ? AVLNode<K, V>::GetStature(x->lc_) : AVLNode<K, V>::GetStature(x->rc_));
	return x->height_ = 1 + max;
}


template<typename K, typename V> void AVLTreeMap<K, V>::UpdateHeightAbove(AVLNode<K, V>* x)
{
	while (x != nullptr)
	{
		UpdateHeight(x);
		x = x->parent_;
	}
}


template<typename K, typename V> AVLNode<K, V>*& AVLTreeMap<K, V>::SearchIn(AVLNode<K, V>*& v, const K& k, AVLNode<K, V>*& hot)
{
	if (v == nullptr || v->key_ == k)
		return v;

	hot = v;

	while (true)
	{
		AVLNode<K, V>*& c = (k < hot->key_) ? hot->lc_ : hot->rc_;

		if (c == nullptr || c->key_ == k)
			return c;

		hot = c;
	}
}


template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::RemoveAt(AVLNode<K, V>*& x, AVLNode<K, V>*& hot)
{
	AVLNode<K, V>* w = x;
	AVLNode<K, V>* succ = nullptr;

	if (AVLNode<K, V>::HasLChild(*x) == false)
	{
		x = x->rc_;
		succ = x;
	}
	else if (AVLNode<K, V>::HasRChild(*x) == false)
	{
		x = x->lc_;
		succ = x;
	}
	else
	{
		w = w->GetSucc();
		x->key_ = w->key_;
		x->value_ = w->value_;
		AVLNode<K, V>* u = w->parent_;
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


template<typename K, typename V> int AVLTreeMap<K, V>::RemoveForDestructor(AVLNode<K, V>* x)
{
	FromParentTo(*x) = nullptr;
	UpdateHeightAbove(x->parent_);
	int count = RemoveAtForDestructor(x);
	size_ -= count;
	return count;
}


template<typename K, typename V> int AVLTreeMap<K, V>::RemoveAtForDestructor(AVLNode<K, V>* x)
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


template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::Connect34(AVLNode<K, V>* a, AVLNode<K, V>* b, AVLNode<K, V>* c,
	AVLNode<K, V>* t0, AVLNode<K, V>* t1, AVLNode<K, V>* t2, AVLNode<K, V>* t3)
{
	a->lc_ = t0;
	if (t0 != nullptr)
		t0->parent_ = a;

	a->rc_ = t1;
	if (t1 != nullptr)
		t1->parent_ = a;

	c->lc_ = t2;
	if (t2 != nullptr)
		t2->parent_ = c;

	c->rc_ = t3;
	if (t3 != nullptr)
		t3->parent_ = c;

	b->lc_ = a;
	a->parent_ = b;
	b->rc_ = c;
	c->parent_ = b;

	UpdateHeight(a);
	UpdateHeight(c);
	UpdateHeight(b);

	return b;
}


template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::RotateAt(AVLNode<K, V>* v)
{
	AVLNode<K, V>* p = v->parent_;
	AVLNode<K, V>* g = p->parent_;

	if (AVLNode<K, V>::IsLChild(*p) == true)
	{
		if (AVLNode<K, V>::IsLChild(*v) == true)
		{
			p->parent_ = g->parent_;
			return Connect34(v, p, g, v->lc_, v->rc_, p->rc_, g->rc_);
		}
		else
		{
			v->parent_ = g->parent_;
			return Connect34(p, v, g, p->lc_, v->lc_, v->rc_, g->rc_);
		}
	}
	else
	{
		if (AVLNode<K, V>::IsRChild(*v) == true)
		{
			p->parent_ = g->parent_;
			return Connect34(g, p, v, g->lc_, p->lc_, v->lc_, v->rc_);
		}
		else
		{
			v->parent_ = g->parent_;
			return Connect34(g, v, p, g->lc_, v->lc_, v->rc_, p->rc_);
		}
	}
}


template<typename K, typename V> AVLNode<K, V>*& AVLTreeMap<K, V>::FromParentTo(const AVLNode<K, V>& avln)
{
	return (AVLNode<K, V>::IsRoot(avln) == true) ? root_ : ((AVLNode<K, V>::IsLChild(avln) == true) ? (avln.parent_)->lc_ : (avln.parent_)->rc_);
}


template<typename K, typename V> AVLTreeMap<K, V>::AVLTreeMap()
{
	size_ = 0;
	root_ = nullptr;
	hot_ = nullptr;
}


template<typename K, typename V> AVLTreeMap<K, V>::~AVLTreeMap()
{
	if (GetSize() > 0)
		RemoveForDestructor(root_);
}


template<typename K, typename V> int AVLTreeMap<K, V>::GetSize() const
{
	return size_;
}


template<typename K, typename V> bool AVLTreeMap<K, V>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::GetRoot() const
{
	return root_;
}


template<typename K, typename V> AVLNode<K, V>*& AVLTreeMap<K, V>::Search(const K& k)
{
	return SearchIn(root_, k, hot_ = nullptr);
}


template<typename K, typename V> AVLNode<K, V>* AVLTreeMap<K, V>::Insert(const K& k, const V& v)
{
	AVLNode<K, V>*& x = Search(k);

	if (x != nullptr)
		return x;

	x = new AVLNode<K, V>(k, v, hot_);
	AVLNode<K, V>* res = x;
	size_++;

	for (AVLNode<K, V>* g = hot_; g != nullptr; g = g->parent_)
	{
		if (AVLNode<K, V>::IsAVLBalanced(*g) == false)
		{
			AVLNode<K, V>*& from_parent_to = FromParentTo(*g);
			from_parent_to = RotateAt(AVLNode<K, V>::GetHigherChild(AVLNode<K, V>::GetHigherChild(g)));
			break;
		}
		else
			UpdateHeight(g);
	}

	return res;
}


template<typename K, typename V> bool AVLTreeMap<K, V>::Remove(const K& k)
{
	AVLNode<K, V>*& x = Search(k);
	if (x == nullptr)
		return false;

	RemoveAt(x, hot_);
	size_--;

	for (AVLNode<K, V>* g = hot_; g != nullptr; g = g->parent_)
	{
		if (AVLNode<K, V>::IsAVLBalanced(*g) == false)
		{
			AVLNode<K, V>*& from_parent_to = FromParentTo(*g);
			from_parent_to = RotateAt(AVLNode<K, V>::GetHigherChild(AVLNode<K, V>::GetHigherChild(g)));
			g = from_parent_to;
		}
		UpdateHeight(g);
	}

	return true;
}


template<typename K, typename V> template<typename VST> void AVLTreeMap<K, V>::TraverseLevel(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraverseLevel(visit);
}


template<typename K, typename V> template<typename VST> void AVLTreeMap<K, V>::TraverseIn(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraverseIn(visit);
}


