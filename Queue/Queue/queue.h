/*********************************************************************************

  * FileName:       queue.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class Queue
  * Project:        The Data Structures - Queue
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "queue_node.h"
#include "queue_underflow_exception.h"


template<typename T> class Queue
{
protected:
	// The size of the queue
	int size_;
	// Points to the header node
	QueueNode<T>* header_;
	// Points to the trailer node
	QueueNode<T>* trailer_;

	/*
	* Initializes the queue
	*/
	void Init();

	/*
	* Frees the queue
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
	void CopyNodes(QueueNode<T>* p, int n);

	/*
	* Gets the pointer that points to the first node
	* @ Return:
	*                  The pointer that points to the first node
	*/
	QueueNode<T>* GetFirst() const;

	/*
	* Gets the pointer that points to the last node
	* @ Return:
	*                  The pointer that points to the last node
	*/
	QueueNode<T>* GetLast() const;

	/*
	* Inserts an element as first node
	* @ Parameter:
	*       e:         The value of the inserted element
	* @ Return:
	*                  Points to the new node
	*/
	QueueNode<T>* InsertAsFirst(const T& e);

	/*
	* Inserts an element as last node
	* @ Parameter:
	*       e:         The value of the inserted element
	* @ Return:
	*                  Points to the new node
	*/
	QueueNode<T>* InsertAsLast(const T& e);

	/*
	* Inserts an element after position p
	* @ Parameter:
	*       p:         The position
	*       e:         The value of the inserted element
	* @ Return:
	*                  Points to the new node
	*/
	QueueNode<T>* InsertAfter(QueueNode<T>* p, const T& e);

	/*
	* Inserts an element before position p
	* @ Parameter:
	*       p:         The position
	*       e:         The value of the inserted element
	* @ Return:
	*                  Points to the new node
	*/
	QueueNode<T>* InsertBefore(QueueNode<T>* p, const T& e);

	/*
	* Removes the node at position p
	* @ Parameter:
	*       p:         The position
	* @ Return:
	*                  The data stored in the removed node
	*/
	T Remove(QueueNode<T>* p);

public:
	Queue();
	Queue(const Queue<T>& q);
	Queue(QueueNode<T>* p, int n);
	~Queue();

	/*
	* Gets the size of the queue
	* @ Return:
	*                  The size of the queue
	*/
	int GetSize() const;

	/*
	* Whether the queue is empty
	* @ Return:
	*                  Whether the queue is empty
	*/
	bool IsEmpty() const;

	/*
	* Enqueues the element to the end of the queue
	* @ Parameter:
	*       e:         The element
	*/
	void Enqueue(const T& e);

	/*
	* Dequeues the element in the front of the queue
	* @ Return:
	*                  The element in the front of the queue
	*/
	T Dequeue();

	/*
	* Gets the element in the front of the queue
	* @ Return:
	*                  The element in the front of the queue
	*/
	T& GetFront();
};


template<typename T> void Queue<T>::Init()
{
	header_ = new QueueNode<T>();
	trailer_ = new QueueNode<T>();
	header_->succ_ = trailer_;
	header_->pred_ = nullptr;
	trailer_->succ_ = nullptr;
	trailer_->pred_ = header_;
	size_ = 0;
}


template<typename T> int Queue<T>::Clear()
{
	int old_size = GetSize();

	while (GetSize() > 0)
		Remove(header_->succ_);

	return old_size;
}


template<typename T> void Queue<T>::CopyNodes(QueueNode<T>* p, int n)
{
	Init();

	while (n > 0)
	{
		InsertAsLast(p->data_);
		p = p->succ_;
		n--;
	}
}


template<typename T> QueueNode<T>* Queue<T>::GetFirst() const
{
	return header_->succ_;
}


template<typename T> QueueNode<T>* Queue<T>::GetLast() const
{
	return trailer_->pred_;
}


template<typename T> QueueNode<T>* Queue<T>::InsertAsFirst(const T& e)
{
	size_++;
	return header_->InsertAsSucc(e);
}


template<typename T> QueueNode<T>* Queue<T>::InsertAsLast(const T& e)
{
	size_++;
	return trailer_->InsertAsPred(e);
}


template<typename T> QueueNode<T>* Queue<T>::InsertAfter(QueueNode<T>* p, const T& e)
{
	size_++;
	return p->InsertAsSucc(e);
}


template<typename T> QueueNode<T>* Queue<T>::InsertBefore(QueueNode<T>* p, const T& e)
{
	size_++;
	return p->InsertAsPred(e);
}


template<typename T> T Queue<T>::Remove(QueueNode<T>* p)
{
	T res = p->data_;
	p->pred_->succ_ = p->succ_;
	p->succ_->pred_ = p->pred_;
	delete p;
	p = nullptr;
	size_--;
	return res;
}


template<typename T> Queue<T>::Queue()
{
	Init();
}


template<typename T> Queue<T>::Queue(QueueNode<T>* p, int n)
{
	CopyNodes(p, n);
}


template<typename T> Queue<T>::Queue(const Queue<T>& q)
{
	CopyNodes((q.header_)->succ_, q.size_);
}


template<typename T> Queue<T>::~Queue()
{
	Clear();
	delete header_;
	header_ = nullptr;
	delete trailer_;
	trailer_ = nullptr;
}


template<typename T> int Queue<T>::GetSize() const
{
	return size_;
}


template<typename T> bool Queue<T>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename T> void Queue<T>::Enqueue(const T& e)
{
	InsertAsLast(e);
}


template<typename T> T Queue<T>::Dequeue()
{
	if (GetSize() == 0)
		throw QueueUnderflowException();

	return Remove(header_->succ_);
}


template<typename T> T& Queue<T>::GetFront()
{
	if (GetSize() == 0)
		throw QueueUnderflowException();

	return header_->succ_->data_;
}


