/*******************************************
* Author:			Marc Penalosa
* Filename:			bsTree.h
* Date Created:		2/02/26
* Date Modified:	2/07/26
*						- Modified to be an AVL Tree
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
*		Creates an AVL Tree that is able to traverse its nodes with various traversal functions, insert nodes,
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
* 		BSNode<T>* LeftBalance(BSNode<T>*& cur, bool& taller)
*			When a tree is unbalanced to the left, this balances it
*		BSNode<T>* RightBalance(BSNode<T>*& cur, bool& taller)
*			When a tree is unbalanced to the right, this balanaces it
*		BSNode<T>* RotateLeft(BSNode<T>*& cur)
*			Rotates a tree to the left
*		BSNode<T>* RotateRight(BSNode<T>*& cur)
*			Rotates a tree to the right
*		BSNode<T>* DeleteLeftBalance(BSNode<T>*& cur, bool& shorter)
*			After deleting a node on the right, the tree is unbalanced to the left. This balances it
*		BSNode<T>* DeleteRightBalance(BSNode<T>*& cur, bool& shorter)
*			After deleting a node on the left, the tree is unbalanced to the right. This balances it
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
	BSNode<T>* m_root;

	void Insert(BSNode<T>*& cur, T data, bool& taller);
	BSNode<T>* Delete(BSNode<T>*& cur, T data, bool& shorter);
	void Purge(BSNode<T>*& cur);
	int Height(BSNode<T>* cur) const;
	void InOrder(BSNode<T>* cur, void (*visit)(T data)) const;
	void PreOrder(BSNode<T>* cur, void (*visit)(T data)) const;
	void PostOrder(BSNode<T>* cur, void (*visit)(T data)) const;
	BSNode<T>* LeftBalance(BSNode<T>*& cur, bool& taller);
	BSNode<T>* RightBalance(BSNode<T>*& cur, bool& taller);
	BSNode<T>* RotateLeft(BSNode<T>*& cur);
	BSNode<T>* RotateRight(BSNode<T>*& cur);
	BSNode<T>* DeleteLeftBalance(BSNode<T>*& cur, bool& shorter);
	BSNode<T>* DeleteRightBalance(BSNode<T>*& cur, bool& shorter);

	// This is a helper function for the Copy Ctor and Op Equal
	BSNode<T>* CopyTree(BSNode<T>* cur) const;
};

template<typename T>
BSTree<T>::BSTree() : m_root(nullptr)
{
}

template<typename T>
BSTree<T>::BSTree(const BSTree& copy) : m_root(CopyTree(copy.m_root))
{
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
	bool taller = false;
	Insert(m_root, data, taller);
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
	bool shorter = false;
	m_root = Delete(m_root, data, shorter);
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
void BSTree<T>::Insert(BSNode<T>*& cur, T data, bool& taller)
{
	// Insert encounters an empty node and unwinds the stack
	if (cur == nullptr)
	{
		cur = new BSNode<T>(data);
		taller = true;
	}
	// If cur is not an empty node
	// Go left if data is less than current node
	else if (data < cur->m_data)
	{
		Insert(cur->m_left, data, taller);
		// Insert encountered an empty node and triggered if(taller)
		if (taller)
		{
			// Insert on this node resulted to an imbalance
			if (cur->m_bal == LH)
				cur = LeftBalance(cur, taller);
			else if (cur->m_bal == EH)
				cur->m_bal = LH;
			else
			{
				// Was right-high, now even-high
				cur->m_bal = EH;
				taller = false;
			}
		}
	}
	// Go right
	else
	{
		Insert(cur->m_right, data, taller);
		// Insert countered an empty node and triggered if(taller)
		if (taller)
		{
			// If this cur node is left heavy, you just inserted right so it evens out
			if (cur->m_bal == LH)
			{
				cur->m_bal = EH;
				taller = false;
			}
			// If this cur node is balanced, it's now right heavy
			else if (cur->m_bal == EH)
				cur->m_bal = RH;
			// if this node is right heavy, your right insert would have unbalanced the tree
			else
				cur = RightBalance(cur, taller);
		}
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
BSNode<T>* BSTree<T>::Delete(BSNode<T>*& cur, T data, bool& shorter)
{
	if (cur == nullptr)
		throw Exception("Delete failed. Could not find data");

	if (data < cur->m_data)
	{
		// Go left and check if it's the data
		cur->m_left = Delete(cur->m_left, data, shorter);
		// shorter becomes true if it encountered and deleted a data, then need to balance
		if (shorter)
			cur = DeleteRightBalance(cur, shorter);
	}
	else if (data > cur->m_data)
	{
		// Go right and check if it's the data
		cur->m_right = Delete(cur->m_right, data, shorter);
		// shorter becomes true if it encountered and deleted a data, then need to balance
		if (shorter)
			cur = DeleteLeftBalance(cur, shorter);
	}
	else // target node found
	{
		BSNode<T>* deleteNode = cur;
		// if right subtree doesn't exist
		if (cur->m_right == nullptr)
		{
			cur = cur->m_left;
			shorter = true;
			delete deleteNode;
		}
		// if left subtree doesn't exist
		else if (cur->m_left == nullptr)
		{
			cur = cur->m_right;
			shorter = true;
			delete deleteNode;
		}
		// else the node has 2 subtrees
		else
		{
			// find the left tree's right-most node
			BSNode<T>* temp = cur->m_left;
			while (temp->m_right != nullptr)
			{
				temp = temp->m_right;
			}

			// swap the left tree's right-most node's data to the root, then delete that node instead of the root
			cur->m_data = temp->m_data;
			cur->m_left = Delete(cur->m_left, temp->m_data, shorter);
			if (shorter)
				cur = DeleteRightBalance(cur, shorter);
		}
	}

	return cur;
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
*		When a tree is unbalanced to the left, this balances it
* Precondition:
*		The tree is left high
* Postcondition:
*		Balances the tree
*		Returns a new root if necessary
*/
template<typename T>
BSNode<T>* BSTree<T>::LeftBalance(BSNode<T>*& cur, bool& taller)
{
	BSNode<T>* leftTree = cur->m_left;
	// If leftSubTree is left-high
	if (leftTree->m_bal == LH)
	{
		// Case 1: LL Rotation
		cur = RotateRight(cur);
		// cur now points to the original root problem's left child, and cur->m_right points to the original root
		cur->m_bal = EH;
		cur->m_right->m_bal = EH;
		taller = false;
	}
	else
	{
		// Case 2: LR Rotation
		BSNode<T>* rightTree = leftTree->m_right;	// leftTree's right subtree
		
		// Adjust balance factors
		if (rightTree->m_bal == LH)
		{
			cur->m_bal = RH;
			leftTree->m_bal = EH;
		}
		else if (rightTree->m_bal == EH)
			leftTree->m_bal = EH;
		else
		{
			// if rightTree->m_bal == RH
			// old root would inherit a node, which balances it, while leftTree would lose it so it will be LH
			cur->m_bal = EH;
			leftTree->m_bal = LH;
		}
		rightTree->m_bal = EH;
		cur->m_left = RotateLeft(leftTree);
		cur = RotateRight(cur);
		taller = false;
	}

	return cur;
}

