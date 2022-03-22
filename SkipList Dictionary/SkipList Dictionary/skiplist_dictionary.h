/*********************************************************************************

  * FileName:       skiplist_dictionary.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class SkipListDictionary
  * Project:        The Data Structures - SkipList Dictionary
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "dictionary.h"
#include "list.h"
#include "quadlist.h"


template<typename K, typename V> class SkipListDictionary: public Dictionary<K, V>, public List<QuadList<K, V>*>
{
protected:
	/*
	* Search algorithm of skiplist
	* @ Parameter:
	*       qlist:     the quadlist
	*       p:         The starting position
	*       k:         The key
	* @ Return:
	*                  Whether the node with key == k is found
	*/
	bool SkipSearch(ListNode<QuadList<K, V>*>*& qlist, QuadListNode<K, V>*& p, const K& k);

public:
	/*
	* Gets the size of the bottom quadlist
	* @ Return:
	*                  The size of the bottom quadlist
	*/
	int GetSize() const;

	/*
	* Gets the height of the level
	* @ Return:
	*                  The height of the level
	*/
	int GetLevel() const;

	/*
	* Inserts an entry
	* @ Parameter:
	*       k:         The key
	*       v:         The value
	* @ Return:
	*                  Whether insertion is successful
	*/
	bool Put(K k, V v);

	/*
	* Gets the value of the entry with key == k
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  The value of the entry with key == k
	*/
	V* Get(K k);

	/*
	* Removes the entry with key == k
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  Whether removal is successful
	*/
	bool Remove(K k);
};


template<typename K, typename V> bool SkipListDictionary<K, V>::SkipSearch(ListNode<QuadList<K, V>*>*& qlist, QuadListNode<K, V>*& p, const K& k)
{
	while (true)
	{
		while ((p->succ_ != nullptr) && ((p->entry_).key_ <= k))
			p = p->succ_;

		p = p->pred_;

		if ((p->pred_ != nullptr) && ((p->entry_).key_ == k))
			return true;

		qlist = qlist->succ_;

		if (qlist->succ_ == nullptr)
			return false;

		p = (p->pred_ != nullptr) ? p->below_ : qlist->data_->GetFirst();
	}
}


template<typename K, typename V> int SkipListDictionary<K, V>::GetSize() const
{
	return (this->IsEmpty() == true) ? 0 : this->GetLast()->data_->GetSize();
}


template<typename K, typename V> int SkipListDictionary<K, V>::GetLevel() const
{
	return List<QuadList<K, V>*>::GetSize();
}


template<typename K, typename V> bool SkipListDictionary<K, V>::Put(K k, V v)
{
	if (this->IsEmpty() == true)
		this->InsertAsFirst(new QuadList<K, V>());

	ListNode<QuadList<K, V>*>* qlist = this->GetFirst();
	QuadListNode<K, V>* p = qlist->data_->GetFirst();

	if (SkipSearch(qlist, p, k) == true)
		while (p->below_ != nullptr)
			p = p->below_;

	qlist = this->GetLast();
	QuadListNode<K, V>* b = qlist->data_->InsertAfterAbove(k, v, p);
	std::uniform_int_distribution<int> u(0, 1);
	std::default_random_engine e;

	while (u(e))
	{
		while ((qlist->data_->IsValid(p) == true) && (p->above_ == nullptr))
			p = p->pred_;

		if (qlist->data_->IsValid(p) == false)
		{
			if (qlist == this->GetFirst())
				this->InsertAsFirst(new QuadList<K, V>);

			p = qlist->pred_->data_->GetFirst()->pred_;
		}
		else
			p = p->above_;

		qlist = qlist->pred_;
		b = qlist->data_->InsertAfterAbove(k, v, p, b);
	}

	return true;
}


template<typename K, typename V> V* SkipListDictionary<K, V>::Get(K k)
{
	if (this->IsEmpty() == true)
		return nullptr;

	ListNode<QuadList<K, V>*>* qlist = this->GetFirst();
	QuadListNode<K, V>* p = qlist->data_->GetFirst();

	return (SkipSearch(qlist, p, k) == true) ? &((p->entry_).value_) : nullptr;
}


template<typename K, typename V> bool SkipListDictionary<K, V>::Remove(K k)
{
	if (this->IsEmpty() == true)
		return false;

	ListNode<QuadList<K, V>*>* qlist = this->GetFirst();
	QuadListNode<K, V>* p = qlist->data_->GetFirst();

	if (SkipSearch(qlist, p, k) == false)
		return false;

	do
	{
		QuadListNode<K, V>* lower = p->below_;
		qlist->data_->Remove(p);
		p = lower;
		qlist = qlist->succ_;
	} while (qlist->succ_ != nullptr);

	while ((this->IsEmpty() == false) && (this->GetFirst()->data_->IsEmpty() == true))
		List<QuadList<K, V>*>::Remove(this->GetFirst());

	return true;
}


