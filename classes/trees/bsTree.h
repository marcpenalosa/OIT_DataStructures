/*******************************************
* Author:			Marc Penalosa
* Filename:			bsTree.h
* Date Created:		2/02/26
*******************************************/

#ifndef BS_TREE_H
#define BS_TREE_H

#include "bsNode.h"
#include "queue.h"
#include "exception.h"

/*
* Class: BSTree
* 
* Purpose:
*		Creates a Binary Search Tree that is able to traverse its nodes with various traversal functions, insert nodes,
*		delete nodes, and purge the entire tree itself
* 
* Manager Functions:
*		BSTree()
*		BSTree(const BSTree& copy)
*		BSTree(BSTree&& copy) noexcept
*		BSTree& operator=(const BSTree& rhs)
*		BSTree& operator=(BSTree&& rhs) noexcept
*		~BSTree()
* 
* Methods:
*		
*/
template<typename T>
class BSTree
{
public:
	BSTree();
	BSTree(const BSTree& copy);
	BSTree(BSTree&& copy) noexcept;
	BSTree& operator=(const BSTree& rhs);
	BSTree& operator=(BSTree&& rhs) noexcept;
	~BSTree();

	// These methods has to call private methods of themselves that take in the root
	// So that the private functions can recursively call themselves without exposing the root
	void Insert(T data);
	void Delete(T data);
	void Purge();
	int Height() const;
	void InOrder(void (*visit)(T data)) const;
	void PreOrder(void (*visit)(T data)) const;
	void PostOrder(void (*visit)(T data)) const;

	void BreadthFirst(void (*visit)(T data)) const;

private:
	void Insert(BSNode<T>*& cur, T data);
	void Delete(BSNode<T>*& parent, T data);
	void Purge(BSNode<T>*& cur);
	int Height(BSNode<T>* cur) const;
	void InOrder(BSNode<T>* cur, void (*visit)(T data)) const;
	void PreOrder(BSNode<T>* cur, void (*visit)(T data)) const;
	void PostOrder(BSNode<T>* cur, void (*visit)(T data)) const;

	BSNode<T>* CopyTree(BSNode<T>* cur) const;

	BSNode<T>* m_root;
};

template<typename T>
BSTree<T>::BSTree() : m_root(nullptr)
{
}

template<typename T>
BSTree<T>::BSTree(const BSTree& copy) : m_root(CopyTree(copy.m_root))
{
	// I was doing a BreadthFirst + Insert combo at first, but then realized the structure wasn't the same
	// Delegates the copying to a private function that ensures the tree's structure is the same
}

