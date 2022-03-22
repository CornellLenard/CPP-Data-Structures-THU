/*********************************************************************************

  * FileName:       priority_queue.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class PriorityQueue
  * Project:        The Data Structures - Vector
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


template<typename T> class PriorityQueue
{
public:
	/*
	* Inserts a new entry
	* @ Parameter:
	*       e:         The element
	*/
	virtual void Insert(T e) = 0;

	/*
	* Gets the element with the highest priority
	* @ Return:
	*                  The element with the highest priority
	*/
	virtual T GetMax() = 0;

	/*
	* Deletes the element with the highest priority
	* @ Return:
	*                  The element with the highest priority
	*/
	virtual T DeleteMax() = 0;
};


