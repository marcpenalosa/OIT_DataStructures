/******************************************************
* Author:		Marc Penalosa
* Filename:		array2D.h
* Date Created:	1/10/26
* Modified:		1/13/26
*					- changed m_array to be of type T** instead of Array<T>
******************************************************/

#ifndef ARRAY_2D_H
#define ARRAY_2D_H

#include "exception.h"
#include "row.h"
#include <iostream>

/************************************************************
* Class: Array2D
* 
* Purpose:
*		Creates a 2D Array that allows the client to get its number of Rows and Columns,
*			while also being able to set it.
*			
* Manager Functions:
*		Array2D()
*			Sets the m_array to nullptr while setting the m_rows and m_columns to 0
*		Array2D(int rows, int columns)
*			Allocates the space for rows, then allocates the space for columns for each rows,
*			then sets the m_rows and m_columns with the given rows and columns respectively
*		Array2D(const Array2D& copy)
*		Array2D(Array2D&& copy) noexcept
*		Array2D& operator=(const Array2D& rhs)
*		Array2D& operator=(Array2D&& rhs) noexcept
*		~Array2D()
*
* Methods:
*		int getRows() const
*		int getColumns() const
*		void setRows(int rows)
*			Sets a new number of rows. If it's bigger, copy data and reallocate more space
*			If lesser, copy data and reallocate only up to that point and lose data
*		void setColumns(int columns)
*			Sets a new number of columns. If it's bigger, copy data and reallocate more space
*			If lesser, copy data and reallocate only up to that point and lose data
*		Row<T> operator[](int row)
*			Extends access to Row class to be able to perform [][]
*		const Row<T> operator[](int row) const
*		T& Select(int desired_row, int desired_column)
*			Returns the address of a T in m_array
*		const T& Select(int desired_row, int desired_column) const
************************************************************/

template<typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int rows, int columns);
	Array2D(const Array2D& copy);
	Array2D(Array2D&& copy) noexcept;
	Array2D& operator=(const Array2D& rhs);
	Array2D& operator=(Array2D&& rhs) noexcept;
	~Array2D();

	int getRows() const;
	int getColumns() const;
	void setRows(int rows);
	void setColumns(int columns);
	Row<T> operator[](int row);
	const Row<T> operator[](int row) const;
	T& Select(int desired_row, int desired_column);
	const T& Select(int desired_row, int desired_column) const;
	
private:
	T** m_array;
	int m_rows;
	int m_columns;
};

template<typename T>
Array2D<T>::Array2D() : m_array(nullptr), m_rows(0), m_columns(0)
{
}

template<typename T>
Array2D<T>::Array2D(int rows, int columns) : m_array(nullptr), m_rows(rows), m_columns(columns)
{
	// Allocate Rows
	m_array = new T * [rows];
	// Allocate Columns
	for (int i = 0; i < rows; i++)
	{
		m_array[i] = new T[columns];
	}
}

template<typename T>
Array2D<T>::Array2D(const Array2D& copy) : m_array(nullptr), m_rows(copy.m_rows), m_columns(copy.m_columns)
{
	// Allocate Rows
	m_array = new T * [m_rows];
	for (int i = 0; i < m_rows; i++)
	{
		// Allocate Columns
		m_array[i] = new T[m_columns]; 
		for (int j = 0; j < m_columns; j++)
		{
			// Copy contents
			m_array[i][j] = copy.m_array[i][j];
		}
	}
}

template<typename T>
Array2D<T>::Array2D(Array2D&& copy) noexcept : m_array(std::move(copy.m_array)), m_rows(copy.m_rows), m_columns(copy.m_columns)
{
	copy.m_array = nullptr;
}

template<typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D& rhs)
{
	if (this != &rhs)
	{
		// Delete the contents of the array
		for (int i = 0; i < m_rows; i++)
		{
			delete[] m_array[i];
		}
		// Delete the array itself
		delete[] m_array;

		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;

		// Allocate Rows
		m_array = new T * [m_rows];
		for (int i = 0; i < m_rows; i++)
		{
			// Allocate Columns
			m_array[i] = new T[m_columns];
			for (int j = 0; j < m_columns; j++)
			{
				// Copy contents
				m_array[i][j] = rhs.m_array[i][j];
			}
		}
	}

	return *this;
}

