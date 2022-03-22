/*********************************************************************************

  * FileName:       vector.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class Vector
  * Project:        The Data Structures - Vector
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <random>
#include "fibonacci.h"
#include "priority_queue_array_heap.h"
#include "vector_index_out_of_bounds_exception.h"


// Defines "rank"
typedef int Rank;


template<typename T> class Vector
{
protected:
	// The default initial capacity
	const static int DEFAULT_CAPACITY_ = 11;
	// The size of vector = the number of elements currently in vector
	Rank size_;
	// The capacity of vector
	int capacity_;
	// Points to the vector data
	T* element_;

	/*
	* Copies the data from array A[lo, hi)
	* @ Parameter:
	*       A:         The data that is copied
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void CopyFrom(const T* A, Rank lo, Rank hi);

	/*
	* Expands the vector when the capacity is not sufficient
	*/
	void Expand();

	/*
	* Shrinks the vector when too much memory of the vector is not used
	*/
	void Shrink();

	/*
	* Binary search algorithm
	* @ Parameter:
	*       e:         The value that is searched
	*       lo:        The lower bound
	*       hi:        The upper bound
	* @ Return:
	*                  The index of search result
	*/
	Rank BinSearch(const T& e, Rank lo, Rank hi) const;

	/*
	* Fibonacci search algorithm
	* @ Parameter:
	*       e:         The value that is searched
	*       lo:        The lower bound
	*       hi:        The upper bound
	* @ Return:
	*                  The index of search result
	*/
	Rank FibSearch(const T& e, Rank lo, Rank hi) const;

	/*
	* Bubble sort algorithm
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void BubbleSort(Rank lo, Rank hi);

	/*
	* Selection sort algorithm
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void SelectionSort(Rank lo, Rank hi);

	/*
	* Merge algorithm
	* @ Parameter:
	*       lo:        The lower bound
	*       mi:        The mid point
	*       hi:        The upper bound
	*/
	void Merge(Rank lo, Rank mi, Rank hi);

	/*
	* Merge sort algorithm
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void MergeSort(Rank lo, Rank hi);

	/*
	* Gets the partition
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	* @ Return:
	*                  The partition
	*/
	Rank GetPartition(Rank lo, Rank hi);

	/*
	* Quick sort algorithm
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void QuickSort(Rank lo, Rank hi);

	/*
	* Heap sort algorithm
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void HeapSort(Rank lo, Rank hi);

public:
	Vector(int c = DEFAULT_CAPACITY_, Rank s = 0, T v = static_cast<T>(0));
	Vector(const T* A, Rank n);
	Vector(const T* A, Rank lo, Rank hi);
	Vector(const Vector<T>& v);
	Vector(const Vector<T>& v, Rank lo, Rank hi);
	~Vector();

	/*
	* Overloads the [], returns const reference as right value
	* @ Parameter:
	*       r:         The rank
	* @ Return:
	*                  The const reference of the element
	*/
	const T& operator[](Rank r) const;

	/*
	* Gets the size
	* @ Return:
	*                  The size
	*/
	Rank GetSize() const;

	/*
	* Whether the vector is empty
	* @ Return:
	*                  Whether the vector is empty
	*/
	bool IsEmpty() const;

	/*
	* Gets the number of disordered pairs in the vector
	* @ Return:
	*                  The number of disordered pairs in the vector
	*/
	int Disordered() const;

	/*
	* Search algorithm in unordered vector
	* @ Parameter:
	*       e:         The value that is searched
	* @ Return:
	*                  The index of search result
	*/
	Rank Find(const T& e) const;

	/*
	* Search algorithm in unordered vector[lo, hi)
	* @ Parameter:
	*       e:         The value that is searched
	*       lo:        The lower bound
	*       hi:        The upper bound
	* @ Return:
	*                  The index of search result, if not found, returns lo - 1
	*/
	Rank Find(const T& e, Rank lo, Rank hi) const;

	/*
	* Search algorithm in ordered vector
	* @ Parameter:
	*       e:         The value that is searched
	* @ Return:
	*                  The index of search result
	*/
	Rank Search(const T& e) const;

	/*
	* Search algorithm in ordered vector[lo, hi)
	* @ Parameter:
	*       e:         The value that is searched
	*       lo:        The lower bound
	*       hi:        The upper bound
	* @ Return:
	*                  The index of search result, if not found, returns the rank of the element that is largest among elements <= e
	*/
	Rank Search(const T& e, Rank lo, Rank hi) const;

	/*
	* Overloads the [], returns non-const reference as left or right value
	* @ Parameter:
	*       r:         The rank
	* @ Return:
	*                  The non-const reference of the element
	*/
	T& operator[](Rank r);

	/*
	* Overloads =
	* @ Parameter:
	*       v:         The vector
	* @ Return:
	*                  The assigned vector
	*/
	Vector<T>& operator=(const Vector<T>& v);

	/*
	* Removes the element with rank r
	* @ Parameter:
	*       r:         The rank
	*       lo:        The lower bound
	*       hi:        The upper bound
	* @ Return:
	*                  The value of the removed element
	*/
	T Remove(Rank r);

	/*
	* Removes vector[lo, hi)
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	* @ Return:
	*                  The number of elements that are removed
	*/
	int Remove(Rank lo, Rank hi);

	/*
	* Inserts an element in rank r
	* @ Parameter:
	*       r:         The insertion index
	*       e:         The value of the inserted element
	* @ Return:
	*                  The index of the newly inserted element
	*/
	Rank Insert(Rank r, const T& e);

	/*
	* Inserts an element in the end of the vector
	* @ Parameter:
	*       e:         The value of the inserted element
	* @ Return:
	*                  The index of the newly inserted element
	*/
	Rank Insert(const T& e);

	/*
	* Sorts vector[lo, hi)
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void Sort(Rank lo, Rank hi);

	/*
	* Removes vector
	*/
	void Sort();

	/*
	* Disorders vector[lo, hi)
	* @ Parameter:
	*       lo:        The lower bound
	*       hi:        The upper bound
	*/
	void Unsort(Rank lo, Rank hi);

	/*
	* Disorders vector
	*/
	void Unsort();

	/*
	* Deduplicates unordered vector
	* @ Return:
	*                  The number of elements that are removed
	*/
	int Deduplicate();

	/*
	* uniquifies ordered vector
	* @ Return:
	*                  The number of elements that are removed
	*/
	int Uniquify();

	/*
	* Traverses the vector
	* @ Parameter:
	*       visit:     The function object
	*/
	template<typename VST> void Traverse(VST& visit);
};


