/*********************************************************************************

  * FileName:       hashmap_dictionary.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class HashMapDictionary
  * Project:        The Data Structures - Hash Map Dictionary
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <cmath>
#include <cstring>
#include "dictionary.h"
#include "entry.h"
#include "bitmap.h"


template<typename K, typename V> class HashMapDictionary: public Dictionary<K, V>
{
protected:
	// Points to the buckets
	Entry<K, V>** ht_;
	// The capacity of the buckets
	int capacity_;
	// The number of entries in the buckets
	int size_;
	// The lazy removal flag
	BitMap* lazy_removal_;

	/*
	* Judges whether x is lazy removed
	* @ Parameter:
	*       x:         The element
	* @ Return:
	*                  Whether x is lazy removed
	*/
	bool IsLazilyRemoved(int x);

	/*
	* Marks x as lazy removed
	* @ Parameter:
	*       x:         The element
	*/
	void MarkAsRemoved(int x);

	/*
	* Searches along the search chain corresponding to k, finds the bucket that matches the entry
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  The index
	*/
	int ProbeForHit(const K& k);

	/*
	* Searches along the search chain corresponding to k, finds the first bucket that can be used
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  The index
	*/
	int ProbeForFree(const K& k);

	/*
	* Expands and rehashes the buckets, ensures the load facor is below threshold
	*/
	void Rehash();

	/*
	* Gets the first prime number that >= c
	* @ Parameter:
	*       c:         The given number
	* @ Return:
	*                  The first prime number that >= c
	*/
	int GetPrime(int c);

	/*
	* Computes the hash code
	* @ Parameter:
	*       c:         The given char
	* @ Return:
	*                  The hash code
	*/
	size_t HashCode(char c);

	/*
	* Computes the hash code
	* @ Parameter:
	*       c:         The given int
	* @ Return:
	*                  The hash code
	*/
	size_t HashCode(int k);

	/*
	* Computes the hash code
	* @ Parameter:
	*       c:         The given long long
	* @ Return:
	*                  The hash code
	*/
	size_t HashCode(long long i);

	/*
	* Computes the hash code
	* @ Parameter:
	*       c:         The given char[]
	* @ Return:
	*                  The hash code
	*/
	size_t HashCode(char s[]);

public:
	HashMapDictionary(int c = 11);
	~HashMapDictionary();

	/*
	* Gets the number of entries
	* @ Return:
	*                  The number of entries
	*/
	int GetSize() const;

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


template<typename K, typename V> bool HashMapDictionary<K, V>::IsLazilyRemoved(int x)
{
	return lazy_removal_->Test(x);
}


template<typename K, typename V> void HashMapDictionary<K, V>::MarkAsRemoved(int x)
{
	lazy_removal_->Set(x);
}


template<typename K, typename V> int HashMapDictionary<K, V>::ProbeForHit(const K& k)
{
	int r = HashCode(k) % capacity_;

	while (((ht_[r] != nullptr) && (ht_[r]->key_ != k)) || ((ht_[r] == nullptr) && (IsLazilyRemoved(r) == true)))
		r = (r + 1) % capacity_;

	return r;
}


template<typename K, typename V> int HashMapDictionary<K, V>::ProbeForFree(const K& k)
{
	int r = HashCode(k) % capacity_;

	while (ht_[r] != nullptr)
		r = (r + 1) % capacity_;

	return r;
}


template<typename K, typename V> void HashMapDictionary<K, V>::Rehash()
{
	int old_capacity = capacity_;
	Entry<K, V>** old_ht = ht_;
	capacity_ = GetPrime(2 * capacity_);
	ht_ = new Entry<K, V>*[capacity_];
	memset(ht_, 0, capacity_ * sizeof(Entry<K, V>*));

	delete lazy_removal_;
	lazy_removal_ = new BitMap(capacity_);
	size_ = 0;

	for (int i = 0; i < old_capacity; i++)
	{
		if (old_ht[i] != nullptr)
		{
			Put(old_ht[i]->key_, old_ht[i]->value_);
			delete old_ht[i];
			old_ht[i] = nullptr;
		}
	}

	delete[] old_ht;
	old_ht = nullptr;
}


template<typename K, typename V> int HashMapDictionary<K, V>::GetPrime(int c)
{
	int i = c, temp = 0;
	bool found = true;

	for (;; i++)
	{
		found = true;
		temp = sqrt(i);

		for (int j = 2; j <= temp; j++)
		{
			if (i % j == 0)
			{
				found = false;
				break;
			}
		}

		if (found == true)
			break;
	}

	return i;
}


template<typename K, typename V> size_t HashMapDictionary<K, V>::HashCode(char c)
{
	return static_cast<size_t>(c);
}


template<typename K, typename V> size_t HashMapDictionary<K, V>::HashCode(int k)
{
	return static_cast<size_t>(k);
}


template<typename K, typename V> size_t HashMapDictionary<K, V>::HashCode(long long i)
{
	return static_cast<size_t>((i >> 32) + static_cast<int>(i));
}


template<typename K, typename V> size_t HashMapDictionary<K, V>::HashCode(char s[])
{
	unsigned int h = 0;
	size_t n = strlen(s);

	for (size_t i = 0; i < n; i++)
	{
		h = (h << 5) | (h >> 27);
		h += static_cast<int>(s[i]);
	}

	return static_cast<size_t>(h);
}


template<typename K, typename V> HashMapDictionary<K, V>::HashMapDictionary(int c)
{
	capacity_ = GetPrime(c);
	size_ = 0;
	ht_ = new Entry<K, V>*[capacity_];
	memset(ht_, 0, capacity_ * sizeof(Entry<K, V>*));
	lazy_removal_ = new BitMap(capacity_);
}


template<typename K, typename V> HashMapDictionary<K, V>::~HashMapDictionary()
{
	for (int i = 0; i < capacity_; i++)
	{
		if (ht_[i] != nullptr)
		{
			delete ht_[i];
			ht_[i] = nullptr;
		}
	}

	delete[] ht_;
	ht_ = nullptr;
	delete lazy_removal_;
	lazy_removal_ = nullptr;
}


template<typename K, typename V> int HashMapDictionary<K, V>::GetSize() const
{
	return size_;
}


template<typename K, typename V> bool HashMapDictionary<K, V>::Put(K k, V v)
{
	if (ht_[ProbeForHit(k)] != nullptr)
		return false;

	int r = ProbeForFree(k);
	ht_[r] = new Entry<K, V>(k, v);
	size_++;

	if (GetSize() * 2 > capacity_)
		Rehash();

	return true;
}


template<typename K, typename V> V* HashMapDictionary<K, V>::Get(K k)
{
	int r = ProbeForHit(k);
	return (ht_[r] != nullptr) ? &(ht_[r]->value_) : nullptr;
}


template<typename K, typename V> bool HashMapDictionary<K, V>::Remove(K k)
{
	int r = ProbeForHit(k);

	if (ht_[r] == nullptr)
		return false;

	delete ht_[r];
	ht_[r] = nullptr;
	MarkAsRemoved(r);
	size_--;

	return true;
}


