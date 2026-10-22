/******************************************************
* Author:			Marc Penalosa
* Filename:			queue.h
* Date Created:		1/27/26
******************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include "exception.h"

/******************************************************
* Class: Queue
* 
* Manager Functions:
*		Queue()
*			Calls the default Array ctor to set m_queue, and sets m_num_elements to 0
*		Queue(const Queue& copy)
*		Queue(Queue&& copy) noexcept
*		Queue& operator=(const Queue& rhs)
*		Queue& operator=(Queue&& rhs) noexcept
*		~Queue()
* 
* Methods:
*		int getNumElements() const
*		bool isEmpty() const
*		void Enqueue(T data)
*			Takes a data parameter to append a data at the end of the queue
*		T Dequeue()
*			Dequeues the data at the head and return its content
*		T Peek() const
*			Return the content of the head without dequeueing
******************************************************/
template<typename T>
class Queue
{
public:
	Queue();
	Queue(const Queue& copy);
	Queue(Queue&& copy) noexcept;
	Queue& operator=(const Queue& rhs);
	Queue& operator=(Queue&& rhs) noexcept;
	~Queue();

	int getNumElements() const;
	bool isEmpty() const;
	void Enqueue(T data);
	T Dequeue();
	T Peek() const;
private:
	List<T> m_queue;
	int m_num_elements;
};

template<typename T>
Queue<T>::Queue() : m_num_elements(0)
{
}

template<typename T>
Queue<T>::Queue(const Queue& copy) : m_queue(copy.m_queue), m_num_elements(copy.m_num_elements)
{
}

template<typename T>
Queue<T>::Queue(Queue&& copy) noexcept : m_queue(std::move(copy.m_queue)), m_num_elements(copy.m_num_elements)
{
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& rhs)
{
	if (this != &rhs)
	{
		// delegate assignment to List
		m_queue = rhs.m_queue;
		m_num_elements = rhs.m_num_elements;
	}

	return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& rhs) noexcept
{
	if (this != &rhs)
	{
		// delegate move to List
		m_queue = std::move(rhs.m_queue);
		m_num_elements = rhs.m_num_elements;

		// reset to default  values
		rhs.m_num_elements = 0;
	}

	return *this;
}

template<typename T>
Queue<T>::~Queue()
{
	m_num_elements = 0;
}

template<typename T>
int Queue<T>::getNumElements() const
{
	return m_num_elements;
}

template<typename T>
bool Queue<T>::isEmpty() const
{
	return (m_num_elements == 0);
}

/*
* Purpose:
*		Takes in a data as a parameter to append that data at the end of the queue
* Precondition:
*		None
* Postcondition:
*		Data is appended to the queue
*/
template<typename T>
void Queue<T>::Enqueue(T data)
{
	m_queue.Append(data);
	++m_num_elements;
}

/*
* Purpose:
*		Dequeues the head and return its content
* Precondition:
*		Queue must not be empty
* Postcondition:
*		Dequeues the head and return its content
*/
template<typename T>
T Queue<T>::Dequeue()
{
	if (m_num_elements == 0)
		throw Exception("Empty queue");

	T result = m_queue.First();
	m_queue.Extract(m_queue.First());
	--m_num_elements;

	return result;
}

/*
* Purpose:
*		Return the content of head without dequeueing
* Precondition:
*		Queue must not be empty
* Postcondition:
*		Return content of head
*/
template<typename T>
T Queue<T>::Peek() const
{
	if (m_num_elements == 0)
		throw Exception("Empty queue");

	return m_queue.First();
}

#endif // !QUEUE_H