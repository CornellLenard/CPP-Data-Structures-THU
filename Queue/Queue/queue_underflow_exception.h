/*********************************************************************************

  * FileName:       queue_underflow_exception.h
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The header file for the class QueueUnderflowException
  * Project:        The Data Structures - Queue
  * Reference:      THU Data Structures

**********************************************************************************/


#pragma once


#include <exception>


class QueueUnderflowException: public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "dequeue() and getFront() cannot called by an empty Queue !";
	}
};


