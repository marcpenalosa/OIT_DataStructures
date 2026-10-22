/*******************************************
* Author:			Marc Penalosa
* Filename:			stack.h
* Date Created:		1/24/26
*******************************************/

#ifndef STACK_H
#define STACK_H

#include "array.h"
#include "exception.h"

/*
* Class: Stack
* 
* Purpose:
*		Creates a templated Stack class
* 
* Manager Functions:
*		Stack();
*			Calls Array default ctor, sets m_size and m_top to 0
*		Stack(int size);
*			Calls Array 2arg ctor, sets m_size to the given parameter, and sets m_top to 0
*		Stack(const Stack<T>& copy);
*		Stack(Stack<T>&& copy) noexcept;
*		Stack& operator=(const Stack<T>& rhs);
*		Stack& operator=(Stack<T>&& rhs) noexcept;
*		~Stack();
* 
* Methods:
*		int getNumElements() const;
*		int getSize() const;
*		bool isEmpty() const;
*		bool isFull() const;
*		void Push(T data);
*			Pushes data into the stack unless the Stack is full
*		T Pop();
*			Pops the top of the stack and returns its content
*		T Peek() const;
*			Returns the content at the top of the stack without popping
*		void setSize(int new_size);
*			Sets a new size to the Stack. Preserves data that is currently on the stack, but
*			data loss can occur if setting to a lesser size
*/
template <typename T>
class Stack
{
public:
	Stack();
	Stack(int size);
	Stack(const Stack<T>& copy);
	Stack(Stack<T>&& copy) noexcept;
	Stack& operator=(const Stack<T>& rhs);
	Stack& operator=(Stack<T>&& rhs) noexcept;
	~Stack();

	int getNumElements() const;
	int getSize() const;
	bool isEmpty() const;
	bool isFull() const;
	void Push(T data);
	T Pop();
	T Peek() const;
	void setSize(int new_size);
private:
	Array<T> m_stack;
	int m_size;	// size of the array
	int m_top;	// top of stack location
};

template<typename T>
Stack<T>::Stack() : m_stack(Array<T>()), m_size(0), m_top(0)
{
}

template<typename T>
Stack<T>::Stack(int size) : m_stack(Array<T>(size)), m_size(size), m_top(0)
{
	// Delagate size checking to Array
}

template<typename T>
Stack<T>::Stack(const Stack<T>& copy) : m_stack(copy.m_stack), m_size(copy.m_size), m_top(copy.m_top)
{
}

template<typename T>
Stack<T>::Stack(Stack<T>&& copy) noexcept : m_stack(std::move(copy.m_stack)), m_size(copy.m_size), m_top(copy.m_top)
{
	copy.m_size = 0;
	copy.m_top = 0;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
	// self reference check
	if (this != &rhs)
	{
		// delegate deallocation and reallocation to Array class
		m_stack = rhs.m_stack;
		m_size = rhs.m_size;
		m_top = rhs.m_top;
	}

	return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& rhs) noexcept
{
	// self reference check
	if (this != &rhs)
	{
		// delegate move op to Array class
		m_stack = std::move(rhs.m_stack);
		m_size = rhs.m_size;
		m_top = rhs.m_top;

		rhs.m_size = 0;
		rhs.m_top = 0;
	}

	return *this;
}

template<typename T>
Stack<T>::~Stack()
{
	m_size = 0;
	m_top = 0;
}

template<typename T>
int Stack<T>::getNumElements() const
{
	return m_top;
}

template<typename T>
int Stack<T>::getSize() const
{
	return m_size;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	// Is the top less than or equal to 0?
	return (m_top <= 0) ? true : false;
}

template<typename T>
bool Stack<T>::isFull() const
{
	// Is the top bigger than or equal to the size of the array?
	return (m_top >= m_size) ? true : false;
}

/*
* Purpose:
*		Pushes data at the top of the stack
* Precondition:
*		Stack must not be full
* Postcondition:
*		Pushes data at the top of the stack
*/
template<typename T>
void Stack<T>::Push(T data)
{
	if (isFull())
		throw Exception("full stack");

	m_stack[m_top] = data;
	m_top++;
}

/*
* Purpose:
*		Pops the data at the top of the stack and returns it
* Precondition:
*		Stack must not be empty
* Postcondition:
*		Pops the data at the top of the stack and returns that data
*/
template<typename T>
T Stack<T>::Pop()
{
	if (isEmpty())
		throw Exception("empty stack");

	m_top--;
	T result = m_stack[m_top];
	m_stack[m_top] = T{};	// reset to default value

	return result;
}

/*
* Purpose:
*		Returns the data at the top of the stack without popping
* Precondition:
*		Stack must not be empty
* Postcondition:
*		Returns the data at the top of the stack
*/
template<typename T>
T Stack<T>::Peek() const
{
	if (isEmpty())
		throw Exception("empty stack");

	return m_stack[m_top - 1];
}

/*
* Purpose:
*		Sets a new size for the stack while preserving its data integrity,
*		unless a lesser size is given
* Precondition:
*		The desired size must not be negative
* Postcondition:
*		Modifies the stack's size and preserving its data if it can
*/
template<typename T>
void Stack<T>::setSize(int new_size)
{
	if (new_size < 0)
		throw Exception("negative size");

	m_stack.setLength(new_size);
	m_size = new_size;
	if (m_top > new_size)
		m_top = new_size;
}

#endif // !STACK_H