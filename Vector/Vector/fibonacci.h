/*********************************************************************************

  * FileName:       fibonacci.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class Fibonacci
  * Project:        The Data Structures - Vector
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


class Fibonacci
{
private:
	// The number of elements in the Fibonacci series
	int size_;
	// Points to the Fibonacci series
	int* fib_;
	// Points to the current element position
	int position_;

public:
	Fibonacci(int s = 2);
	~Fibonacci();

	/*
	* Gets the current element from the series
	* @ Return:
	*                  The current element from the series
	*/
	int Get() const;

	/*
	* The position steps one unit in prev direction
	*/
	void Prev();
};


