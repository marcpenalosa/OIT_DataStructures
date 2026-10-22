/******************************************************
* Author:		Marc Penalosa
* Filename:		array.h
* Date Created:	1/6/26
* Modified:		1/7/26 - modified name casings to follow CST Style Guide 2015
******************************************************/

#ifndef ARRAY
#define ARRAY

#include "Exception.h"

/*****************************************************************************************************************
* Class: Array
* 
* Purpose: Creates a 1D Array than allows the client to set its length and its starting index
* 
* Manager Functions:
*		Array()
*			An instance of an array with an array that's set to nullptr, start index to 0, and length of 0
*		Array(int length, int start_index = 0)
*			Creates an instance of an array that allocates enough space with the given length, and defaults
*			the starting index to 0 if it is left unspecified
*		Array(const Array<T>& copy)
*		Array(Array<T>&& copy)
*		Array& operator = (const Array<T>&& rhs)
*		Array& operator = (Array<T>& rhs)
*		~Array()
*****************************************************************************************************************/
template <typename T>
class Array {
public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array<T>& copy);
	Array(Array<T>&& copy);
	Array& operator = (const Array<T>& rhs);
	Array& operator = (Array<T>&& rhs);
	~Array();
	T& operator [] (int index);
	int getStartIndex();
	void setStartIndex(int start_index);
	int getLength();
	void setLength(int length);
private:
	T* m_array;
	int m_start_index;
	int m_length;
};

template<typename T>
Array<T>::Array() : m_array(nullptr), m_start_index(0), m_length(0)
{
}

template<typename T>
Array<T>::Array(int length, int start_index) : m_array(nullptr), m_start_index(start_index), m_length(length)
{
	m_array = new T[m_length];
}

template<typename T>
Array<T>::Array(const Array<T>& copy) : m_array(nullptr), m_start_index(copy.m_start_index), m_length(copy.m_length)
{
	m_array = new T[m_length];
	for (int i = 0; i < m_length; i++)
	{
		m_array[i] = copy.m_array[i];
	}
}

template<typename T>
Array<T>::Array(Array<T>&& copy) : m_array(std::move(copy.m_array)), m_start_index(copy.m_start_index), m_length(copy.m_length)
{
	copy.m_array = nullptr;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
	// self reference check
	if (this != &rhs)
	{
		// de-allocate then check if rhs is nullptr
		delete[] m_array;
		if (rhs.m_array != nullptr)
		{
			m_array = new T[rhs.m_length];
			for (int i = 0; i < rhs.m_length; i++)
			{
				m_array[i] = rhs.m_array[i];
			}
		}
		else
		{
			m_array = nullptr;
		}
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;
	}
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& rhs)
{
	if (this != &rhs)
	{
		delete[] m_array;
		m_array = std::move(rhs.m_array);
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;

		rhs.m_array = nullptr;
	}
	return *this;
}

template<typename T>
Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

template<typename T>
T& Array<T>::operator[](int index)
{
	if (m_array == nullptr)
		throw Exception("m_array is empty\n");
	if (index < 0 - m_start_index)
		throw Exception("Out-of-range lower bounds\n");
	if (index >= m_length + m_start_index)
		throw Exception("Out-of-range upper bounds\n");
	return m_array[index - m_start_index];
}

/*
* Purpose:
*		This function returns an int that represents the starting index.
* Precondition:
*		None.
* Postcondition:
*		Returns the integer member variable m_start_index.
*/
template<typename T>
int Array<T>::getStartIndex()
{
	return m_start_index;
}

/*
* Purpose:
*		This function sets the starting index of the array. In other words, instead of the usual
*		starting index of 0, it can be set to 1 or any other number (even negative numbers).
* Precondition:
*		None.
* Postcondition:
*		Returns nothing.
*		Sets the integer member variable m_start_index.
*/
template<typename T>
void Array<T>::setStartIndex(int start_index)
{
	m_start_index = start_index;
}

/*
* Purpose:
*		This function returns the length of the m_array.
* Precondition:
*		Array length must be initialized.
*		Length must be non-negative
* Postcondition:
*		Returns the int member variable m_length
*/
template<typename T>
int Array<T>::getLength()
{
	return m_length;
}

/*
* Purpose:
*		This function sets the length of the array. If the given length is smaller than the current
*		length, data will be lost.
* Precondition:
*		Array must be initialized.
*		Length must be non-negative
* Postcondition:
*		Returns nothing.
*		Modifies the array such that it allocates either a smaller or larger space, keeping the integrity
*		of the data, unless the given length is smaller than the current length (which then data loss will occur).
*/
template<typename T>
void Array<T>::setLength(int length)
{
	if (length < 0)
	{
		throw Exception("SetLength index is smaller than lower bound\n");
	}
	
	// Copy contents of m_array into a temp buffer
	T* temp = new T[m_length];
	for (int i = 0; i < m_length; i++)
	{
		temp[i] = m_array[i];
	}
	// Delete the old array, allocate new length, then copy back its contents
	delete[] m_array;
	m_array = new T[length];
	
	// if setLength is smaller than original m_length, set it now
	// to avoid overflow
	if (length < m_length)
		m_length = length;
	for (int i = 0; i < m_length; i++)
	{
		m_array[i] = temp[i];
	}
	m_length = length;
	delete[] temp;
}

#endif // !ARRAY