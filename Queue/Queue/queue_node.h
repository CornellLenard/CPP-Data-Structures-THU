/*********************************************************************************

  * FileName:       queue_node.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class QueueNode
  * Project:        The Data Structures - Queue
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


template<typename T> class QueueNode
{
public:
	// Stores the data
	T data_;
	// Points to the predecessor
	QueueNode<T>* pred_;
	// Points to the successor
	QueueNode<T>* succ_;

	QueueNode(T e = static_cast<T>(0), QueueNode<T>* p = nullptr, QueueNode<T>* s = nullptr);
	~QueueNode();

	/*
	* Inserts a new node as predecessor of the current node
	* @ Parameter:
	*       e:         The data of the new node
	* @ Return:
	*                  Points to the new node
	*/
	QueueNode<T>* InsertAsPred(const T& e);

	/*
	* Inserts a new node as successor of the current node
	* @ Parameter:
	*       e:         The data of the new node
	* @ Return:
	*                  Points to the new node
	*/
	QueueNode<T>* InsertAsSucc(const T& e);
};


template<typename T> QueueNode<T>::QueueNode(T e, QueueNode<T>* p, QueueNode<T>* s): data_(e), pred_(p), succ_(s)
{
}


template<typename T> QueueNode<T>::~QueueNode()
{
	pred_ = nullptr;
	succ_ = nullptr;
}


template<typename T> QueueNode<T>* QueueNode<T>::InsertAsPred(const T& e)
{
	QueueNode<T>* x = new QueueNode<T>(e, pred_, this);
	pred_->succ_ = x;
	pred_ = x;
	return x;
}


template<typename T> QueueNode<T>* QueueNode<T>::InsertAsSucc(const T& e)
{
	QueueNode<T>* x = new QueueNode<T>(e, this, succ_);
	succ_->pred_ = x;
	succ_ = x;
	return x;
}


