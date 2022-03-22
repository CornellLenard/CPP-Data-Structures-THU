/*********************************************************************************

  * FileName:       list.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class List
  * Project:        The Data Structures - List
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <random>
#include "list_node.h"


template<typename T> class List
{
protected:
	// The size of the list
	int size_;
	// Points to the header node
	ListNode<T>* header_;
	// Points to the trailer node
	ListNode<T>* trailer_;

	/*
	* Initializes the list
	*/
	void Init();

	/*
	* Frees the list
	* @ Return:
	*                  The number of nodes
	*/
	int Clear();

	/*
	* Copies n nodes since position p
	* @ Parameter:
	*       p:         The position
	*       n:         How many nodes to copy
	*/
	void CopyNodes(ListNode<T>* p, int n);

	/*
	* Merge algorithm
	* @ Parameter:
	*       p:         The start position of first list segment
	*       n:         The length of first list segment
	*       lst:       The list
	*       q:         The start position of second list segment
	*       m:         The length of second list segment
	*/
	void Merge(ListNode<T>*& p, int n, List<T>& lst, ListNode<T>* q, int m);

	/*
	* Merge sort algorithm to n nodes starting from position p
	* @ Parameter:
	*       p:         The position
	*       n:         How many nodes to sort
	*/
	void MergeSort(ListNode<T>*& p, int n);

	/*
	* Selection sort algorithm to n nodes starting from position p
	* @ Parameter:
	*       p:         The position
	*       n:         How many nodes to sort
	*/
	void SelectionSort(ListNode<T>* p, int n);

	/*
	* Selects the max element from n nodes starting from position p
	* @ Parameter:
	*       p:         The position
	*       n:         The number of nodes
	* @ Return:
	*                  Points to the max element
	*/
	ListNode<T>* SelectMax(ListNode<T>* p, int n);

	/*
	* Selects the max element from the list
	* @ Return:
	*                  Points to the max element
	*/
	ListNode<T>* SelectMax();

	/*
	* Insertion sort algorithm to n nodes starting from position p
	* @ Parameter:
	*       p:         The position
	*       n:         How many nodes to sort
	*/
	void InsertionSort(ListNode<T>* p, int n);

