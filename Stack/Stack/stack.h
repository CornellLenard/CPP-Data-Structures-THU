/*********************************************************************************

  * FileName:       stack.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class Stack
  * Project:        The Data Structures - Stack
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "stack_underflow_exception.h"


template<typename T> class Stack
{
protected:
	// The default initial capacity
	const static int DEFAULT_CAPACITY_ = 11;
	// The size of stack = the number of elements currently in stack
	int size_;
	// The capacity of stack
	int capacity_;
	// Points to the stack data
	T* element_;

	/*
	* Copies the data from array A[lo, hi)
	* @ Parameter:
	*       A:         The data that is copied
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void CopyFrom(const T* A, int lo, int hi);

	/*
	* Expands the stack when the capacity is not sufficient
	*/
	void Expand();

	/*
	* Shrinks the stack when too much memory of the stack is not used
	*/
	void Shrink();

public:
	Stack(int c = DEFAULT_CAPACITY_, int s = 0, T v = static_cast<T>(0));
	Stack(const T* A, int n);
	Stack(const T* A, int lo, int hi);
	Stack(const Stack<T>& s);
	Stack(const Stack<T>& s, int lo, int hi);
	~Stack();

	/*
	* Gets the size
	* @ Return:
	*                  The size
	*/
	int GetSize() const;

	/*
	* Whether the stack is empty
	* @ Return:
	*                  Whether the stack is empty
	*/
	bool IsEmpty() const;

	/*
	* Overloads =
	* @ Parameter:
	*       v:         The stack
	* @ Return:
	*                  The assigned stack
	*/
	Stack<T>& operator=(const Stack<T>& s);

	/*
	* Pushes the element to the top of the stack
	* @ Parameter:
	*       e:         The element
	*/
	void Push(const T& e);

	/*
	* Pops the top element out of the stack
	* @ Return:
	*                  The top element
	*/
	T Pop();

	/*
	* Gets the top element
	* @ Return:
	*                  The top element
	*/
	T& Top();
};


template<typename T> void Stack<T>::CopyFrom(const T* A, int lo, int hi)
{
	capacity_ = 2 * (hi - lo);
	size_ = hi - lo;
	element_ = new T[capacity_];

	for (int i = 0; i < size_; i++)
		element_[i] = A[lo + i];
}


template<typename T> void Stack<T>::Expand()
{
	if (GetSize() < capacity_)
		return;

	if (capacity_ < DEFAULT_CAPACITY_)
		capacity_ = DEFAULT_CAPACITY_;

	T* old_element = element_;
	capacity_ *= 2;
	element_ = new T[capacity_];

	for (int i = 0; i < GetSize(); i++)
		element_[i] = old_element[i];

	delete[] old_element;
	old_element = nullptr;
}


template<typename T> void Stack<T>::Shrink()
{
	if (capacity_ / 2 < DEFAULT_CAPACITY_)
		return;

	if (GetSize() * 4 > capacity_)
		return;

	T* old_element = element_;
	capacity_ /= 2;
	element_ = new T[capacity_];

	for (int i = 0; i < GetSize(); i++)
		element_[i] = old_element[i];

	delete[] old_element;
	old_element = nullptr;
}


template<typename T> Stack<T>::Stack(int c, int s, T v)
{
	capacity_ = c;
	size_ = s;
	element_ = new T[capacity_];
	for (int i = 0; i < size_; i++)
		element_[i] = v;
}


template<typename T> Stack<T>::Stack(const T* A, int n)
{
	CopyFrom(A, 0, n);
}


template<typename T> Stack<T>::Stack(const T* A, int lo, int hi)
{
	CopyFrom(A, lo, hi);
}


template<typename T> Stack<T>::Stack(const Stack<T>& s)
{
	CopyFrom(s.element, 0, s.size);
}


template<typename T> Stack<T>::Stack(const Stack<T>& s, int lo, int hi)
{
	CopyFrom(s.element, lo, hi);
}


template<typename T> Stack<T>::~Stack()
{
	delete[] element_;
	element_ = nullptr;
}


template<typename T> int Stack<T>::GetSize() const
{
	return size_;
}


template<typename T> bool Stack<T>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename T> Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
	if (element_ != nullptr)
		delete[] element_;

	CopyFrom(s.element_, 0, s.size_);
	return *this;
}


template<typename T> void Stack<T>::Push(const T& e)
{
	Expand();
	element_[GetSize()] = e;
	size_++;
}


template<typename T> T Stack<T>::Pop()
{
	if (GetSize() == 0)
		throw StackUnderflowException();

	T res = element_[GetSize() - 1];
	size_--;
	Shrink();

	return res;
}


template<typename T> T& Stack<T>::Top()
{
	if (GetSize() == 0)
		throw StackUnderflowException();

	return element_[GetSize() - 1];
}