template<typename T> void Vector<T>::CopyFrom(const T* A, Rank lo, Rank hi)
{
	capacity_ = 2 * (hi - lo);
	size_ = hi - lo;
	element_ = new T[capacity_];
	for (Rank i = 0; i < size_; i++)
		element_[i] = A[lo + i];
}


template<typename T> void Vector<T>::Expand()
{
	if (GetSize() < capacity_)
		return;

	if (capacity_ < DEFAULT_CAPACITY_)
		capacity_ = DEFAULT_CAPACITY_;

	T* old_element = element_;
	capacity_ *= 2;
	element_ = new T[capacity_];

	for (Rank i = 0; i < GetSize(); i++)
		element_[i] = old_element[i];

	delete[] old_element;
	old_element = nullptr;
}


template<typename T> void Vector<T>::Shrink()
{
	if (capacity_ / 2 < DEFAULT_CAPACITY_)
		return;

	if (GetSize() * 4 > capacity_)
		return;

	T* old_element = element_;
	capacity_ /= 2;
	element_ = new T[capacity_];

	for (Rank i = 0; i < GetSize(); i++)
		element_[i] = old_element[i];

	delete[] old_element;
	old_element = nullptr;
}


template<typename T> Rank Vector<T>::BinSearch(const T& e, Rank lo, Rank hi) const
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	Rank mi = 0;

	while (lo < hi)
	{
		mi = (lo + hi) / 2;
		(e < element_[mi]) ? hi = mi : lo = mi + 1;
	}

	return lo - 1;
}


template<typename T> Rank Vector<T>::FibSearch(const T& e, Rank lo, Rank hi) const
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	Fibonacci fib(hi - lo);
	Rank mi = 0;

	while (lo < hi)
	{
		while (fib.Get() > hi - lo)
			fib.Prev();

		mi = lo + fib.Get() - 1;

		if (e < element_[mi])
			hi = mi;
		else if (e > element_[mi])
			lo = mi + 1;
		else
			return mi;
	}
}


