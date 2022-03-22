/*********************************************************************************

  * FileName:       list_node.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class ListNode
  * Project:        The Data Structures - List
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


template<typename T> class ListNode
{
public:
	// Stores the data
	T data_;
	// Points to the predecessor
	ListNode<T>* pred_;
	// Points to the successor
	ListNode<T>* succ_;

	ListNode(T e = static_cast<T>(0), ListNode<T>* p = nullptr, ListNode<T>* s = nullptr);
	~ListNode();

	/*
	* Inserts a new node as predecessor of the current node
	* @ Parameter:
	*       e:         The data of the new node
	* @ Return:
	*                  Points to the new node
	*/
	ListNode<T>* InsertAsPred(const T& e);

	/*
	* Inserts a new node as successor of the current node
	* @ Parameter:
	*       e:         The data of the new node
	* @ Return:
	*                  Points to the new node
	*/
	ListNode<T>* InsertAsSucc(const T& e);
};


template<typename T> ListNode<T>::ListNode(T e, ListNode<T>* p, ListNode<T>* s): data_(e), pred_(p), succ_(s)
{
}


template<typename T> ListNode<T>::~ListNode()
{
	pred_ = nullptr;
	succ_ = nullptr;
}


template<typename T> ListNode<T>* ListNode<T>::InsertAsPred(const T& e)
{
	ListNode<T>* x = new ListNode<T>(e, pred_, this);
	pred_->succ_ = x;
	pred_ = x;
	return x;
}


template<typename T> ListNode<T>* ListNode<T>::InsertAsSucc(const T& e)
{
	ListNode<T>* x = new ListNode<T>(e, this, succ_);
	succ_->pred_ = x;
	succ_ = x;
	return x;
}