/*
* Purpose:
*		When a tree is unbalanced to the right, this balances it
* Precondition:
*		The tree is right high
* Postcondition:
*		Balances the tree
*		Returns a new root if necessary
*/
template<typename T>
BSNode<T>* BSTree<T>::RightBalance(BSNode<T>*& cur, bool& taller)
{
	BSNode<T>* rightTree = cur->m_right;
	// If right sub tree is high
	if (rightTree->m_bal == RH)
	{
		// Case 1: RR Rotation
		cur = RotateLeft(cur);
		// cur now points to the original root problem's right child, and cur->m_left points to the original root
		cur->m_bal = EH;
		cur->m_left->m_bal = EH;
		taller = false;
	}
	else
	{
		// Case 2: RL Rotation
		BSNode<T>* leftTree = rightTree->m_left;

		// Adjust Balance Factors
		if (leftTree->m_bal == LH)
		{
			// if leftTree is LH, after the rotation, rightTree will lose a node and make it RH,
			// while original root will inherit it and balance out
			cur->m_bal = EH;
			rightTree->m_bal = RH;
		}
		else if (leftTree->m_bal == EH)
			rightTree->m_bal = EH;
		else
		{
			// if leftTree->m_bal == RH
			cur->m_bal = LH;
			rightTree->m_bal = EH;
		}
		leftTree->m_bal = EH;
		cur->m_right = RotateRight(rightTree);
		cur = RotateLeft(cur);
		taller = false;
	}

	return cur;
}

/*
* Purpose:
*		Rotates a subtree to the left
* Precondition:
*		Cur points the root of the subtree to be rotated
* Postcondition:
*		Tree is rotated
*		Returns a new root
*/
template<typename T>
BSNode<T>* BSTree<T>::RotateLeft(BSNode<T>*& cur)
{
	BSNode<T>* temp = cur->m_right;
	cur->m_right = temp->m_left;
	temp->m_left = cur;
	return temp;
}

/*
* Purpose:
*		Rotates a subtree to the right
* Precondition:
*		Cur points the root of the subtree to be rotated
* Postcondition:
*		Tree is rotated
*		Returns a new root
*/
template<typename T>
BSNode<T>* BSTree<T>::RotateRight(BSNode<T>*& cur)
{
	BSNode<T>* temp = cur->m_left;
	cur->m_left = temp->m_right;
	temp->m_right = cur;
	return temp;
}

