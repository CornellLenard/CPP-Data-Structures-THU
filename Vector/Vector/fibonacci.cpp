/*********************************************************************************

  * FileName:       fibonacci.cpp
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The implementation of the class Fibonacci
  * Project:        The Data Structures - Vector
  * Reference:      THU Data Structures

**********************************************************************************/


#include "fibonacci.h"


Fibonacci::Fibonacci(int s)
{
	(s <= 2) ? size_ = 2 : size_ = s;

	fib_ = new int[size_];
	fib_[0] = 0;
	fib_[1] = 1;

	for (int i = 2; i < size_; i++)
		fib_[i] = fib_[i - 1] + fib_[i - 2];

	position_ = size_ - 1;
}


Fibonacci::~Fibonacci()
{
	delete[] fib_;
	fib_ = nullptr;
}


int Fibonacci::Get() const
{
	return fib_[position_];
}


void Fibonacci::Prev()
{
	if (position_ == 0)
		return;
	else
		position_--;
}