public:
	List();
	List(const List<T>& lst);
	List(ListNode<T>* p, int n);
	~List();

	/*
	* Gets the size of the list
	* @ Return:
	*                  The size of the list
	*/
	int GetSize() const;

	/*
	* Whether the list is empty
	* @ Return:
	*                  Whether the list is empty
	*/
	bool IsEmpty() const;

	/*
	* Gets the pointer that points to the first node
	* @ Return:
	*                  The pointer that points to the first node
	*/
	ListNode<T>* GetFirst() const;

	/*
	* Gets the pointer that points to the last node
	* @ Return:
	*                  The pointer that points to the last node
	*/
	ListNode<T>* GetLast() const;

	/*
	* Whether the pointer points to a valid position of the list
	* @ Parameter:
	*       p:         The pointer
	* @ Return:
	*                  Whether the pointer points to a valid position of the list
	*/
	bool IsValid(ListNode<T>* p) const;

	/*
	* Gets the number of disordered pairs in the list
	* @ Return:
	*                  The number of disordered pairs in the list
	*/
	int Disordered() const;

	/*
	* Search algorithm in unordered list
	* @ Parameter:
	*       e:         The value that is searched
	* @ Return:
	*                  The pointer that points to the result
	*/
	ListNode<T>* Find(const T& e) const;

	/*
	* Search algorithm in p's n predecessor nodes
	* @ Parameter:
	*       e:         The value that is searched
	*       n:         The number of predecessor nodes
	*       p:         The position
	* @ Return:
	*                  The pointer that points to the result, if found, returns the rightest one, else returns nullptr
	*/
	ListNode<T>* Find(const T& e, int n, ListNode<T>* p) const;

	/*
	* Search algorithm in ordered list
	* @ Parameter:
	*       e:         The value that is searched
	* @ Return:
	*                  The pointer that points to the result
	*/
	ListNode<T>* Search(const T& e) const;

	/*
	* Search algorithm in p's n predecessor nodes
	* @ Parameter:
	*       e:         The value that is searched
	*       n:         The number of predecessor nodes
	*       p:         The position
	* @ Return:
	*                  If found, points to the element that is the first one <= e, else points to the predecessor node of the leftest node
	*/
	ListNode<T>* Search(const T& e, int n, ListNode<T>* p) const;

	/*
	* Inserts an element as first node
	* @ Parameter:
	*       e:         The value of the inserted element
	* @ Return:
	*                  Points to the new node
	*/
	ListNode<T>* InsertAsFirst(const T& e);

	/*
	* Inserts an element as last node
	* @ Parameter:
	*       e:         The value of the inserted element
	* @ Return:
	*                  Points to the new node
	*/
	ListNode<T>* InsertAsLast(const T& e);

	/*
	* Inserts an element after position p
	* @ Parameter:
	*       p:         The position
	*       e:         The value of the inserted element
	* @ Return:
	*                  Points to the new node
	*/
	ListNode<T>* InsertAfter(ListNode<T>* p, const T& e);

	/*
	* Inserts an element before position p
	* @ Parameter:
	*       p:         The position
	*       e:         The value of the inserted element
	* @ Return:
	*                  Points to the new node
	*/
	ListNode<T>* InsertBefore(ListNode<T>* p, const T& e);

	/*
	* Removes the node at position p
	* @ Parameter:
	*       p:         The position
	* @ Return:
	*                  The data stored in the removed node
	*/
	T Remove(ListNode<T>* p);

	/*
	* Removes all the nodes whose data == e
	* @ Parameter:
	*       e:         The value
	* @ Return:
	*                  The number of removed nodes
	*/
	int Remove(const T& e);

	/*
	* Merge algorithm to the whole list
	* @ Parameter:
	*       lst:       The list
	*/
	void Merge(List<T>& lst);

	/*
	* Sorts the list
	*/
	void Sort();

	/*
	* Deduplicates the unordered list
	* @ Return:
	*                  The number of removed nodes
	*/
	int Deduplicate();

	/*
	* Uniquifies the ordered list
	* @ Return:
	*                  The number of removed nodes
	*/
	int Uniquify();

	/*
	* Reverses the list
	*/
	void Reverse();

	/*
	* Traverses the list
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void Traverse(VST& visit);
};


template<typename T> void List<T>::Init()
{
	header_ = new ListNode<T>();
	trailer_ = new ListNode<T>();
	header_->succ_ = trailer_;
	header_->pred_ = nullptr;
	trailer_->succ_ = nullptr;
	trailer_->pred_ = header_;
	size_ = 0;
}


template<typename T> int List<T>::Clear()
{
	int old_size = GetSize();

	while (GetSize() > 0)
		Remove(header_->succ_);

	return old_size;
}


template<typename T> void List<T>::CopyNodes(ListNode<T>* p, int n)
{
	Init();

	while (n > 0)
	{
		InsertAsLast(p->data);
		p = p->succ_;
		n--;
	}
}


template<typename T> void List<T>::Merge(ListNode<T>*& p, int n, List<T>& lst, ListNode<T>* q, int m)
{
	ListNode<T>* pp = p->pred_;

	while (m > 0)
	{
		if ((n > 0) && (p->data_ <= q->data_))
		{
			p = p->succ_;

			if (p == q)
				break;

			n--;
		}
		else
		{
			InsertBefore(p, lst.Remove((q = q->succ_)->pred_));
			m--;
		}
	}

	p = pp->succ_;
}


template<typename T> void List<T>::MergeSort(ListNode<T>*& p, int n)
{
	if (n <= 1)
		return;

	int m = n / 2;
	ListNode<T>* q = p;

	for (int i = 0; i < m; i++)
		q = q->succ_;

	MergeSort(p, m);
	MergeSort(q, n - m);
	Merge(p, m, *this, q, n - m);
}


template<typename T> void List<T>::SelectionSort(ListNode<T>* p, int n)
{
	ListNode<T>* head = p->pred_;
	ListNode<T>* tail = p;

	for (int i = 0; i < n; i++)
		tail = tail->succ_;

	ListNode<T>* max = nullptr;

	while (n > 1)
	{
		max = SelectMax(head->succ_, n);
		InsertBefore(tail, Remove(max));
		tail = tail->pred_;
		n--;
	}
}


template<typename T> ListNode<T>* List<T>::SelectMax(ListNode<T>* p, int n)
{
	ListNode<T>* max = p;
	ListNode<T>* q = max->succ_;

	while (n > 1)
	{
		if (q->data_ >= max->data_)
			max = q;

		q = q->succ_;
		n--;
	}

	return max;
}


template<typename T> ListNode<T>* List<T>::SelectMax()
{
	return SelectMax(header_->succ_, GetSize());
}


template<typename T> void List<T>::InsertionSort(ListNode<T>* p, int n)
{
	for (int i = 0; i < n; i++)
	{
		InsertAfter(Search(p->data_, i, p), p->data_);
		p = p->succ_;
		Remove(p->pred_);
	}
}


template<typename T> List<T>::List()
{
	Init();
}


template<typename T> List<T>::List(ListNode<T>* p, int n)
{
	CopyNodes(p, n);
}


template<typename T> List<T>::List(const List<T>& lst)
{
	CopyNodes((lst.header_)->succ_, lst.size_);
}


template<typename T> List<T>::~List()
{
	Clear();
	delete header_;
	header_ = nullptr;
	delete trailer_;
	trailer_ = nullptr;
}


template<typename T> int List<T>::GetSize() const
{
	return size_;
}


template<typename T> bool List<T>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename T> ListNode<T>* List<T>::GetFirst() const
{
	return header_->succ_;
}


template<typename T> ListNode<T>* List<T>::GetLast() const
{
	return trailer_->pred_;
}


template<typename T> bool List<T>::IsValid(ListNode<T>* p) const
{
	ListNode<T>* q = header_->succ_;

	while (q != trailer_)
	{
		if (q == p)
			return true;
		q = q->succ_;
	}

	return false;
}


template<typename T> int List<T>::Disordered() const
{
	ListNode<T>* p = GetFirst()->succ_;
	int count = 0;

	while (p != trailer_)
	{
		if (p->pred_->data_ > p->data_)
			count++;

		p = p->succ_;
	}

	return count;
}


template<typename T> ListNode<T>* List<T>::Find(const T& e) const
{
	return Find(e, GetSize(), trailer_);
}


template<typename T> ListNode<T>* List<T>::Find(const T& e, int n, ListNode<T>* p) const
{
	while (n > 0)
	{
		p = p->pred_;

		if (p->data_ == e)
			return p;

		n--;
	}
	return nullptr;
}


template<typename T> ListNode<T>* List<T>::Search(const T& e) const
{
	return Search(e, GetSize(), trailer_);
}


template<typename T> ListNode<T>* List<T>::Search(const T& e, int n, ListNode<T>* p) const
{
	while (n >= 0)
	{
		p = p->pred_;

		if ((p->data_) <= e)
			break;

		n--;
	}
	return p;
}


template<typename T> ListNode<T>* List<T>::InsertAsFirst(const T& e)
{
	size_++;
	return header_->InsertAsSucc(e);
}


template<typename T> ListNode<T>* List<T>::InsertAsLast(const T& e)
{
	size_++;
	return trailer_->InsertAsPred(e);
}


template<typename T> ListNode<T>* List<T>::InsertAfter(ListNode<T>* p, const T& e)
{
	size_++;
	return p->InsertAsSucc(e);
}


template<typename T> ListNode<T>* List<T>::InsertBefore(ListNode<T>* p, const T& e)
{
	size_++;
	return p->InsertAsPred(e);
}


template<typename T> T List<T>::Remove(ListNode<T>* p)
{
	if (IsValid(p) == false)
		return p->data_;

	T res = p->data_;
	p->pred_->succ_ = p->succ_;
	p->succ_->pred_ = p->pred_;

	delete p;
	p = nullptr;
	size_--;

	return res;
}


template<typename T> int List<T>::Remove(const T& e)
{
	ListNode<T>* p = header_->succ_;
	int count = 0;

	while (p != trailer_)
	{
		p = p->succ_;

		if (p->pred_->data_ == e)
		{
			Remove(p->pred_);
			count++;
		}
	}

	return count;
}


template<typename T> void List<T>::Merge(List<T>& lst)
{
	Merge(header_->succ_, GetSize(), lst, (lst.header_)->succ_, lst.GetSize());
}


template<typename T> void List<T>::Sort()
{
	std::uniform_int_distribution<int> u(0, 2);
	std::default_random_engine e;
	ListNode<T>* p = header_->succ_;

	switch (u(e))
	{
		case 0: InsertionSort(p, GetSize()); break;
		case 1: SelectionSort(p, GetSize()); break;
		case 2: MergeSort(p, GetSize()); break;
	}
}


template<typename T> int List<T>::Deduplicate()
{
	if (GetSize() <= 1)
		return 0;

	int old_size = GetSize();
	ListNode<T>* p = header_->succ_;
	int r = 0;
	ListNode<T>* q = nullptr;

	while (p != trailer_)
	{
		q = Find(p->data_, r, p);
		(q != nullptr) ? Remove(q) : r++;
		p = p->succ_;
	}

	return old_size - GetSize();
}


template<typename T> int List<T>::Uniquify()
{
	if (GetSize() <= 1)
		return 0;

	int old_size = GetSize();
	ListNode<T>* p = header_->succ_;
	ListNode<T>* q = p->succ_;

	while (q != trailer_)
	{
		if (p->data_ == q->data_)
			Remove(q);
		else
			p = q;
		q = p->succ_;
	}

	return old_size - GetSize();
}


template<typename T> void List<T>::Reverse()
{
	ListNode<T>* p = header_->succ_;
	ListNode<T>* q = trailer_->pred_;
	T temp = static_cast<T>(0);
	int n = GetSize() / 2;

	while (n > 0)
	{
		temp = p->data_;
		p->data_ = q->data_;
		q->data_ = temp;
		p = p->succ_;
		q = q->pred_;
		n--;
	}
}


template<typename T> template<typename VST> void List<T>::Traverse(VST& visit)
{
	ListNode<T>* p = header_->succ_;

	while (p != trailer_)
	{
		visit(p->data_);
		p = p->succ_;
	}
}


