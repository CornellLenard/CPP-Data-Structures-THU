/*********************************************************************************

  * FileName:       quadlist.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class QuadList
  * Project:        The Data Structures - SkipList Dictionary
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "quadlist_node.h"


template<typename K, typename V> class QuadList
{
private:
	// The size of the quadlist
	int size_;
	// Points to the header node
	QuadListNode<K, V>* header_;
	// Points to the trailer node
	QuadListNode<K, V>* trailer_;

protected:
	/*
	* Initializes the quadlist
	*/
	void Init();

	/*
	* Frees the quadlist
	* @ Return:
	*                  The number of nodes
	*/
	int Clear();

public:
	QuadList();
	~QuadList();

	/*
	* Gets the size of the quadlist
	* @ Return:
	*                  The size of the quadlist
	*/
	int GetSize() const;

	/*
	* Whether the quadlist is empty
	* @ Return:
	*                  Whether the quadlist is empty
	*/
	bool IsEmpty() const;

	/*
	* Gets the pointer that points to the first node
	* @ Return:
	*                  The pointer that points to the first node
	*/
	QuadListNode<K, V>* GetFirst() const;

	/*
	* Gets the pointer that points to the last node
	* @ Return:
	*                  The pointer that points to the last node
	*/
	QuadListNode<K, V>* GetLast() const;

	/*
	* Whether the pointer points to a valid position of the quadlist
	* @ Parameter:
	*       p:         The pointer
	* @ Return:
	*                  Whether the pointer points to a valid position of the quadlist
	*/
	bool IsValid(QuadListNode<K, V>* p) const;

	/*
	* Removes the node at position p
	* @ Parameter:
	*       p:         The position
	* @ Return:
	*                  The value stored in the removed node
	*/
	V Remove(QuadListNode<K, V>* p);

	/*
	* Inserts a new node, its pred is the node p, its below is the node b
	* @ Parameter:
	*       k:         The key
	*       v:         The value
	*       p:         The node p
	*       b:         The node b
	* @ Return:
	*                  Points to the inserted node
	*/
	QuadListNode<K, V>* InsertAfterAbove(const K& k, const V& v, QuadListNode<K, V>* p, QuadListNode<K, V>* b = nullptr);

	/*
	* Traverses the list
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void Traverse(VST& visit);
};


template<typename K, typename V> void QuadList<K, V>::Init()
{
	header_ = new QuadListNode<K, V>(static_cast<K>(0));
	trailer_ = new QuadListNode<K, V>(static_cast<K>(0));
	header_->succ_ = trailer_;
	header_->pred_ = nullptr;
	trailer_->succ_ = nullptr;
	trailer_->pred_ = header_;
	header_->above_ = nullptr;
	header_->below_ = nullptr;
	trailer_->above_ = nullptr;
	trailer_->below_ = nullptr;
	size_ = 0;
}


template<typename K, typename V> int QuadList<K, V>::Clear()
{
	int old_size = GetSize();

	while (GetSize() > 0)
		Remove(header_->succ_);

	return old_size;
}


template<typename K, typename V> QuadList<K, V>::QuadList()
{
	Init();
}


template<typename K, typename V> QuadList<K, V>::~QuadList()
{
	Clear();
	delete header_;
	header_ = nullptr;
	delete trailer_;
	trailer_ = nullptr;
}


template<typename K, typename V> int QuadList<K, V>::GetSize() const
{
	return size_;
}


template<typename K, typename V> bool QuadList<K, V>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename K, typename V> QuadListNode<K, V>* QuadList<K, V>::GetFirst() const
{
	return header_->succ_;
}


template<typename K, typename V> QuadListNode<K, V>* QuadList<K, V>::GetLast() const
{
	return trailer_->pred_;
}


template<typename K, typename V> bool QuadList<K, V>::IsValid(QuadListNode<K, V>* p) const
{
	QuadListNode<K, V>* q = header_->succ_;

	while (q != trailer_)
	{
		if (q == p)
			return true;

		q = q->succ_;
	}

	return false;
}


template<typename K, typename V> V QuadList<K, V>::Remove(QuadListNode<K, V>* p)
{
	if (IsValid(p) == false)
		return (p->entry_).value_;

	V res = (p->entry_).value_;
	p->pred_->succ_ = p->succ_;
	p->succ_->pred_ = p->pred_;

	delete p;
	p = nullptr;
	size_--;
	return res;
}


template<typename K, typename V> QuadListNode<K, V>* QuadList<K, V>::InsertAfterAbove(const K& k, const V& v, QuadListNode<K, V>* p, QuadListNode<K, V>* b)
{
	size_++;
	return p->InsertAsSuccAbove(k, v, b);
}


template<typename K, typename V> template<typename VST> void QuadList<K, V>::Traverse(VST& visit)
{
	QuadListNode<K, V>* p = header_->succ_;

	while (p != trailer_)
	{
		visit((p->entry_).value_);
		p = p->succ_;
	}
}