template<typename T>
BSTree<T>::BSTree(BSTree&& copy) noexcept : m_root(std::move(copy.m_root))
{
	copy.m_root = nullptr;
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& rhs)
{
	if (this != &rhs)
	{
		// Deallocate
		Purge();
		
		// Copy
		m_root = CopyTree(rhs.m_root);
	}

	return *this;
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(BSTree&& rhs) noexcept
{
	if (this != &rhs)
	{
		// Deallocate
		Purge();

		// Move
		m_root = std::move(rhs.m_root);

		// Reset rhs
		rhs.m_root = nullptr;
	}

	return *this;
}

template<typename T>
BSTree<T>::~BSTree()
{
	Purge();
}

/************************************************************************************************
* PUBLIC METHODS
************************************************************************************************/
template<typename T>
void BSTree<T>::Insert(T data)
{
	Insert(m_root, data);
}

template<typename T>
void BSTree<T>::Delete(T data)
{
	if (m_root == nullptr)
		throw Exception("tree is empty");

	BSNode<T>* cur = m_root;
	BSNode<T>* prev = cur;
	bool found = false;

	// Find the target node
	while (cur != nullptr && found == false)
	{
		if (cur->m_data == data)
		{
			found = true;
		}
		else
		{
			prev = cur;
			if (data < cur->m_data)
				cur = cur->m_left;
			else
				cur = cur->m_right;
		}
	}
	// At this point, assuming the data was found, cur should have the target data, prev should be the cur's parent 

	if (cur == nullptr)
		throw Exception("data not found");

	if (cur == prev)
		Delete(cur, data);
	else if (data < prev->m_data)
		Delete(prev->m_left, data);
	else
		Delete(prev->m_right, data);
}

template<typename T>
void BSTree<T>::Purge()
{
	if (m_root == nullptr)
		throw Exception("tree is empty");
	Purge(m_root);
}

template<typename T>
int BSTree<T>::Height() const
{
	if (m_root == nullptr)
		throw Exception("tree is empty");
	return Height(m_root);
}

template<typename T>
void BSTree<T>::InOrder(void(*visit)(T data)) const
{
	if (m_root == nullptr)
		throw Exception("tree is empty");
	InOrder(m_root, visit);
}

template<typename T>
void BSTree<T>::PreOrder(void(*visit)(T data)) const
{
	if (m_root == nullptr)
		throw Exception("tree is empty");
	PreOrder(m_root, visit);
}

template<typename T>
void BSTree<T>::PostOrder(void(*visit)(T data)) const
{
	if (m_root == nullptr)
		throw Exception("tree is empty");
	PostOrder(m_root, visit);
}

template<typename T>
void BSTree<T>::BreadthFirst(void(*visit)(T data)) const
{
	if (m_root == nullptr)
		throw Exception("tree is empty");

	// visit each node, from left to right, on each height before going on
	Queue<BSNode<T>*> queue;
	queue.Enqueue(m_root);
	BSNode<T>* temp;

	while (!queue.isEmpty())
	{
		temp = queue.Dequeue();
		visit(temp->m_data);
		if (temp->m_left != nullptr)
			queue.Enqueue(temp->m_left);
		if (temp->m_right != nullptr)
			queue.Enqueue(temp->m_right);
	}
}
/************************************************************************************************
* PRIVATE METHODS
************************************************************************************************/
template<typename T>
void BSTree<T>::Insert(BSNode<T>*& cur, T data)
{
	if (cur == nullptr)
	{
		cur = new BSNode<T>(data);
	}
	else if (data < cur->m_data)
	{
		Insert(cur->m_left, data);
	}
	else
	{
		Insert(cur->m_right, data);
	}
}

template<typename T>
void BSTree<T>::Delete(BSNode<T>*& parent, T data)
{
	// REMEMBER: parent is NOT the pointer to the Parent Node
	// parent is the m_left or m_right pointer of the Parent Node that contains the target data
	BSNode<T>* cur = parent;
	BSNode<T>* prev = nullptr;

	if (parent == nullptr)
		throw ("empty node");

	// Case 1 - Leaf Node
	if (cur->m_left == nullptr && cur->m_right == nullptr)
	{
		parent = nullptr;
	}
	// Case 2 - Left empty | Right has data
	else if (cur->m_left == nullptr && cur->m_right != nullptr)
	{
		parent = parent->m_right;
		if (cur == m_root)
			m_root = parent;
	}
	// Case 3 - Left has data | Right empty
	else if (cur->m_left != nullptr && cur->m_right == nullptr)
	{
		parent = parent->m_left;
		if (cur == m_root)
			m_root = parent;
	}
	// Case 4 - Left and Right has data
	else
	{
		// Find the right-most node on the left subtree
		cur = parent->m_left;
		while (cur->m_right != nullptr)
		{
			prev = cur;
			cur = cur->m_right;
		}
		// then set the parent's data to that node's data
		parent->m_data = cur->m_data;
		if (cur == m_root)
			m_root = parent;

		// if the immediate left of the parent is already the right-most node, then just connect the current's left
		if (prev == nullptr)
			parent->m_left = cur->m_left;
		else
			prev->m_right = cur->m_left;
	}
	delete cur;
}

template<typename T>
void BSTree<T>::Purge(BSNode<T>*& cur)
{
	if (cur != nullptr)
	{
		// Similar logic to PostOrder
		Purge(cur->m_left);
		Purge(cur->m_right);
		// delete then reset this node
		delete cur;
		cur = nullptr;
	}
}

template<typename T>
int BSTree<T>::Height(BSNode<T>* cur) const
{
	int intReturn;
	if (cur == nullptr)
	{
		intReturn = -1;
	}
	else
	{
		int intLeft = Height(cur->m_left);
		int intRight = Height(cur->m_right);

		if (intLeft > intRight)
			intReturn = intLeft + 1;
		else
			intReturn = intRight + 1;
	}
	
	return intReturn;
}

template<typename T>
void BSTree<T>::InOrder(BSNode<T>* cur, void(*visit)(T data)) const
{
	// the visitor manipulates a copy of the data without modifying the original value

	// visit from left to right order
	if (cur != nullptr)
	{
		InOrder(cur->m_left, visit);
		visit(cur->m_data);
		InOrder(cur->m_right, visit);
	}
}

template<typename T>
void BSTree<T>::PreOrder(BSNode<T>* cur, void(*visit)(T data)) const
{
	// visit as you go
	if (cur != nullptr)
	{
		visit(cur->m_data);
		PreOrder(cur->m_left, visit);
		PreOrder(cur->m_right, visit);
	}
}

template<typename T>
void BSTree<T>::PostOrder(BSNode<T>* cur, void(*visit)(T data)) const
{
	// visit from right to left order
	if (cur != nullptr)
	{
		PostOrder(cur->m_left, visit);
		PostOrder(cur->m_right, visit);
		visit(cur->m_data);
	}
}

template<typename T>
BSNode<T>* BSTree<T>::CopyTree(BSNode<T>* cur) const
{
	BSNode<T>* temp = nullptr;

	// If this node is not empty
	if (cur != nullptr)
	{
		// Create a new node with the rhs data
		temp = new BSNode<T>(cur->m_data);

		// Copy the left subtree
		temp->m_left = CopyTree(cur->m_left);

		// Copy the right subtree
		temp->m_right = CopyTree(cur->m_right);
	}

	return temp;
}

#endif // !BS_TREE_H