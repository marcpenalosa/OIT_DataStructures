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
*			Sets the m_root to nullptr
*		BSTree(const BSTree& copy)
*		BSTree(BSTree&& copy) noexcept
*		BSTree& operator=(const BSTree& rhs)
*		BSTree& operator=(BSTree&& rhs) noexcept
*		~BSTree()
* 
* Methods:
*		void Insert(T data)
*			Calls the private Insert function, passing in the root as pointer ref
*		void Delete(T data)
*			Find the target node, then passes the parent node of that target, unless it's the root (then it passes the root)
*		void Purge()
*			Calls the private Purge function, passing in the root as pointer ref
*		int Height() const
*			Calls the private Height function, passing in the root as a pointer ref
* 
*		// These are public traversal interfaces that calls their private counterpart, passes the root as pointer reference
*		// and takes in a void visit function
*		void InOrder(void (*visit)(T data)) const
*		void PreOrder(void (*visit)(T data)) const
*		void PostOrder(void (*visit)(T data)) const
* 
*		void BreadthFirst(void (*visit)(T data)) const
*			A public traversal method that is iterative. Uses the visit function from left to right, each height, before moving down
* 
*		***** PRIVATE FUNCTIONS *****
*		void Insert(BSNode<T>*& cur, T data)
*			Insert a node depending if it's greather than or equal to the current node. If it's equal, then move right
*		void Delete(BSNode<T>*& parent, T data)
*			Deletes a target node and reconnect links
*		void Purge(BSNode<T>*& cur)
*			Deletes the entire tree
*		int Height(BSNode<T>* cur) const
*			Returns the depth of the tree. Has a starting index of 0
* 
*		// These methods uses the visit function in order of the traversal method chosen
*		void InOrder(BSNode<T>* cur, void (*visit)(T data)) const
*		void PreOrder(BSNode<T>* cur, void (*visit)(T data)) const
*		void PostOrder(BSNode<T>* cur, void (*visit)(T data)) const
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

	// This one is iterative and uses a queue
	void BreadthFirst(void (*visit)(T data)) const;

private:
	void Insert(BSNode<T>*& cur, T data);
	void Delete(BSNode<T>*& parent, T data);
	void Purge(BSNode<T>*& cur);
	int Height(BSNode<T>* cur) const;
	void InOrder(BSNode<T>* cur, void (*visit)(T data)) const;
	void PreOrder(BSNode<T>* cur, void (*visit)(T data)) const;
	void PostOrder(BSNode<T>* cur, void (*visit)(T data)) const;

	// This is a helper function for the Copy Ctor and Op Equal
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
	// Is that legal?
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
		Purge();
		m_root = CopyTree(rhs.m_root);
	}

	return *this;
}

