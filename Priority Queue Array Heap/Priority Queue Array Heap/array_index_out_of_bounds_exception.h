/*********************************************************************************

  * FileName:       array_index_out_of_bounds_exception.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class ArrayIndexOutOfBoundsException
  * Project:        The Data Structures - Priority Queue Array Heap
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <exception>


class ArrayIndexOutOfBoundsException: public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "The given index is out of bounds !";
	}
};