/*
* Purpose:
*		The tree is shorter after a delete on the right, this balances it
* Precondition:
*		The tree is shorter
* Postcondition:
*		Balances the tree and adjusts the affected nodes' balance factors
*		Returns a new root if necessary
*/
template<typename T>
BSNode<T>* BSTree<T>::DeleteLeftBalance(BSNode<T>*& cur, bool& shorter)
{
	// God have mercy
	// determine if we need to balance tree
	if (cur->m_bal == LH) // if cur was left heavy and we deleted right, it becomes unbalanced
	{
		BSNode<T>* leftTree = cur->m_left;

		// NOTE: Balance factors are adjusted before rotation
		// Check if we need a double rotation or a single rotation
		if (leftTree->m_bal == RH) // double rotation because it's left then right
		{
			BSNode<T>* rightTree = leftTree->m_right;

			// adjust balance factors
			if (rightTree->m_bal == RH)
			{
				leftTree->m_bal = LH;
				cur->m_bal = EH;
			}
			else if (rightTree->m_bal == EH)
			{
				leftTree->m_bal = EH;
				cur->m_bal = EH;
			}
			else // rightTree->m_bal == LH
			{
				leftTree->m_bal = EH;
				cur->m_bal = RH;
			}
			rightTree->m_bal = EH;

			// double rotate, temp subtree first, then current tree
			cur->m_left = RotateLeft(leftTree);
			cur = RotateRight(cur);
			
		}
		else // single rotation
		{
			// adjust balance factors
			if (leftTree->m_bal != EH)
			{
				leftTree->m_bal = EH;
				cur->m_bal = EH;
			}
			else
			{
				leftTree->m_bal = RH;
				cur->m_bal = LH;
				shorter = false;
			}
			cur = RotateRight(cur);
		}
	}
	else if (cur->m_bal == EH) // if root was even, we just deleted right, it's now right heavy and doesn't affect the parents' balance factors anymore
	{
		cur->m_bal = LH;
		shorter = false;
	}
	else // if root was RH, we just deleted right so it evens out, we keep "shorter" to true so that this cur's parent node balances itself
	{
		cur->m_bal = EH;
	}

	return cur;
}

/*
* Purpose:
*		The tree is shorter after a delete on the left, this balances it
* Precondition:
*		The tree is shorter
* Postcondition:
*		Balances the tree and adjusts the affected nodes' balance factors
*		Returns a new root if necessary
*/
template<typename T>
BSNode<T>* BSTree<T>::DeleteRightBalance(BSNode<T>*& cur, bool& shorter)
{
	// determine if we even need to balance the tree
	if (cur->m_bal == LH) // if the root was LH, and we just deleted left, it's now EH
	{
		cur->m_bal = EH;
	}
	else if (cur->m_bal == EH) // if the root was EH, we just deleted the left, it's now RH and the tree cannot be shorter because height stays same
	{
		cur->m_bal = RH;
		shorter = false;
	}
	else // right tree was RH already so rotate left
	{
		BSNode<T>* rightTree = cur->m_right;

		// NOTE: Balance factors are adjusted before rotation
		// Check if we need a double rotation or a single rotation
		if (rightTree->m_bal == LH)	// Double Rotation
		{
			BSNode<T>* leftTree = rightTree->m_left;
			
			// adjust balance factors
			if (leftTree->m_bal == LH)
			{
				rightTree->m_bal = RH;
				cur->m_bal = EH;
			}
			else if (leftTree->m_bal == EH)
			{
				rightTree->m_bal = EH;
				cur->m_bal = EH;
			}
			else // leftTree->m_bal == RH
			{
				rightTree->m_bal = EH;
				cur->m_bal = LH;
			}
			leftTree->m_bal = EH;

			// Double rotate, temporary subtree first, then the current subtree
			cur->m_right = RotateRight(rightTree);
			cur = RotateLeft(cur);
		}
		else // single rotation
		{
			// adjust balance factors
			if (rightTree->m_bal != EH)
			{
				rightTree->m_bal = EH;
				cur->m_bal = EH;
			}
			else
			{
				rightTree->m_bal = LH;
				cur->m_bal = RH;
				shorter = false;
			}
			cur = RotateLeft(cur);
		}
	}

	return cur;
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
		temp->m_bal = cur->m_bal;

		// Copy the left subtree
		temp->m_left = CopyTree(cur->m_left);

		// Copy the right subtree
		temp->m_right = CopyTree(cur->m_right);
	}

	return temp;
}

#endif // !BS_TREE_H