/*******************************************
* Author:			Marc Penalosa
* Filename:			bsNode.h
* Date Created:		2/02/26
*******************************************/

#ifndef BS_NODE_H
#define BS_NODE_H

enum BalanceFactor
{
	LH = 1,
	EH = 0,
	RH = -1
};

template<typename T>
class BSTree;

/*
* Class: BSNode
* 
* Purpose:
*		Creates a Node for a Binary Search Tree
* 
* Manager Functions:
*		BSNode()
*			Sets all member variables to their default values. The default T for m_data and nullptrs to m_left and m_right
*		BSNode(T data)
*			Sets the m_data member variable to the given data parameter. Sets m_left and m_right to nullptr
*		BSNode(const BSNode& copy)
*		BSNode(BSNode&& copy) noexcept
*		BSNode& operator=(const BSNode& rhs)
*		BSNode& operator=(BSNode&& rhs) noexcept
*		~BSNode()
*/
template<typename T>
class BSNode
{
	friend class BSTree<T>;
private:
	BSNode();
	BSNode(T data);
	BSNode(const BSNode& copy);
	BSNode(BSNode&& copy) noexcept;
	BSNode& operator=(const BSNode& rhs);
	BSNode& operator=(BSNode&& rhs) noexcept;
	~BSNode();

	T m_data;
	BSNode<T>* m_left;
	BSNode<T>* m_right;
	int m_bal;
};

template<typename T>
BSNode<T>::BSNode() : m_data{}, m_left(nullptr), m_right(nullptr), m_bal(0)
{
}

template<typename T>
BSNode<T>::BSNode(T data) : m_data(data), m_left(nullptr), m_right(nullptr), m_bal(0)
{
}

template<typename T>
BSNode<T>::BSNode(const BSNode& copy) : m_data(copy.m_data), m_left(nullptr), m_right(nullptr), m_bal(0)
{
}

template<typename T>
BSNode<T>::BSNode(BSNode&& copy) noexcept : m_data(std::move(copy.m_data)), m_left(nullptr), m_right(nullptr), m_bal(0)
{
}

template<typename T>
BSNode<T>& BSNode<T>::operator=(const BSNode& rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_left = nullptr;
		m_right = nullptr;
	}
	return *this;
}

template<typename T>
BSNode<T>& BSNode<T>::operator=(BSNode&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_data = std::move(rhs.m_data);
		m_left = nullptr;
		m_right = nullptr;

		rhs.m_data = T();
	}
	return *this;
}

template<typename T>
BSNode<T>::~BSNode()
{
	m_data = T();
	m_left = nullptr;
	m_right = nullptr;
	m_bal = 0;
}

#endif // !BS_NODE_H