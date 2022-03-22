/*********************************************************************************

  * FileName:       splay_tree_map.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class SplayTreeMap
  * Project:        The Data Structures - Splay Tree Map
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "splay_node.h"


template<typename K, typename V> class SplayTreeMap
{
protected:
	// The size of the splay tree
	int size_;
	// Points to the root node of the splay tree
	SplayNode<K, V>* root_;
	// The mother node of the search-hit node
	SplayNode<K, V>* hot_;

	/*
	* Updates the height of the node x
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The new height of the node x
	*/
	int UpdateHeight(SplayNode<K, V>* x);

	/*
	* Updates the height of the node x and its ancestors
	* @ Parameter:
	*       x:         The node x
	*/
	void UpdateHeightAbove(SplayNode<K, V>* x);

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
	SplayNode<K, V>*& SearchIn(SplayNode<K, V>*& v, const K& k, SplayNode<K, V>*& hot);

	/*
	* Removes the node x
	* @ Parameter:
	*       x:         The node
	*       hot:       The mother node of the node x
	* @ Return:
	*                  Points to the new child of the node hot
	*/
	SplayNode<K, V>* RemoveAt(SplayNode<K, V>*& x, SplayNode<K, V>*& hot);

	/*
	* Removes the tree whose root node is x
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The size of the removed tree
	*/
	int RemoveForDestructor(SplayNode<K, V>* x);

	/*
	* Removes the node x and its successors
	* @ Parameter:
	*       x:         The node x
	* @ Return:
	*                  The size of the removed nodes
	*/
	int RemoveAtForDestructor(SplayNode<K, V>* x);

	/*
	* Splay algorithm, splays the node v to the position of the root node
	* @ Parameter:
	*       v:         The node v
	* @ Return:
	*                  Points to the node v
	*/
	SplayNode<K, V>* Splay(SplayNode<K, V>* v);

	/*
	* Constructs the mother-left child relation between the node x and the node lc
	* @ Parameter:
	*       x:         The node x
	*       lc:        The node lc
	*/
	void AttachAsLChild(SplayNode<K, V>* x, SplayNode<K, V>* lc);

	/*
	* Constructs the mother-right child relation between the node x and the node rc
	* @ Parameter:
	*       x:         The node x
	*       rc:        The node lc
	*/
	void AttachAsRChild(SplayNode<K, V>* x, SplayNode<K, V>* rc);

	/*
	* Gets the pointer from the node sn's mother node that points to the node sn
	* @ Parameter:
	*       sn:        The node sn
	* @ Return:
	*                  The pointer from the node sn's mother node that points to the node sn
	*/
	SplayNode<K, V>*& FromParentTo(const SplayNode<K, V>& sn);

public:
	SplayTreeMap();
	~SplayTreeMap();

	/*
	* Gets the size of the splay tree
	* @ Return:
	*                  The size of the splay tree
	*/
	int GetSize() const;

	/*
	* Whether the splay tree is empty
	* @ Return:
	*                  Whether the splay tree is empty
	*/
	bool IsEmpty() const;

	/*
	* Gets the root node
	* @ Return:
	*                  Points to the root node
	*/
	SplayNode<K, V>* GetRoot() const;

	/*
	* Splay tree search algorithm
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  The reference of the pointer
	*/
	SplayNode<K, V>*& Search(const K& k);

	/*
	* Inserts a new node
	* @ Parameter:
	*       k:         The key
	*       v:         The value
	* @ Return:
	*                  Points to the new node
	*/
	SplayNode<K, V>* Insert(const K& k, const V& v);

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


template<typename K, typename V> int SplayTreeMap<K, V>::UpdateHeight(SplayNode<K, V>* x)
{
	int max = (SplayNode<K, V>::GetStature(x->lc_) > SplayNode<K, V>::GetStature(x->rc_) ? SplayNode<K, V>::GetStature(x->lc_) : SplayNode<K, V>::GetStature(x->rc_));
	return x->height_ = 1 + max;
}