template<typename T> void Vector<T>::BubbleSort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	Rank upper_bound = hi - 1;
	Rank uncertain_upper_bound = 0;
	T temp = static_cast<T>(0);

	while (lo < upper_bound)
	{
		uncertain_upper_bound = 0;

		for (Rank i = lo; i < upper_bound; i++)
		{
			if (element_[i] > element_[i + 1])
			{
				temp = element_[i];
				element_[i] = element_[i + 1];
				element_[i + 1] = temp;
				uncertain_upper_bound = i;
			}
		}

		upper_bound = uncertain_upper_bound;
	}
}


template<typename T> void Vector<T>::SelectionSort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	Rank max = 0;
	T temp = static_cast<T>(0);

	for (Rank upper_bound = hi - 1; upper_bound > lo; upper_bound--)
	{
		max = lo;

		for (Rank i = lo + 1; i <= upper_bound; i++)
			if (element_[i] >= element_[max])
				max = i;

		if (max == upper_bound)
			continue;
		else
		{
			temp = element_[upper_bound];
			element_[upper_bound] = element_[max];
			element_[max] = temp;
		}
	}
}


template<typename T> void Vector<T>::Merge(Rank lo, Rank mi, Rank hi)
{
	int lb = mi - lo, lc = hi - mi;

	T* A = element_ + lo;
	T* B = new T[lb];

	for (Rank i = 0; i < lb; i++)
		B[i] = A[i];

	T* C = element_ + mi;

	for (Rank i = 0, j = 0, k = 0; j < lb;)
		A[i++] = (k >= lc || B[j] <= C[k]) ? B[j++] : C[k++];

	delete[] B;
	B = nullptr;
}


template<typename T> void Vector<T>::MergeSort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	if (hi - lo <= 1)
		return;

	Rank mi = (lo + hi) / 2;

	MergeSort(lo, mi);
	MergeSort(mi, hi);
	Merge(lo, mi, hi);
}


template<typename T> Rank Vector<T>::GetPartition(Rank lo, Rank hi)
{
	T temp = static_cast<T>(0);
	std::uniform_int_distribution<int> u(0, hi - lo - 1);
	std::default_random_engine e;
	Rank rd = u(e);
	temp = element_[lo];
	element_[lo] = element_[lo + rd];
	element_[lo + rd] = temp;
	T pivot = element_[lo];
	hi--;

	while (lo < hi)
	{
		while ((lo < hi) && (pivot <= element_[hi]))
			hi--;

		element_[lo] = element_[hi];

		while ((lo < hi) && (pivot >= element_[lo]))
			lo++;

		element_[hi] = element_[lo];
	}

	element_[lo] = pivot;
	return lo;
}


template<typename T> void Vector<T>::QuickSort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	if (hi - lo <= 1)
		return;

	Rank mi = GetPartition(lo, hi);
	QuickSort(lo, mi);
	QuickSort(mi + 1, hi);
}


template<typename T> void Vector<T>::HeapSort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	PriorityQueueArrayHeap<T> heap(element_ + lo, hi - lo);

	while (heap.IsEmpty() == false)
		element_[--hi] = heap.DeleteMax();
}


template<typename T> Vector<T>::Vector(int c, Rank s, T v)
{
	capacity_ = c;
	size_ = s;
	element_ = new T[capacity_];
	for (Rank i = 0; i < size_; i++)
		element_[i] = v;
}


template<typename T> Vector<T>::Vector(const T* A, Rank n)
{
	CopyFrom(A, 0, n);
}


template<typename T> Vector<T>::Vector(const T* A, Rank lo, Rank hi)
{
	CopyFrom(A, lo, hi);
}


template<typename T> Vector<T>::Vector(const Vector<T>& v)
{
	CopyFrom(v.element_, 0, v.size_);
}


template<typename T> Vector<T>::Vector(const Vector<T>& v, Rank lo, Rank hi)
{
	CopyFrom(v.element_, lo, hi);
}


template<typename T> Vector<T>::~Vector()
{
	delete[] element_;
	element_ = nullptr;
}


template<typename T> const T& Vector<T>::operator[](Rank r) const
{
	if (r < 0 || r >= GetSize())
		throw VectorIndexOutOfBoundsException();

	return element_[r];
}


template<typename T> Rank Vector<T>::GetSize() const
{
	return size_;
}


template<typename T> bool Vector<T>::IsEmpty() const
{
	return !static_cast<bool>(GetSize());
}


