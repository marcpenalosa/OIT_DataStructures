/******************************************************
* Author:		Marc Penalosa
* Filename:		exception.h
* Date Created:	1/6/26
* Modified:		1/7/26 - modified ostream to not use friends
******************************************************/

#ifndef EXCEPTION
#define EXCEPTION

#define _CRT_SECURE_NO_WARNINGS

#include <ostream>
using std::ostream;

/**************************************************************************
* Class: Exception
* 
* Purpose: This class provides an implementation of exception handling
* 
* Manager Functions:
*		Exception()
*			The default msg is a nullptr
*		Exception(const char* msg)
*			Creates an Exception instance with the given msg set
*		Exception(const Exception& copy)
*		Exception& operator=(const Exception& rhs)
*		Exception& operator=(Exception&& rhs) noexcept
*		~Exception()
**************************************************************************/

class Exception
{
public:
	Exception();
	Exception(const char* msg);
	Exception(const Exception& copy);
	Exception(Exception&& copy) noexcept;
	Exception& operator=(const Exception& rhs);
	Exception& operator=(Exception&& rhs) noexcept;
	~Exception();
	const char* getMessage() const;
	void setMessage(const char* msg);
private:
	char* m_msg;
};

ostream& operator<<(ostream& stream, const Exception& except);

#endif // !EXCEPTION