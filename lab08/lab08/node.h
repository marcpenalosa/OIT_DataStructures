/********************************************************
* Author:			Marc Penalosa
* Filename:			node.h
* Date Created:		1/8/26
* Modified:			1/26/26 - Fixed move operator= not returning *this
*							- Fixed move operator= resetting to 0 instead of T()
********************************************************/

#ifndef NODE_H
#define NODE_H

template <typename T>
class List;

/**************************************************************************
* Class: Node
*
* Purpose: This class provides a way to make Nodes for a Double-Linked List
*
* Manager Functions:
*		Node();
*			Initializes the data to default T(), while setting the next and prev pointers to nullptr
*		Node(T data);
*			Sets the m_data to the given input, while setting the next and prev pointers to nullptr
*		Node(const Node& copy);
*		Node(Node&& copy) noexcept;
*		Node<T>& operator=(const Node& rhs);
*		Node<T>& operator=(Node&& rhs) noexcept;
*		~Node();
**************************************************************************/

template <typename T>
class Node {
	friend class List<T>;
private:
	T m_data;
	Node<T>* m_next;
	Node<T>* m_prev;

	Node();
	Node(T data);
	Node(const Node<T>& copy);
	Node(Node<T>&& copy) noexcept;
	Node<T>& operator=(const Node<T>& rhs);
	Node<T>& operator=(Node<T>&& rhs) noexcept;
	~Node();
};

template<typename T>
Node<T>::Node() : m_data(T()), m_next(nullptr), m_prev(nullptr)
{
}

template<typename T>
Node<T>::Node(T data) : m_data(data), m_next(nullptr), m_prev(nullptr)
{
}

template<typename T>
Node<T>::Node(const Node<T>& copy) : m_data(copy.m_data), m_next(nullptr), m_prev(nullptr)
{
}

template<typename T>
Node<T>::Node(Node<T>&& copy) noexcept : m_data(std::move(copy.m_data)), m_next(nullptr), m_prev(nullptr)
{
}

template<typename T>
Node<T>& Node<T>::operator=(const Node<T>& rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = nullptr;
		m_prev = nullptr;
	}
	return *this;
}

template<typename T>
Node<T>& Node<T>::operator=(Node<T>&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_data = std::move(rhs.m_data);
		m_next = nullptr;
		m_prev = nullptr;

		rhs.m_data = T();
	}

	return *this;
}

template<typename T>
Node<T>::~Node()
{
	m_data = T();
	m_next = nullptr;
	m_prev = nullptr;
}

#endif // !NODE_H