/******************************************************
* Author:		Marc Penalosa
* Filename:		row.h
* Date Created:	1/10/26
* Modified:		1/15/26
*					- modified class for const correctness
******************************************************/

#ifndef ROW_H
#define ROW_H

template<typename T>
class Array2D;

/************************************************************************************************
* Class: Row
*
* Purpose:
*		This class allows the Array2D class to perform a [][] operation by
*			using this class's [] operator to return a T&
*
* Manager Functions:
*		Row(Array2D<T>& array2D, int row)
*			Takes an Array2D<T>& and sets the row, so that the opreator[] overload can be used
*
* Methods:
*		T& operator[](int column)
*			Calls Array2D::Select to select a T in m_array similar to [][]
*		const T& operator[](int column) const
************************************************************************************************/
template<typename T>
class Row
{
	friend class Array2D<T>;
public:
	int m_row;

	Row(Array2D<T>& array2D, int row);
	T& operator[](int column);
	const T& operator[](int column) const;
private:
	Array2D<T>& m_array2D;
};

template<typename T>
Row<T>::Row(Array2D<T>& array2D, int row) : m_array2D(array2D), m_row(row)
{
}

/*
* Purpose:
*		Calls the function Array2D::Select to return a T&
* Precondition:
*		Array2D is defined
* Postcondition:
*		Returns an address of a T in Array2D's m_array
*/
template<typename T>
T& Row<T>::operator[](int column)
{
	return m_array2D.Select(m_row, column);
}

template<typename T>
const T& Row<T>::operator[](int column) const
{
	return m_array2D.Select(m_row, column);
}
#endif // !ROW_H