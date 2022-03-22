/*********************************************************************************

  * FileName:       array_for_heap.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class ArrayForHeap
  * Project:        The Data Structures - Vector
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include "array_index_out_of_bounds_exception.h"


template<typename T> class ArrayForHeap
{
protected:
	// The default initial capacity
	const static int DEFAULT_CAPACITY_ = 11;
	// The size of array = the number of elements currently in array
	int size_;
	// The capacity of array
	int capacity_;
	// Points to the array data
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
	* Expands the array when the capacity is not sufficient
	*/
	void Expand();

	/*
	* Shrinks the array when too much memory of the array is not used
	*/
	void Shrink();

public:
	ArrayForHeap(int c = DEFAULT_CAPACITY_, int s = 0, T v = static_cast<T>(0));
	ArrayForHeap(const T* A, int n);
	ArrayForHeap(const T* A, int lo, int hi);
	ArrayForHeap(const ArrayForHeap<T>& ar);
	ArrayForHeap(const ArrayForHeap<T>& ar, int lo, int hi);
	~ArrayForHeap();

	/*
	* Overloads the [], returns const reference as right value
	* @ Parameter:
	*       r:         The index
	* @ Return:
	*                  The const reference of the element
	*/
	const T& operator[](int r) const;

	/*
	* Gets the size
	* @ Return:
	*                  The size
	*/
	int GetSize() const;

	/*
	* Whether the array is empty
	* @ Return:
	*                  Whether the array is empty
	*/
	bool IsEmpty() const;

	/*
	* Overloads the [], returns non-const reference as left or right value
	* @ Parameter:
	*       r:         The index
	* @ Return:
	*                  The non-const reference of the element
	*/
	T& operator[](int r);

	/*
	* Overloads =
	* @ Parameter:
	*       ar:        The array
	* @ Return:
	*                  The assigned array
	*/
	ArrayForHeap<T>& operator=(const ArrayForHeap<T>& ar);

	/*
	* Inserts an element in index r
	* @ Parameter:
	*       r:         The insertion index
	*       e:         The value of the inserted element
	* @ Return:
	*                  The index of the newly inserted element
	*/
	int Insert(int r, const T& e);

	/*
	* Inserts an element in the end of the array
	* @ Parameter:
	*       e:         The value of the inserted element
	* @ Return:
	*                  The index of the newly inserted element
	*/
	int Insert(const T& e);
};


template<typename T> void ArrayForHeap<T>::CopyFrom(const T* A, int lo, int hi)
{
	capacity_ = 2 * (hi - lo);
	size_ = hi - lo;
	element_ = new T[capacity_];
	for (int i = 0; i < size_; i++)
		element_[i] = A[lo + i];
}


template<typename T> void ArrayForHeap<T>::Expand()
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


template<typename T> void ArrayForHeap<T>::Shrink()
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


template<typename T> ArrayForHeap<T>::ArrayForHeap(int c, int s, T v)
{
	capacity_ = c;
	size_ = s;
	element_ = new T[capacity_];
	for (int i = 0; i < size_; i++)
		element_[i] = v;
}


template<typename T> ArrayForHeap<T>::ArrayForHeap(const T* A, int n)
{
	CopyFrom(A, 0, n);
}


template<typename T> ArrayForHeap<T>::ArrayForHeap(const T* A, int lo, int hi)
{
	CopyFrom(A, lo, hi);
}


template<typename T> ArrayForHeap<T>::ArrayForHeap(const ArrayForHeap<T>& ar)
{
	CopyFrom(ar.element_, 0, ar.size_);
}


template<typename T> ArrayForHeap<T>::ArrayForHeap(const ArrayForHeap<T>& ar, int lo, int hi)
{
	CopyFrom(ar.element_, lo, hi);
}


template<typename T> ArrayForHeap<T>::~ArrayForHeap()
{
	delete[] element_;
	element_ = nullptr;
}


template<typename T> const T& ArrayForHeap<T>::operator[](int r) const
{
	if (r < 0 || r >= GetSize())
		throw ArrayIndexOutOfBoundsException();

	return element_[r];
}


template<typename T> int ArrayForHeap<T>::GetSize() const
{
	return size_;
}


template<typename T> bool ArrayForHeap<T>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename T> int ArrayForHeap<T>::Insert(int r, const T& e)
{
	if (r > GetSize())
		throw ArrayIndexOutOfBoundsException();

	Expand();

	for (int i = GetSize() - 1; i >= r; i--)
		element_[i + 1] = element_[i];

	element_[r] = e;
	size_++;

	return r;
}


template<typename T> int ArrayForHeap<T>::Insert(const T& e)
{
	return Insert(GetSize(), e);
}


template<typename T> T& ArrayForHeap<T>::operator[](int r)
{
	if (r < 0 || r >= GetSize())
		throw ArrayIndexOutOfBoundsException();

	return element_[r];
}


template<typename T> ArrayForHeap<T>& ArrayForHeap<T>::operator=(const ArrayForHeap<T>& ar)
{
	if (element_ != nullptr)
		delete[] element_;

	CopyFrom(ar.element_, 0, ar.size_);

	return *this;
}


