/******************************************************
* Author:		Marc Penalosa
* Filename:		array2D.h
* Date Created:	1/10/26
* Modified:		1/15/26
*					- modified the class for const correctness
******************************************************/

#ifndef ARRAY_2D_H
#define ARRAY_2D_H

#include "array.h"
#include "row.h"

/************************************************************
* Class: Array2D
* 
* Purpose:
*		Creates a 2D Array that allows the client to get its number of Rows and Columns,
*			while also being able to set it.
*			
* Manager Functions:
*		Array2D()
*			Calls the default Array constructor to set its default
*			values while setting the m_rows and m_columns to 0
*		Array2D(int rows, int columns)
*			Calls the Array length arg constructor that allocates enough space for
*			rows * columns, while setting the m_rows and m_columns with the given rows
*			and columns respectively
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
*		const T& Select(int desired_row, int desired_column) const
*			Returns the address of a T in m_array
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
	Array<T> m_array;
	int m_rows;
	int m_columns;
};

template<typename T>
Array2D<T>::Array2D() : m_array(Array<T>()), m_rows(0), m_columns(0)
{
}

template<typename T>
Array2D<T>::Array2D(int rows, int columns) : m_array(Array<T>(rows * columns)), m_rows(rows), m_columns(columns)
{
}

template<typename T>
Array2D<T>::Array2D(const Array2D& copy) : m_array(copy.m_array), m_rows(copy.m_rows), m_columns(copy.m_columns)
{
}

template<typename T>
Array2D<T>::Array2D(Array2D&& copy) noexcept : m_array(std::move(copy.m_array)), m_rows(copy.m_rows), m_columns(copy.m_columns)
{
}

template<typename T>
Array2D<T>& Array2D<T>::operator=(const Array2D& rhs)
{
	if (this != &rhs)
	{
		m_array = rhs.m_array;
		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;
	}

	return *this;
}

template<typename T>
Array2D<T>& Array2D<T>::operator=(Array2D&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_array = std::move(rhs.m_array);
		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;
	}

	return *this;
}

template<typename T>
Array2D<T>::~Array2D()
{
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
	Array<T> temp(rows * m_columns);

	// copy contents of m_array to temp
	for (int i = 0; i < m_rows && i < rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
			temp[i * m_columns + j] = m_array[i * m_columns + j];
	}

	// call Array<T>::operator=
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
	Array<T> temp(m_rows * columns);

	// copy content of m_array to temp
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns && j < columns; j++)
			temp[i * columns + j] = m_array[i * m_columns + j];
	}

	// call Array<T>::operator=
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
	if (row < 0 || row >= m_rows)
		throw Exception("Out of bounds\n");

	// extends access to Row class and using its operator[] overload
	// which Row would then call Array2D<T>::Select
	return Row<T>(*this, row);
}

template<typename T>
const Row<T> Array2D<T>::operator[](int row) const
{
	// NOTE TO SELF: you can only call const methods from const objects

	if (row < 0 || row >= m_rows)
		throw Exception("Out of bounds\n");

	// extends access to Row class and using its operator[] overload
	// which Row would then call Array2D<T>::Select
	return Row<T>(const_cast<Array2D<T>&>(*this), row);
}

/*
* Purpose:
*		Selects the address of a T in m_array using the formula [desired_row * m_columns + desired_column]
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

	return m_array[desired_row * m_columns + desired_column];
}

template<typename T>
const T& Array2D<T>::Select(int desired_row, int desired_column) const
{
	if (desired_row < 0 || desired_row >= m_rows || desired_column < 0 || desired_column >= m_columns)
		throw Exception("Out of bounds\n");

	return m_array[desired_row * m_columns + desired_column];
}

#endif // !ARRAY_2D_H