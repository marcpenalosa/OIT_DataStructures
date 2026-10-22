/********************************************************
* Author:			Marc Penalosa
* Filename:			list.h
* Date Created:		1/8/26
* Modified:			1/10/26
						- Fixed pointers pointing to things already deleted
*						- Modified functions that were calling isEmpty() to instead check
*							if m_head is nullptr
********************************************************/

#ifndef LIST_H
#define LIST_H

#include "node.h"
#include "exception.h"

/**************************************************************************
* Class: List
*
* Purpose: This class provides a Double-Linked List ADT
*
* Manager Functions:
*		List();
*			An empty list where head and tail points to nullptr
*		List(const List& copy);
*		List(List&& copy) noexcept;
*		List<T>& operator=(const List& rhs);
*		List<T>& operator=(List&& rhs) noexcept;
*		~List();
**************************************************************************/

template <typename T>
class List {
public:
	List();
	List(const List<T>& copy);
	List(List&& copy) noexcept;
	List<T>& operator=(const List<T>& rhs);
	List<T>& operator=(List<T>&& rhs) noexcept;
	~List();

	Node<T>* getTail();
	Node<T>* getHead();
	void PrintForwards();
	void PrintBackwards();
	bool isEmpty();
	const T& First();
	const T& Last();
	void Prepend(const T& data);
	void Append(const T& data);
	void Purge();
	void Extract(const T& target);
	void InsertBefore(const T& new_data, const T& existing_data);
	void InsertAfter(const T& new_data, const T& existing_data);

private:
	Node<T>* m_head;
	Node<T>* m_tail;
};


template<typename T>
List<T>::List() : m_head(nullptr), m_tail(nullptr)
{
}

template<typename T>
List<T>::List(const List<T>& copy) : m_head(nullptr), m_tail(nullptr)
{
	if (copy.m_head != nullptr)
	{
		Node<T>* travel = copy.m_head;
		while (travel != nullptr)
		{
			Append(travel->m_data);
			travel = travel->m_next; // Traverse to next ptr
		}
	}
}

template<typename T>
List<T>::List(List<T>&& copy) noexcept : m_head(nullptr), m_tail(nullptr)
{
	if (copy.m_head != nullptr)
	{
		m_head = std::move(copy.m_head);
		m_tail = std::move(copy.m_tail);
		copy.m_head = nullptr;
		copy.m_tail = nullptr;
	}
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
	if (this != &rhs)
	{
		Purge();

		Node<T>* travel = rhs.m_head;
		while (travel != nullptr)
		{
			Append(travel->m_data);
			travel = travel->m_next;
		}
	}
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& rhs) noexcept
{
	if (this != &rhs)
	{
		Purge();

		m_head = std::move(rhs.m_head);
		m_tail = std::move(rhs.m_tail);
		rhs.m_head = nullptr;
		rhs.m_tail = nullptr;
	}
	return *this;
}

template<typename T>
List<T>::~List()
{
	Purge();
	m_head = nullptr;
	m_tail = nullptr;
}

/*
* Purpose:
*		This function gets the reference of the list's tail
* Precondition:
*		List must be declared
* Postcondition:
*		Returns the reference to the m_tail
*/
template<typename T>
Node<T>* List<T>::getTail()
{
	return m_tail;
}

/*
* Purpose:
*		This function gets the reference of the list's head
* Precondition:
*		List must be declared
* Postcondition:
*		Returns the reference to the m_head
*/
template<typename T>
Node<T>* List<T>::getHead()
{
	return m_head;
}

/*
* Purpose:
*		This function prints the data of the nodes, from head to tail
* Precondition:
*		List must be initialized
* Postcondition:
*		Returns nothing
*		Prints out the data in all the nodes to the console
*/
template<typename T>
void List<T>::PrintForwards()
{
	Node<T>* travel = m_head;
	while (travel != nullptr)
	{
		std::cout << travel->m_data << std::endl;
		travel = travel->m_next;
	}
}

/*
* Purpose:
*		This function prints the data of the nodes, from tail to head
* Precondition:
*		List must be initialized
* Postcondition:
*		Returns nothing
*		Prints out the data in all the nodes to the console
*/
template<typename T>
void List<T>::PrintBackwards()
{
	Node<T>* travel = m_tail;
	while (travel != nullptr)
	{
		std::cout << travel->m_data << std::endl;
		travel = travel->m_prev;
	}
}

/*
* Purpose:
*		This function determines if the list is empty
* Precondition:
*		List is declared
* Postcondition:
*		Returns a boolean
*/
template<typename T>
bool List<T>::isEmpty()
{
	bool result = true;
	if (m_head != nullptr)
		result = false;
	return result;
}

/*
* Purpose:
*		This function gets the data in the head pointer
* Precondition:
*		List is initialized
* Postcondition:
*		Returns the reference to the data of type T in a node
*/
template<typename T>
const T& List<T>::First()
{
	if (m_head == nullptr)
		throw Exception("List<T>::First - List is empty");
	return m_head->m_data;
}

/*
* Purpose:
*		This function gets the data in the tail pointer
* Precondition:
*		List is initialized
* Postcondition:
*		Returns the reference to the data of type T in a node
*/
template<typename T>
const T& List<T>::Last()
{
	if (m_head == nullptr)
		throw Exception("List<T>::Last - List is empty");
	return m_tail->m_data;
}

