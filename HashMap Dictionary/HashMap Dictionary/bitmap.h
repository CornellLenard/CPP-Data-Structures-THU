/*********************************************************************************

  * FileName:       bitmap.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class BitMap
  * Project:        The Data Structures - Hash Map Dictionary
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


class BitMap
{
private:
	// Points to the bitmap
	char* map_;
	// The number of chars in the map
	int size_;

protected:
	/*
	* Initializes the bitmap
	* @ Parameter:
	*       n:         The size of the bitmap
	*/
	void Init(int n);

public:
	BitMap(int n = 8);
	~BitMap();

	/*
	* Sets the kth bit
	* @ Parameter:
	*       k:         The bit 
	*/
	void Set(int k);

	/*
	* Clears the kth bit
	* @ Parameter:
	*       k:         The bit
	*/
	void Clear(int k);

	/*
	* Judges whether the kth bit is set
	* @ Parameter:
	*       k:         The bit
	* @ Return:
	*                  Whether the kth bit is set
	*/
	bool Test(int k);

	/*
	* Expands the bitmap
	* @ Parameter:
	*       k:         How many bits to expand to
	*/
	void Expand(int k);
};


