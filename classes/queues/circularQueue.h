/******************************************************
* Author:		Marc Penalosa
* Filename:		circularQueue.h
* Date Created:	1/27/26
******************************************************/

#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "array.h"
#include "exception.h"

template<typename T>
class CircularQueue
{
public:
	CircularQueue();
	CircularQueue(int size);
	CircularQueue(const CircularQueue& copy);
	CircularQueue(CircularQueue&& copy) noexcept;
	CircularQueue& operator=(const CircularQueue& rhs);
	CircularQueue& operator=(CircularQueue&& rhs) noexcept;
	~CircularQueue();

	int getSize() const;
	bool isEmpty() const;
	bool isFull() const;
	void Enqueue(T data);
	T Dequeue();
	T Peek() const;
private:
	Array<T> m_queue;
	int m_size;
	int m_head;	// index of the head
	int m_tail;	// index of the tail. Points to an empty space in the array
};

template<typename T>
CircularQueue<T>::CircularQueue() : m_size(0), m_head(-1), m_tail(-1)
{
}

template<typename T>
CircularQueue<T>::CircularQueue(int size) : m_queue(Array<T>(size)), m_size(size), m_head(-1), m_tail(-1)
{
}

template<typename T>
CircularQueue<T>::CircularQueue(const CircularQueue& copy) : m_queue(copy.m_queue), m_size(copy.m_size), m_head(copy.m_head), m_tail(copy.m_tail)
{
}

template<typename T>
CircularQueue<T>::CircularQueue(CircularQueue&& copy) noexcept : m_queue(std::move(copy.m_queue)), m_size(copy.m_size), m_head(copy.m_head), m_tail(copy.m_tail)
{
	// Reset variables to default
	copy.m_size = 0;
	copy.m_head = -1;
	copy.m_tail = -1;
}

template<typename T>
CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue& rhs)
{
	if (this != &rhs)
	{
		// delegate copy assignment to Array
		m_queue = rhs.m_queue;
		m_size = rhs.m_size;
		m_head = rhs.m_head;
		m_tail = rhs.m_tail;
	}

	return *this;
}

template<typename T>
CircularQueue<T>& CircularQueue<T>::operator=(CircularQueue&& rhs) noexcept
{
	if (this != &rhs)
	{
		// delegate move assignment to Array
		m_queue = std::move(rhs.m_queue);
		m_size = rhs.m_size;
		m_head = rhs.m_head;
		m_tail = rhs.m_tail;

		// reset rhs variables to default values
		rhs.m_size = 0;
		rhs.m_head = -1;
		rhs.m_tail = -1;
	}

	return *this;
}

template<typename T>
CircularQueue<T>::~CircularQueue()
{
	m_size = 0;
	m_head = -1;
	m_tail = -1;
}

template<typename T>
int CircularQueue<T>::getSize() const
{
	return m_size;
}

template<typename T>
bool CircularQueue<T>::isEmpty() const
{
	// if m_head is -1, it means that the Queue is empty
	// m_head (and m_tail) is always reset to -1 when the last element is dequeued
	return (m_head == -1);
}

template<typename T>
bool CircularQueue<T>::isFull() const
{
	bool full = false;

	// if the Queue was never empty to begin with, and tail caught up to head
	if (m_head != -1 && (m_head == (m_tail + 1) % m_size))
		full = true;

	return full;
}

template<typename T>
void CircularQueue<T>::Enqueue(T data)
{
	if (isFull())
		throw Exception("Queue is full");

	// if head never moved
	if (m_head == -1)
	{
		m_head = 0;
		m_tail = 0;
	}
	else
	{
		// this formula sets the tail to the next index, and circling to 0 if m_size is hit
		m_tail = (m_tail + 1) % m_size;
	}
	m_queue[m_tail] = data;
}

template<typename T>
T CircularQueue<T>::Dequeue()
{
	if (isEmpty())
		throw Exception("Queue is empty");

	T result = m_queue[m_head];

	// Reset the current value before moving
	m_queue[m_head] = T();
	
	// if there's only one element, reset both the head and tail to -1
	if (m_head == m_tail)
	{
		m_head = -1;
		m_tail = -1;
	}
	else
	{
		// this formula sets the tail to the next index, and circling to 0 if m_size is hit
		m_head = (m_head + 1) % m_size;
	}

	return result;
}

template<typename T>
T CircularQueue<T>::Peek() const
{
	if (isEmpty())
		throw Exception("Queue is empty");

	return m_queue[m_head];
}

#endif // !CIRCULAR_QUEUE_H