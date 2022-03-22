/*********************************************************************************

  * FileName:       priority_queue_array_heap.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class PriorityQueueArrayHeap
  * Project:        The Data Structures - Vector
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <iostream>
#include "priority_queue.h"
#include "array_for_heap.h"


template<typename T> class PriorityQueueArrayHeap : public PriorityQueue<T>, public ArrayForHeap<T>
{
protected:
	/*
	* Judges whether the index i is valid
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  Whether the index i is valid
	*/
	bool InHeap(int i);

	/*
	* Gets the index of the node i's mother node
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  The index of the node i's mother node
	*/
	int Parent(int i);

	/*
	* Gets the last internal node
	* @ Return:
	*                  The last internal node
	*/
	int LastInternal();

	/*
	* Gets the index of the node i's left child
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  The index of the node i's left child
	*/
	int LChild(int i);

	/*
	* Gets the index of the node i's left child
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  The index of the node i's left child
	*/
	int RChild(int i);

	/*
	* Judges whether the node i has mother node
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  Whether the node i has mother node
	*/
	bool HasParent(int i);

	/*
	* Judges whether the node i has left child
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  Whether the node i has left child
	*/
	bool HasLChild(int i);

	/*
	* Judges whether the node i has right child
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  Whether the node i has right child
	*/
	bool HasRChild(int i);

	/*
	* Gets the index of the higher one between node i and node j
	* @ Parameter:
	*       i:         The index of node i
	*       j:         The index of node j
	* @ Return:
	*                  The index of the higher one between node i and node j
	*/
	int GetHigher(int i, int j);

	/*
	* Gets the index of the highest one among node i and its two children
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  The index of the highest one among node i and its two children
	*/
	int GetMaxOfThree(int i);

	/*
	* Percolate down algorithm
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  The final index of node i
	*/
	int PercolateDown(int i);

	/*
	* Percolate up algorithm
	* @ Parameter:
	*       i:         The index of node i
	* @ Return:
	*                  The final index of node i
	*/
	int PercolateUp(int i);

	/*
	* Floyd heapify algorithm
	*/
	void Heapify();

public:
	PriorityQueueArrayHeap();
	PriorityQueueArrayHeap(T* A, int n);

	/*
	* Inserts a new entry
	* @ Parameter:
	*       e:         The element
	*/
	void Insert(T e);

	/*
	* Gets the element with the highest priority
	* @ Return:
	*                  The element with the highest priority
	*/
	T GetMax();

	/*
	* Deletes the element with the highest priority
	* @ Return:
	*                  The element with the highest priority
	*/
	T DeleteMax();
};


template<typename T> bool PriorityQueueArrayHeap<T>::InHeap(int i)
{
	return (i >= 0) && (i < this->GetSize());
}


template<typename T> int PriorityQueueArrayHeap<T>::Parent(int i)
{
	return (i - 1) / 2;
}


template<typename T> int PriorityQueueArrayHeap<T>::LastInternal()
{
	return Parent(this->GetSize() - 1);
}


template<typename T> int PriorityQueueArrayHeap<T>::LChild(int i)
{
	return 2 * i + 1;
}


template<typename T> int PriorityQueueArrayHeap<T>::RChild(int i)
{
	return 2 * i + 2;
}


template<typename T> bool PriorityQueueArrayHeap<T>::HasParent(int i)
{
	return i > 0;
}


template<typename T> bool PriorityQueueArrayHeap<T>::HasLChild(int i)
{
	return InHeap(LChild(i)) == true;
}


template<typename T> bool PriorityQueueArrayHeap<T>::HasRChild(int i)
{
	return InHeap(RChild(i)) == true;
}


template<typename T> int PriorityQueueArrayHeap<T>::GetHigher(int i, int j)
{
	return (this->element_[i] < this->element_[j]) ? j : i;
}


template<typename T> int PriorityQueueArrayHeap<T>::GetMaxOfThree(int i)
{
	int lc = LChild(i), rc = RChild(i), max = 0;

	if (InHeap(rc) == true)
	{
		max = GetHigher(i, lc);
		max = GetHigher(max, rc);
	}
	else if (InHeap(lc) == true)
		max = GetHigher(i, lc);
	else
		max = i;

	return max;
}


template<typename T> int PriorityQueueArrayHeap<T>::PercolateDown(int i)
{
	T temp = static_cast<T>(0);
	int j = GetMaxOfThree(i);

	while (i != j)
	{
		temp = this->element_[i];
		this->element_[i] = this->element_[j];
		this->element_[j] = temp;
		i = j;
		j = GetMaxOfThree(i);
	}

	return i;
}


template<typename T> int PriorityQueueArrayHeap<T>::PercolateUp(int i)
{
	int j = 0;
	T temp = static_cast<T>(0);

	while (HasParent(i) == true)
	{
		j = Parent(i);

		if (this->element_[i] < this->element_[j])
			break;

		temp = this->element_[i];
		this->element_[i] = this->element_[j];
		this->element_[j] = temp;
		i = j;
	}

	return i;
}


template<typename T> void PriorityQueueArrayHeap<T>::Heapify()
{
	for (int i = LastInternal(); InHeap(i) == true; i--)
		PercolateDown(i);
}


template<typename T> PriorityQueueArrayHeap<T>::PriorityQueueArrayHeap()
{
}


template<typename T> PriorityQueueArrayHeap<T>::PriorityQueueArrayHeap(T* A, int n) : ArrayForHeap<T>(A, n)
{
	Heapify();
}


template<typename T> void PriorityQueueArrayHeap<T>::Insert(T e)
{
	ArrayForHeap<T>::Insert(e);
	PercolateUp(this->GetSize() - 1);
}


template<typename T> T PriorityQueueArrayHeap<T>::GetMax()
{
	return this->element_[0];
}


template<typename T> T PriorityQueueArrayHeap<T>::DeleteMax()
{
	if (this->GetSize() == 0)
	{
		std::cout << "Warning ! You cannot call deleteMax() from an empty priority queue !\n";
		return this->element_[0];
	}

	T max = this->element_[0];
	this->element_[0] = this->element_[--(this->size_)];
	PercolateDown(0);

	return max;
}


