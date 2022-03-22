/*********************************************************************************

  * FileName:       entry.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class Entry
  * Project:        The Data Structures - Hash Map Dictionary
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


template<typename K, typename V> class Entry
{
public:
	// The key
	K key_;
	// The value
	V value_;

	Entry(K k = static_cast<K>(0), V v = static_cast<V>(0)) : key_(k), value_(v)
	{
	}

	Entry(const Entry<K, V>& e) : key_(e.key_), value_(e.value_)
	{
	}

	/*
	* Overloads <
	* @ Parameter:
	*       e:         The entry
	* @ Return:
	*                  Whether the current entry < e
	*/
	bool operator<(const Entry<K, V>& e) { return key_ < e.key_; }

	/*
	* Overloads >
	* @ Parameter:
	*       e:         The entry
	* @ Return:
	*                  Whether the current entry > e
	*/
	bool operator>(const Entry<K, V>& e) { return key_ > e.key_; }

	/*
	* Overloads ==
	* @ Parameter:
	*       e:         The entry
	* @ Return:
	*                  Whether the current entry == e
	*/
	bool operator==(const Entry<K, V>& e) { return key_ == e.key_; }

	/*
	* Overloads !=
	* @ Parameter:
	*       e:         The entry
	* @ Return:
	*                  Whether the current entry != e
	*/
	bool operator!=(const Entry<K, V>& e) { return key_ != e.key_; }
};


