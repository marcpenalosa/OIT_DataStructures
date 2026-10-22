/*******************************************
* Author:			Marc Penalosa
* Filename:			stack.h
* Date Created:		1/25/26
*******************************************/

#ifndef STACK_H
#define STACK_H

#include "list.h"
#include "exception.h"

/*
* Class: Stack
* 
* Purpose:
*		Creates a templated List-Based Stack class
* 
* Manager Functions:
*		Stack()
*			Calls the default List ctor and sets the num_elements to 0
*		Stack(const Stack& copy)
*		Stack(Stack&& copy) noexcept
*		Stack& operator=(const Stack& rhs)
*		Stack& operator=(Stack&& rhs) noexcept
*		~Stack()
* 
* Methods:
*		int getNumElements() const
*		bool isEmpty() const
*		void Push(T data)
*			Pushes data at the top of the stack
*		T Pop()
*			Pops the data at the top of the stack and return its content
*		T Peek() const
*			Return the contents at the tops of the stack without popping
*/

template<typename T>
class Stack
{
public:
	Stack();
	Stack(const Stack& copy);
	Stack(Stack&& copy) noexcept;
	Stack& operator=(const Stack& rhs);
	Stack& operator=(Stack&& rhs) noexcept;
	~Stack();

	int getNumElements() const;
	bool isEmpty() const;
	void Push(T data);
	T Pop();
	T Peek() const;
private:
	List<T> m_stack;
	int num_elements;	// named num_elements per lab writeup
};

template<typename T>
Stack<T>::Stack() : m_stack(List<T>()), num_elements(0)
{
}

template<typename T>
Stack<T>::Stack(const Stack& copy) : m_stack(copy.m_stack), num_elements(copy.num_elements)
{
}

template<typename T>
Stack<T>::Stack(Stack&& copy) noexcept : m_stack(std::move(copy.m_stack)), num_elements(copy.num_elements)
{
	copy.num_elements = 0;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	// self reference check
	if (this != &rhs)
	{
		// delegate operator to List
		m_stack = rhs.m_stack;
		num_elements = rhs.num_elements;
	}
	
	return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& rhs) noexcept
{
	if (this != &rhs)
	{
		// delegate operator to List
		m_stack = std::move(rhs.m_stack);
		num_elements = rhs.num_elements;

		// reset rhs to default
		rhs.num_elements = 0;
	}

	return *this;
}

template<typename T>
Stack<T>::~Stack()
{
	num_elements = 0;
}

template<typename T>
int Stack<T>::getNumElements() const
{
	return num_elements;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	// Is the number of elements 0 or less somehow
	return (num_elements <= 0) ? true : false;
}

/*
* Purpose:
*		Pushes data at the top of the stack
* Precondition:
*		None
* Postcondition:
*		Pushes data at the top of the stack
*/
template<typename T>
void Stack<T>::Push(T data)
{
	m_stack.Append(data);
	num_elements++;
}

/*
* Purpose:
*		Pops the data at the top of the stack and return its content
* Precondition:
*		Stack must not be empty
* Postcondition:
*		Pops the data at the top of the stack and return its content
*/
template<typename T>
T Stack<T>::Pop()
{
	if (num_elements <= 0)
		throw Exception("empty list");

	num_elements--;
	// I added a Pop function in my List so that it doesn't change the way my List's extract work (extracting the first data starting from the head)
	// I'm not sure if Todd allows this :)
	return m_stack.Pop();
}

/*
* Purpose:
*		Return the data at the top of the stack without popping
* Precondition:
*		Stack must not be empty
* Postcondition:
*		Return the data at the top of the stack
*/
template<typename T>
T Stack<T>::Peek() const
{
	// List has exception check for this too but catch it now
	if (num_elements == 0)
		throw Exception("stack is empty");
	return m_stack.Last();
}

#endif // !STACK_H