template<typename K, typename V> void SplayTreeMap<K, V>::UpdateHeightAbove(SplayNode<K, V>* x)
{
	while (x != nullptr)
	{
		UpdateHeight(x);
		x = x->parent_;
	}
}


template<typename K, typename V> SplayNode<K, V>*& SplayTreeMap<K, V>::SearchIn(SplayNode<K, V>*& v, const K& k, SplayNode<K, V>*& hot)
{
	if (v == nullptr || v->key_ == k)
		return v;

	hot = v;

	while (true)
	{
		SplayNode<K, V>*& c = (k < hot->key_) ? hot->lc_ : hot->rc_;

		if (c == nullptr || c->key_ == k)
			return c;

		hot = c;
	}
}


template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::RemoveAt(SplayNode<K, V>*& x, SplayNode<K, V>*& hot)
{
	SplayNode<K, V>* w = x;
	SplayNode<K, V>* succ = nullptr;

	if (SplayNode<K, V>::HasLChild(*x) == false)
	{
		x = x->rc_;
		succ = x;
	}
	else if (SplayNode<K, V>::HasRChild(*x) == false)
	{
		x = x->lc_;
		succ = x;
	}
	else
	{
		w = w->GetSucc();
		x->key_ = w->key_;
		x->value_ = w->value_;
		SplayNode<K, V>* u = w->parent_;
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


template<typename K, typename V> int SplayTreeMap<K, V>::RemoveForDestructor(SplayNode<K, V>* x)
{
	FromParentTo(*x) = nullptr;
	UpdateHeightAbove(x->parent_);
	int count = RemoveAtForDestructor(x);
	size_ -= count;
	return count;
}


template<typename K, typename V> int SplayTreeMap<K, V>::RemoveAtForDestructor(SplayNode<K, V>* x)
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


template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::Splay(SplayNode<K, V>* v)
{
	if (v == nullptr)
		return nullptr;

	SplayNode<K, V>* p = nullptr;
	SplayNode<K, V>* g = nullptr;
	SplayNode<K, V>* gg = nullptr;

	while (((p = v->parent_) != nullptr) && ((g = p->parent_) != nullptr))
	{
		gg = g->parent_;

		if (SplayNode<K, V>::IsLChild(*v) == true)
		{
			if (SplayNode<K, V>::IsLChild(*p) == true)
			{
				AttachAsLChild(g, p->rc_);
				AttachAsLChild(p, v->rc_);
				AttachAsRChild(p, g);
				AttachAsRChild(v, p);
			}
			else
			{
				AttachAsLChild(p, v->rc_);
				AttachAsRChild(g, v->lc_);
				AttachAsLChild(v, g);
				AttachAsRChild(v, p);
			}
		}
		else if (SplayNode<K, V>::IsRChild(*p) == true)
		{
			AttachAsRChild(g, p->lc_);
			AttachAsRChild(p, v->lc_);
			AttachAsLChild(p, g);
			AttachAsLChild(v, p);
		}
		else
		{
			AttachAsRChild(p, v->lc_);
			AttachAsLChild(g, v->rc_);
			AttachAsRChild(v, g);
			AttachAsLChild(v, p);
		}

		if (gg == nullptr)
			v->parent_ = nullptr;
		else
			(g == gg->lc_) ? AttachAsLChild(gg, v) : AttachAsRChild(gg, v);

		UpdateHeight(g);
		UpdateHeight(p);
		UpdateHeight(v);
	}

	if ((p = v->parent_) != nullptr)
	{
		if (SplayNode<K, V>::IsLChild(*v) == true)
		{
			AttachAsLChild(p, v->rc_);
			AttachAsRChild(v, p);
		}
		else
		{
			AttachAsRChild(p, v->lc_);
			AttachAsLChild(v, p);
		}

		UpdateHeight(p);
		UpdateHeight(v);
	}

	v->parent_ = nullptr;
	return v;
}


template<typename K, typename V> void SplayTreeMap<K, V>::AttachAsLChild(SplayNode<K, V>* x, SplayNode<K, V>* lc)
{
	x->lc_ = lc;

	if (lc != nullptr)
		lc->parent_ = x;
}


template<typename K, typename V> void SplayTreeMap<K, V>::AttachAsRChild(SplayNode<K, V>* x, SplayNode<K, V>* rc)
{
	x->rc_ = rc;

	if (rc != nullptr)
		rc->parent_ = x;
}


template<typename K, typename V> SplayNode<K, V>*& SplayTreeMap<K, V>::FromParentTo(const SplayNode<K, V>& sn)
{
	return (SplayNode<K, V>::IsRoot(sn) == true) ? root_ : ((SplayNode<K, V>::IsLChild(sn) == true) ? (sn.parent_)->lc_ : (sn.parent_)->rc_);
}


template<typename K, typename V> SplayTreeMap<K, V>::SplayTreeMap()
{
	size_ = 0;
	root_ = nullptr;
	hot_ = nullptr;
}


template<typename K, typename V> SplayTreeMap<K, V>::~SplayTreeMap()
{
	if (GetSize() > 0)
		RemoveForDestructor(root_);
}


template<typename K, typename V> int SplayTreeMap<K, V>::GetSize() const
{
	return size_;
}


template<typename K, typename V> bool SplayTreeMap<K, V>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::GetRoot() const
{
	return root_;
}


template<typename K, typename V> SplayNode<K, V>*& SplayTreeMap<K, V>::Search(const K& k)
{
	SplayNode<K, V>*& x = SearchIn(root_, k, hot_ = nullptr);
	root_ = Splay((x != nullptr) ? x : hot_);
	return root_;
}


template<typename K, typename V> SplayNode<K, V>* SplayTreeMap<K, V>::Insert(const K& k, const V& v)
{
	if (root_ == nullptr)
	{
		size_++;
		return root_ = new SplayNode<K, V>(k, v);
	}

	if (Search(k)->key_ == k)
		return root_;

	SplayNode<K, V>* t = root_;

	if (root_->key_ < k)
	{
		root_ = new SplayNode<K, V>(k, v, nullptr, t, t->rc_);
		t->parent_ = root_;

		if (SplayNode<K, V>::HasRChild(*t) == true)
		{
			t->rc_->parent_ = root_;
			t->rc_ = nullptr;
		}
	}
	else
	{
		root_ = new SplayNode<K, V>(k, v, nullptr, t->lc_, t);
		t->parent_ = root_;

		if (SplayNode<K, V>::HasLChild(*t) == true)
		{
			t->lc_->parent_ = root_;
			t->lc_ = nullptr;
		}
	}

	UpdateHeightAbove(t);
	size_++;
	return root_;
}


template<typename K, typename V> bool SplayTreeMap<K, V>::Remove(const K& k)
{
	if (root_ == nullptr || Search(k)->key_ != k)
		return false;

	SplayNode<K, V>* w = root_;

	if (SplayNode<K, V>::HasLChild(*root_) == false)
	{
		root_ = root_->rc_;

		if (root_ != nullptr)
			root_->parent_ = nullptr;
	}
	else if (SplayNode<K, V>::HasRChild(*root_) == false)
	{
		root_ = root_->lc_;

		if (root_ != nullptr)
			root_->parent_ = nullptr;
	}
	else
	{
		SplayNode<K, V>* left_tree = root_->lc_;
		left_tree->parent_ = nullptr;
		root_->lc_ = nullptr;
		root_ = root_->rc_;
		root_->parent_ = nullptr;
		Search(w->key_);
		root_->lc_ = left_tree;
		left_tree->parent_ = root_;
	}

	delete w;
	w = nullptr;
	size_--;

	if (root_ != nullptr)
		UpdateHeight(root_);

	return true;
}


template<typename K, typename V> template<typename VST> void SplayTreeMap<K, V>::TraverseLevel(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraverseLevel(visit);
}


template<typename K, typename V> template<typename VST> void SplayTreeMap<K, V>::TraverseIn(VST& visit)
{
	if (GetRoot() != nullptr)
		root_->TraverseIn(visit);
}