/*
* Purpose:
*		This function prepends the list with a node with using given data
* Precondition:
*		List is declared
* Postcondition:
*		Returns nothing
*		Modifies the list to prepend a node with a given data
*/
template<typename T>
void List<T>::Prepend(const T& data)
{
	Node<T>* newNode = new Node<T>(data);
	if (m_head == nullptr)	// if list is empty, set this node as the head and tail
	{
		m_head = newNode;
		m_tail = newNode;
	}
	else
	{
		newNode->m_next = m_head;
		m_head->m_prev = newNode;
		m_head = newNode;
	}
}

/*
* Purpose:
*		This function appends the list with a node using given data
* Precondition:
*		List is declared
* Postcondition:
*		Returns nothing
*		Modifies the list to append a node with a given data
*/
template<typename T>
void List<T>::Append(const T& data)
{
	Node<T>* newNode = new Node<T>(data);
	if (m_head == nullptr)	// if list is empty, set this node as the head and tail
	{
		m_head = newNode;
		m_tail = newNode;
	}
	else
	{
		newNode->m_prev = m_tail;
		m_tail->m_next = newNode;
		m_tail = newNode;
	}
}

/*
* Purpose:
*		This function deletes the entire list
* Precondition:
*		List is declared
* Postcondition:
*		Returns nothing
*		Deletes the list
*/
template<typename T>
void List<T>::Purge()
{
	m_tail = m_head;
	while (m_head != nullptr)
	{
		m_tail = m_head;
		m_head = m_head->m_next;
		delete m_tail;
	}
	m_head = nullptr;
	m_tail = nullptr;
}

/*
* Purpose:
*		Extracts the first node matching the given target data
* Precondition:
*		List must be initialized and not empty
*		Target data in the list must be known to exist, otherwise it will throw an exception
* Postcondition:
*		Returns nothing
*		Modifies the list to pop the first node with a matching target
*/
template<typename T>
void List<T>::Extract(const T& target)
{
	if (m_head == nullptr)
		throw Exception("List<T>::Extract - List is empty");
	Node<T>* travel = m_head;
	Node<T>* trail = nullptr;
	bool found = false;
	while (travel != nullptr && found == false)
	{
		if (travel->m_data == target)
		{
			if (travel == m_head)	// if this is the head
			{
				if (travel == m_tail)	// if this is the only thing in the list
				{
					m_head = nullptr;
					m_tail = nullptr;
					delete travel;
					travel = nullptr;
				}
				else
				{
					m_head = travel->m_next;
					m_head->m_prev = nullptr;
					delete travel;
					travel = m_head;
				}
			}
			else if (travel == m_tail)	// if this is the tail
			{
				m_tail = travel->m_prev;
				m_tail->m_next = nullptr;
				delete travel;
				travel = nullptr;
			}
			else
			{
				trail = travel->m_prev;
				trail->m_next = travel->m_next;
				trail = travel->m_next;
				trail->m_prev = travel->m_prev;
				delete travel;
				travel = trail;
			}
			found = true;
		}
		if (travel != nullptr)
			travel = travel->m_next;
	}
	if (found == false)
		throw Exception("List<T>::Extract - target not found\n");
}

/*
* Purpose:
*		Inserts a new node before an existing one, if the existing node matches a given data
* Precondition:
*		List must be initialized
*		Existing data must be known, otherwise throw an exception if data is not found
* Postcondition:
*		Returns nothing
*		Modifies the list to insert a new node before an existing target node
*/
template<typename T>
void List<T>::InsertBefore(const T& new_data, const T& existing_data)
{
	Node<T>* travel = m_head;
	Node<T>* trail = nullptr;
	bool found = false;
	while (travel != nullptr && found == false)
	{
		if (existing_data == travel->m_data)
		{
			if (travel == m_head)
			{
				Prepend(new_data);
			}
			else
			{
				Node<T>* newNode = new Node<T>(new_data);
				trail = travel->m_prev;
				newNode->m_prev = trail;
				newNode->m_next = travel;
				trail->m_next = newNode;
				travel->m_prev = newNode;
			}
			found = true;
		}
		travel = travel->m_next;
	}
	if (found == false)
		throw Exception("List<T>::InsertBefore - no match with existing_data");
}

/*
* Purpose:
*		Inserts a new node after an existing one, if the existing node matches a given data
* Precondition:
*		List must be initialized
*		Existing data must be known, otherwise throw an exception if data is not found
* Postcondition:
*		Returns nothing
*		Modifies the list to insert a new node after an existing target node
*/
template<typename T>
void List<T>::InsertAfter(const T& new_data, const T& existing_data)
{
	Node<T>* travel = m_head;
	Node<T>* trail = nullptr;
	bool found = false;
	while (travel != nullptr && found == false)
	{
		if (existing_data == travel->m_data)
		{
			if (travel == m_tail)
			{
				Append(new_data);
			}
			else
			{
				Node<T>* newNode = new Node<T>(new_data);
				travel = travel->m_next;
				trail = travel->m_prev;
				newNode->m_prev = trail;
				newNode->m_next = travel;
				trail->m_next = newNode;
				travel->m_prev = newNode;
			}
			found = true;
		}
		travel = travel->m_next;
	}
	if (found == false)
		throw Exception("List<T>::InsertAfter - no match with existing_data");
}

#endif // !LIST_H