template<typename T> int Vector<T>::Disordered() const
{
	int count = 0;

	for (Rank i = 0; i < GetSize() - 1; i++)
		if (element_[i] > element_[i + 1])
			count++;

	return count;
}


template<typename T> Rank Vector<T>::Find(const T& e) const
{
	return Find(e, 0, GetSize());
}


template<typename T> Rank Vector<T>::Find(const T& e, Rank lo, Rank hi) const
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	for (Rank i = hi - 1; i >= lo; i--)
		if (element_[i] == e)
			return i;

	return lo - 1;
}


template<typename T> Rank Vector<T>::Search(const T& e) const
{
	return (GetSize() == 0) ? (-1) : Search(e, 0, GetSize());
}


template<typename T> Rank Vector<T>::Search(const T& e, Rank lo, Rank hi) const
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	std::uniform_int_distribution<int> u(0, 1);
	std::default_random_engine e;

	return u(e) ? BinSearch(e, lo, hi) : FibSearch(e, lo, hi);
}


template<typename T> T Vector<T>::Remove(Rank r)
{
	if (r < 0 || r >= GetSize())
		throw VectorIndexOutOfBoundsException();

	T e = element_[r];
	Remove(r, r + 1);

	return e;
}


template<typename T> int Vector<T>::Remove(Rank lo, Rank hi)
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	if (lo == hi)
		return 0;

	for (Rank i = hi; i < GetSize(); i++)
		element_[i - hi + lo] = element_[i];

	size_ -= (hi - lo);
	Shrink();

	return hi - lo;
}


template<typename T> Rank Vector<T>::Insert(Rank r, const T& e)
{
	if (r > GetSize())
		throw VectorIndexOutOfBoundsException();

	Expand();

	for (Rank i = GetSize() - 1; i >= r; i--)
		element_[i + 1] = element_[i];
	element_[r] = e;
	size_++;

	return r;
}


template<typename T> Rank Vector<T>::Insert(const T& e)
{
	return Insert(GetSize(), e);
}


template<typename T> void Vector<T>::Sort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	std::uniform_int_distribution<int> u(0, 4);
	std::default_random_engine e;

	switch (u(e))
	{
		case 0: BubbleSort(lo, hi); break;
		case 1: SelectionSort(lo, hi); break;
		case 2: MergeSort(lo, hi); break;
		case 3: HeapSort(lo, hi); break;
		case 4: QuickSort(lo, hi); break;
	}
}


template<typename T> void Vector<T>::Sort()
{
	Sort(0, GetSize());
}


template<typename T> void Vector<T>::Unsort(Rank lo, Rank hi)
{
	if (lo < 0 || lo > GetSize() || hi < 0 || hi > GetSize())
		throw VectorIndexOutOfBoundsException();

	T* v = element_ + lo;
	T temp;
	std::default_random_engine e;
	Rank r = 0;

	for (Rank i = hi - 1; i >= lo + 1; i--)
	{
		std::uniform_int_distribution<int> u(0, i - 1);
		r = u(e);
		temp = element_[i];
		element_[i] = element_[r];
		element_[r] = temp;
	}
}


template<typename T> void Vector<T>::Unsort()
{
	Unsort(0, GetSize());
}


template<typename T> T& Vector<T>::operator[](Rank r)
{
	if (r < 0 || r >= GetSize())
		throw VectorIndexOutOfBoundsException();

	return element_[r];
}


template<typename T> Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
	if (element_ != nullptr)
		delete[] element_;

	CopyFrom(v.element_, 0, v.size_);

	return *this;
}


template<typename T> int Vector<T>::Deduplicate()
{
	int old_size = GetSize();
	Rank i = 1;

	while (i < GetSize())
		(Find(element_[i], 0, i) < 0) ? i++ : Remove(i);

	return old_size - GetSize();
}


template<typename T> int Vector<T>::Uniquify()
{
	Rank i = 0, j = 1;

	while (j < GetSize())
	{
		if (element_[i] != element_[j])
			element_[++i] = element_[j];
		j++;
	}

	size_ = ++i;
	Shrink();

	return j - i;
}


template<typename T> template<typename VST> void Vector<T>::Traverse(VST& visit)
{
	for (Rank i = 0; i < GetSize(); i++)
		visit(element_[i]);
}


