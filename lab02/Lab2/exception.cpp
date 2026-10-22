/******************************************************
* Author:		Marc Penalosa
* Filename:		exception.cpp
* Date Created:	1/6/26
* Modified:		1/7/26 - modified the ostream to not use friends
******************************************************/

#include "Exception.h"

Exception::Exception() : m_msg(nullptr)
{
}

Exception::Exception(const char* msg) : m_msg(nullptr)
{
	if (msg != nullptr)
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}

Exception::Exception(const Exception& copy) : m_msg(nullptr)
{
	if (copy.m_msg != nullptr)
	{
		delete m_msg;
		m_msg = new char[strlen(copy.m_msg) + 1];
		strcpy(m_msg, copy.m_msg);
	}
}

Exception::Exception(Exception&& copy) noexcept : m_msg(std::move(copy.m_msg))
{
	copy.m_msg = nullptr;
}

Exception& Exception::operator=(const Exception& rhs)
{
	// Self-check
	if (this != &rhs)
	{
		// Delete the current m_msg (if any. deleting nullptr is fine I think)
		delete m_msg;

		if (rhs.m_msg != nullptr)
		{
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy(m_msg, rhs.m_msg);
		}
	}
	return *this;
}

Exception& Exception::operator=(Exception&& rhs) noexcept
{
	if (this != &rhs)
	{
		delete m_msg;
		m_msg = std::move(rhs.m_msg);
		rhs.m_msg = nullptr;
	}
	return *this;
}

Exception::~Exception()
{
	delete m_msg;
	m_msg = nullptr;
}

/*
* Purpose:
*		This function gets the const char* member variable m_msg.
* Precondition:
*		Exception must be declared.
* Postcondition:
*		Returns the const char* member variable m_msg.
*/
const char* Exception::getMessage() const
{
	return m_msg;
}

/*
* Purpose:
*		This functions sets the member variable m_msg
* Precondition:
*		Exception must be declared.
* Postcondition:
*		Returns nothing.
*		Sets the member varaible m_msg to a different char string. Set it to nullptr if the given msg is nullptr.
*/
void Exception::setMessage(const char* msg)
{
	if (msg != nullptr)
	{
		delete m_msg;
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
	else
	{
		m_msg = nullptr;
	}
}

/*
* Purpose:
*		Overloads the << so that Exception can be used in an ostream
* Precondition:
*		Exception must be declared.
* Postoncidion:
*		Calls the Exception::getMessage() function.
*		Returns an ostream&
*/
ostream& operator<<(ostream& stream, const Exception& except)
{
	return stream << except.getMessage();
}