template<typename T>
Array2D<T>& Array2D<T>::operator=(Array2D&& rhs) noexcept
{
	if (this != rhs)
	{
		m_array = std::move(rhs.m_array);
		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;

		rhs.m_array = nullptr;
	}

	return *this;
}

template<typename T>
Array2D<T>::~Array2D()
{
	// Delete the contents of the array
	for (int i = 0; i < m_rows; i++)
	{
		delete[] m_array[i];
	}
	// Delete the array itself
	delete[] m_array;

	m_array = nullptr;
	m_rows = 0;
	m_columns = 0;
}

/*
* Purpose:
*		Gets the number of rows
* Precondition:
*		Array2D is defined
* Postcondition:
*		Returns the number of int m_rows
*/
template<typename T>
int Array2D<T>::getRows() const
{
	return m_rows;
}

/*
* Purpose:
*		Gets the number of columns
* Precondition:
*		Array2D is defined
* Postcondition:
*		Returns the number of int m_columns
*/
template<typename T>
int Array2D<T>::getColumns() const
{
	return m_columns;
}

/*
* Purpose:
*		Sets the number of rows of a 2D Array
* Precondition:
*		Array2D is defined
* Postcondition:
*		Returns nothing
*		Modifies the Array2D
*			- If the new number of rows is less than the original's, you lose data
*			- Else, a bigger size is allocated without data loss
*/
template<typename T>
void Array2D<T>::setRows(int rows)
{
	// allocate temp resource with new length
	T** temp = nullptr;
	temp = new T * [rows];
	for (int i = 0; i < rows; i++)
		temp[i] = new T[m_columns];

	// copy contents of m_array to temp
	for (int i = 0; i < m_rows && i < rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
			temp[i][j] = m_array[i][j];
	}

	m_rows = rows;
	m_array = temp;
}

/*
* Purpose:
*		Sets the number of columns of a 2D Array
* Precondition:
*		Array2D is defined
* Postcondition:
*		Returns nothing
*		Modifies the Array2D
*			- If the new number of columns is less than the original's, you lose data
*			- Else, a bigger size is allocated without data loss
*/
template<typename T>
void Array2D<T>::setColumns(int columns)
{
	// allocate temp resource with new length
	T** temp = nullptr;
	temp = new T * [m_rows];
	for (int i = 0; i < m_rows; i++)
		temp[i] = new T[columns];

	// copy content of m_array to temp
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns && j < columns; j++)
			temp[i][j] = m_array[i][j];
	}

	m_columns = columns;
	m_array = temp;
}

/*
* Purpose:
*		Overloads the operator[] to return a Row<T>
* Precondition:
*		Array2D is defined
*		Given row must not go out of bounds
* Postcondition:
*		Returns a Row<T>
*/
template<typename T>
Row<T> Array2D<T>::operator[](int row)
{
	// NOTE TO SELF: you can only call const methods from const objects

	if (row < 0 || row >= m_rows)
		throw Exception("Out of bounds\n");

	// extends access to Row class and using its operator[] overload
	// which Row would then call Array2D<T>::Select
	return Row<T>(*this, row);
}

// const compliant operator[]
template<typename T>
const Row<T> Array2D<T>::operator[](int row) const
{
	if (row < 0 || row >= m_rows)
		throw Exception("Out of bounds\n");

	return Row<T>(const_cast<Array2D<T>&>(*this), row);
}

/*
* Purpose:
*		Selects the address of a T in m_array
* Precondition:
*		Array2D is defined
*		Desired destination must not go out of bounds
* Postcondition:
*		Returns the address of a T in m_array
*/
template<typename T>
T& Array2D<T>::Select(int desired_row, int desired_column)
{
	if (desired_row < 0 || desired_row >= m_rows || desired_column < 0 || desired_column >= m_columns)
		throw Exception("Out of bounds\n");

	return m_array[desired_row][desired_column];
}

// const compliant Select
template<typename T>
const T& Array2D<T>::Select(int desired_row, int desired_column) const
{
	if (desired_row < 0 || desired_row >= m_rows || desired_column < 0 || desired_column >= m_columns)
		throw Exception("Out of bounds\n");

	return m_array[desired_row][desired_column];
}
#endif // !ARRAY_2D_H