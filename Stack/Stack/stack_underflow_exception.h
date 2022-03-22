/*********************************************************************************

  * FileName:       stack_underflow_exception.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class StackUnderflowException
  * Project:        The Data Structures - Stack
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <exception>


class StackUnderflowException: public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "pop() and top() cannot called by an empty Stack !";
	}
};