template<typename T>
BSTree<T>& BSTree<T>::operator=(BSTree&& rhs) noexcept
{
	if (this != &rhs)
	{
		Purge();
		m_root = std::move(rhs.m_root);

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

/*
* Purpose:
*		An interface that calls the private counterpart that passes in the root and data paremeter
*		Avoids exposing the root to consumer
* Precondition:
*		None
* Postcondition:
*		None
*/
template<typename T>
void BSTree<T>::Insert(T data)
{
	Insert(m_root, data);
}

/*
* Purpose:
*		An interface that calls the private counterpart to avoid exposing the root to consumer
*		Finds the target's parent node and passes that to the private interface (passes the root instead if data is in it)
* Precondition:
*		Tree must not be empty
*		Target must be known and exist
* Postcondition:
*		None
*/
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
		Delete(m_root, data);
	else if (data < prev->m_data)
		Delete(prev->m_left, data);
	else
		Delete(prev->m_right, data);
}

/*
* Purpose:
*		An interface that calls the private counterpart that passes the root 
*		Avoids exposing the root to consumer
* Precondition:
*		None
* Postcondition:
*		None
*/
template<typename T>
void BSTree<T>::Purge()
{
	Purge(m_root);
}

/*
* Purpose:
*		An interface that calls the private counterpart that passes the root
*		Avoids exposing the root to consumer
* Precondition:
*		None
* Postcondition:
*		None
*/
template<typename T>
int BSTree<T>::Height() const
{
	return Height(m_root);
}

/*
* Purpose:
*		An interface that calls the private counterpart that passes the root and the visit function parameter
*		Avoids exposing the root to consumer
* Precondition:
*		Tree must not be empty
* Postcondition:
*		None
*/
template<typename T>
void BSTree<T>::InOrder(void(*visit)(T data)) const
{
	if (m_root == nullptr)
		throw Exception("tree is empty");
	InOrder(m_root, visit);
}

/*
* Purpose:
*		An interface that calls the private counterpart that passes the root and the visit function parameter
*		Avoids exposing the root to consumer
* Precondition:
*		Tree must not be empty
* Postcondition:
*		None
*/
template<typename T>
void BSTree<T>::PreOrder(void(*visit)(T data)) const
{
	if (m_root == nullptr)
		throw Exception("tree is empty");
	PreOrder(m_root, visit);
}

/*
* Purpose:
*		An interface that calls the private counterpart that passes the root and the visit function parameter
*		Avoids exposing the root to consumer
* Precondition:
*		Tree must not be empty
* Postcondition:
*		None
*/
template<typename T>
void BSTree<T>::PostOrder(void(*visit)(T data)) const
{
	if (m_root == nullptr)
		throw Exception("tree is empty");
	PostOrder(m_root, visit);
}

/*
* Purpose:
*		Traverses the tree and calls the visit function breadth-first
* Precondition:
*		Tree must not be empty
* Postcondition:
*		A copy of m_data is manipulated by the visiting function
*/
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
		// temp is used so that we can reuse the pointer to check for m_left and m_right
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

/*
* Purpose:
*		Inserts a node in order that makes up a binary tree
*		If a duplicate exists, it moves to the right of that node and compares again
* Precondition:
*		None
* Postcondition;
*		A node is inserted to the tree
*/
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

/*
* Purpose:
*		Deletes a node that contains the target data
* Precondition:
*		Parent node must not be nullptr
* Postcondition:
*		The target node is deleted, and the existing nodes are rearranged based on the 4 given cases
*/
template<typename T>
void BSTree<T>::Delete(BSNode<T>*& parent, T data)
{
	// REMEMBER: parent is NOT the pointer to the Parent Node
	// parent is the m_left or m_right pointer of the Parent Node that contains the target data
	// this might have been confusing. I could have just said that this points to the target node
	BSNode<T>* cur = parent;
	BSNode<T>* prev = nullptr;

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

		// if the immediate left of the parent is already the right-most node, then just connect the current's left
		if (prev == nullptr)
			parent->m_left = cur->m_left;
		else
			prev->m_right = cur->m_left;
	}
	delete cur;
}

/*
* Purpose:
*		To delete the entire tree
* Precondition:
*		None
* Postcondition:
*		Deletes the entire tree
*/
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

/*
* Purpose:
*		Gets the height of the tree, with a starting index of 0
*		An empty tree returns a -1
* Precondition:
*		None
* Postcondition:
*		Returns the height of the tree
*/
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

/*
* Purpose:
*		Traverses the tree and calls the visit function in-order
* Precondition:
*		None
* Postcondition:
*		A copy of m_data is manipulated by the visiting function
*/
template<typename T>
void BSTree<T>::InOrder(BSNode<T>* cur, void(*visit)(T data)) const
{
	if (cur != nullptr)
	{
		InOrder(cur->m_left, visit);
		visit(cur->m_data);
		InOrder(cur->m_right, visit);
	}
}

/*
* Purpose:
*		Traverses the tree and calls the visit function pre-order
* Precondition:
*		None
* Postcondition:
*		A copy of m_data is manipulated by the visiting function
*/
template<typename T>
void BSTree<T>::PreOrder(BSNode<T>* cur, void(*visit)(T data)) const
{
	if (cur != nullptr)
	{
		visit(cur->m_data);
		PreOrder(cur->m_left, visit);
		PreOrder(cur->m_right, visit);
	}
}

/*
* Purpose:
*		Traverses the tree and calls the visit function post-order
* Precondition:
*		None
* Postcondition:
*		A copy of m_data is manipulated by the visiting function
*/
template<typename T>
void BSTree<T>::PostOrder(BSNode<T>* cur, void(*visit)(T data)) const
{
	if (cur != nullptr)
	{
		PostOrder(cur->m_left, visit);
		PostOrder(cur->m_right, visit);
		visit(cur->m_data);
	}
}

/*
* Purpose:
*		A function to help the Copy Ctor and Copy Assignment
* Precondition:
*		None
* Postcondition:
*		Copies and preserves the structure of the rhs tree to the lhs
*/
template<typename T>
BSNode<T>* BSTree<T>::CopyTree(BSNode<T>* cur) const
{
	BSNode<T>* temp = nullptr;

	// If this node is not empty
	// Recursively copy each path of the tree to preserve the structure
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