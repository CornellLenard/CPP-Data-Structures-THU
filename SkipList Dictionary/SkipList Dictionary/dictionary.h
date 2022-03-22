/*********************************************************************************

  * FileName:       dictionary.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class Dictionary
  * Project:        The Data Structures - SkipList Dictionary
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


template<typename K, typename V> class Dictionary
{
public:
	/*
	* Gets the number of entries
	* @ Return:
	*                  The number of entries
	*/
	virtual int GetSize() const = 0;

	/*
	* Inserts an entry
	* @ Parameter:
	*       k:         The key
	*       v:         The value
	* @ Return:
	*                  Whether insertion is successful
	*/
	virtual bool Put(K k, V v) = 0;

	/*
	* Gets the value of the entry with key == k
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  The value of the entry with key == k
	*/
	virtual V* Get(K k) = 0;

	/*
	* Removes the entry with key == k
	* @ Parameter:
	*       k:         The key
	* @ Return:
	*                  Whether removal is successful
	*/
	virtual bool Remove(K k) = 0;
};


