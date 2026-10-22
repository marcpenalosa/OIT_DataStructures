/*********************************************
* Author:		Marc Penalosa
* Filename:		graph.h
* Date Created:	02/24/26
*********************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
using std::list;
#include <iterator>
#include <queue>
using std::queue;
#include <stack>
using std::stack;

#include "vertex.h"
#include "exception.h"

/*
* Class: Graph
* 
* Purpose:
*		Creates a templated undirected Graph class, where V is the data stored in a Vertex and E is an identifier of an Edge
* 
* Manager Functions:
*		Graph();
*			delegates setting default values to list and Vertex
*		Graph(const Graph& copy);
*			pushes all Vertex data from the rhs to the lhs, then reconstructs all Edges to point to the correct Vertices
*		Graph(Graph&& copy) noexcept;
*		Graph& operator=(const Graph& rhs);
*			purges the lhs, then does the same thing as the copy ctor
*		Graph& operator=(Graph&& rhs) noexcept;
*		~Graph();
* 
* Public Methods:
*		int getNumVertices() const;
*		list<Vertex<V, E>>& getVertices();
*		const list<Vertex<V, E>>& getVertices() const;
* 
*		list<Edge<V, E>>& operator[](V data);
*			accesses a Vertex's list of Edges
*		const list<Edge<V, E>>& operator[](const V data) const;
*		void InsertVertex(V data);
*			inserts a Vertex into the list
*		void InsertEdge(V from, V to, E edge, int weight);
*			connects two Vertices with a given Edge and weight
*		void DeleteVertex(V data);
*			deletes a Vertex from the list, disconnecting existing connections
*		void DeleteEdge(V from, V to);
*			deletes an Edge in between two Vertices
*		void DeleteEdge(E edge);
*			deletes all Edges containing the matching identifier
*		void Purge();
*			deletes the entire list of Vertices
*		void PurgeEdges();
*			retains the list of Vertices, but disconnect all existing connections
*		void BreadthFirst(void(*visit)(V data));
*		void BreadthFirst(void(*visit)(V data), V start);
*		void DepthFirst(void(*visit)(V data));
*		void DepthFirst(void(*visit)(V data), V start);
*		void ClearProcessed();
*			clears the processed variable in Vertex
*/
template<typename V, typename E>
class Graph
{
public:
	Graph();
	Graph(const Graph& copy);
	Graph(Graph&& copy) noexcept;
	Graph& operator=(const Graph& rhs);
	Graph& operator=(Graph&& rhs) noexcept;
	~Graph();

	int getNumVertices() const;
	list<Vertex<V, E>>& getVertices();
	const list<Vertex<V, E>>& getVertices() const;
	list <Edge<V, E>>& operator[](V data);
	const list<Edge<V, E>>& operator[](const V data) const;
	void InsertVertex(V data);
	void InsertEdge(V from, V to, E edge, int weight);
	void DeleteVertex(V data);
	void DeleteEdge(V from, V to);
	void DeleteEdge(E edge);
	void Purge();
	void PurgeEdges();
	void BreadthFirst(void(*visit)(V data));
	void BreadthFirst(void(*visit)(V data), V start);
	void DepthFirst(void(*visit)(V data));
	void DepthFirst(void(*visit)(V data), V start);
	void ClearProcessed();
private:
	list<Vertex<V, E>> m_vertices;
};

template<typename V, typename E>
Graph<V, E>::Graph()
{
}

/*
* Purpose:
*		deep copies an existing Graph
* Precondition:
*		none
* Postcondition:
*		a given Graph, its Vertices, and Edges connecting them, are deep copied to this Graph
*/
template<typename V, typename E>
Graph<V, E>::Graph(const Graph& copy)
{
	// insert all rhs vertices data into this one
	for (typename list<Vertex<V, E>>::const_iterator i = copy.m_vertices.begin(); i != copy.m_vertices.end(); i++)
	{
		m_vertices.push_back(i->getVData());
	}

	// traverse through the rhs vertices data again and reconstruct edges
	for (typename list<Vertex<V, E>>::const_iterator currentVertex = copy.m_vertices.begin(); currentVertex != copy.m_vertices.end(); currentVertex++)
	{
		for (typename list<Edge<V, E>>::const_iterator edgeList = currentVertex->getEdges().begin(); edgeList != currentVertex->getEdges().end(); edgeList++)
		{
			// Takes information from rhs to fill out InsertEdge(V from, V to, E edge, int weight)
			InsertEdge(currentVertex->getVData(), edgeList->getDestination()->getVData(), edgeList->getEData(), edgeList->getWeight());
		}
	}
}

template<typename V, typename E>
Graph<V, E>::Graph(Graph&& copy) noexcept : m_vertices(std::move(copy.m_vertices))
{
}

/*
* Purpose:
*		deep copies an existing Graph
* Precondition:
*		none
* Postcondition:
*		purges this Grapth, then a given Graph, its Vertices, and Edges connecting them, are deep copied to this Graph
*/
template<typename V, typename E>
Graph<V, E>& Graph<V, E>::operator=(const Graph& rhs)
{
	if (this != &rhs)
	{
		// clear lhs
		m_vertices.clear();

		// insert all rhs vertices data into this one
		for (typename list<Vertex<V, E>>::const_iterator i = rhs.m_vertices.begin(); i != rhs.m_vertices.end(); i++)
		{
			m_vertices.push_back(i->getVData());
		}

		// traverse through the rhs vertices data again and reconstruct edges
		for (typename list<Vertex<V, E>>::const_iterator currentVertex = rhs.m_vertices.begin(); currentVertex != rhs.m_vertices.end(); currentVertex++)
		{
			//const list<Edge<V, E>> rhsEdgeList = i->getEdges();
			for (typename list<Edge<V, E>>::const_iterator edgeList = currentVertex->getEdges().begin(); edgeList != currentVertex->getEdges().end(); edgeList++)
			{
				InsertEdge(currentVertex->getVData(), edgeList->getDestination()->getVData(), edgeList->getEData(), edgeList->getWeight());
			}
		}
	}

	return *this;
}

template<typename V, typename E>
Graph<V, E>& Graph<V, E>::operator=(Graph&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_vertices = std::move(rhs.m_vertices);
	}

	return *this;
}

template<typename V, typename E>
Graph<V, E>::~Graph()
{
	m_vertices.clear();
}

template<typename V, typename E>
int Graph<V, E>::getNumVertices() const
{
	return m_vertices.size();
}

template<typename V, typename E>
list<Vertex<V, E>>& Graph<V, E>::getVertices()
{
	return m_vertices;
}

template<typename V, typename E>
const list<Vertex<V, E>>& Graph<V, E>::getVertices() const
{
	return m_vertices;
}

/*
* Purpose:
*		Accesses a given Vertex's list of Edges
* Precondition:
*		the given Vertex must exist
* Postcondition:
*		a Vertex's list of Edges is returned
*/
template<typename V, typename E>
list<Edge<V, E>>& Graph<V, E>::operator[](V data)
{
	bool found = false;

	// find and stop the iterator at the Vertex's location
	typename list<Vertex<V, E>>::iterator vList = m_vertices.begin();
	while (!found && vList != m_vertices.end())
	{
		if (data == vList->getVData())
			found = true;
		else
			vList++;
	}
	if (!found)
		throw Exception("could not find vertex");

	return vList->getEdges();
}

/*
* const version of the function above
*/
template<typename V, typename E>
const list<Edge<V, E>>& Graph<V, E>::operator[](const V data) const
{
	bool found = false;

	// find and stop the iterator at the Vertex's location
	typename list<Vertex<V, E>>::const_iterator vList = m_vertices.begin();
	while (!found && vList != m_vertices.end())
	{
		if (data == vList->getVData())
			found = true;
		else
			vList++;
	}
	if (!found)
		throw Exception("could not find vertex");

	return vList->getEdges();
}

/*
* Purpose:
*		inserts a Vertex into the Graph
* Precondition:
*		duplicate Vertices are ignored
* Postcondition:
*		a Vertex is pushed into this Graph's list of Vertices
*/
template<typename V, typename E>
void Graph<V, E>::InsertVertex(V data)
{
	bool found = false;

	// see if the Vertex already exist, if not then push it to the list
	for (typename list<Vertex<V, E>>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if (data == i->getVData())
			found = true;
	}
	if (!found)
		m_vertices.push_back(Vertex<V, E>(data));
}

/*
* Purpose:
*		connects two Vertices with a given Edge and weight
* Precondition:
*		'from' and 'to' locations must exist
* Postcondition:
*		two Edges are created. These Edges contain destinations to 'from' and 'to' location
*/
template<typename V, typename E>
void Graph<V, E>::InsertEdge(V from, V to, E edge, int weight)
{
	Vertex<V, E>* fromLocation = nullptr;
	Vertex<V, E>* toLocation = nullptr;
	bool foundFrom = false;
	bool foundTo = false;

	// find from and to pointer location, and save their pointers
	for (typename list<Vertex<V, E>>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if (from == i->getVData())
		{
			fromLocation = &*i;
			foundFrom = true;
		}
		if (to == i->getVData())
		{
			toLocation = &*i;
			foundTo = true;
		}
	}

	if (!foundFrom)
		throw Exception("could not find 'from' location");
	if (!foundTo)
		throw Exception("could not find 'to' location");

	fromLocation->Connect(edge, weight, toLocation);
	toLocation->Connect(edge, weight, fromLocation);
}

/*
* Purpose:
*		deletes a Vertex from the Graph
* Precondition:
*		Vertex must exist
* Postcondition:
*		a Vertex and its Edges connecting to other Vertices are deleted from the Graph
*/
template<typename V, typename E>
void Graph<V, E>::DeleteVertex(V data)
{
	bool found = false;
	typename list<Vertex<V, E>>::iterator vList = m_vertices.begin();
	
	// traverse through all the vertices to find the target vertex
	// stops the iterator to the desired vertex location
	while (!found && vList != m_vertices.end())
	{
		if (data == vList->getVData())
			found = true;
		else
			vList++;
	}

	if (!found)
		throw Exception("vertex not found");

	// traverse through all this vertex's edge destination and disconnect them
	typename list<Edge<V, E>>::iterator eList = vList->getEdges().begin();
	while (eList != vList->getEdges().end())
	{
		typename list<Edge<V, E>>::iterator deleteTemp = eList;
		eList++;
		// uses information information from above call DeleteEdge(V from, V to). This disconnects both ways
		DeleteEdge(vList->getVData(), deleteTemp->getDestination()->getVData());
	}

	// delete the vertex from the graph's list
	m_vertices.erase(vList);
}

/*
* Purpose:
*		deletes all Edges between two Vertices
* Precondition:
*		'from' and 'to' location must exist
* PostconditioN:
*		all Edges between two Vertices are deleted
*/
template<typename V, typename E>
void Graph<V, E>::DeleteEdge(V from, V to)
{
	Vertex<V, E>* fromLocation = nullptr;
	Vertex<V, E>* toLocation = nullptr;
	// traverse through all the vertices
	for (typename list<Vertex<V, E>>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if (i->getVData() == from)
			fromLocation = &*i;
		if (i->getVData() == to)
			toLocation = &*i;
	}

	if (fromLocation == nullptr)
		throw Exception("could not find 'from' vertex");
	if (toLocation == nullptr)
		throw Exception("could not find 'to' vertex");

	// Disconnect both ways
	fromLocation->Disconnect(toLocation);
	toLocation->Disconnect(fromLocation);
}

/*
* Purpose:
*		deletes all Edges that matches the given identifier
* Precondition:
*		Edge must exist
* Postcondition:
*		deletes all Edges from every Vertices that matches the given identifier
*/
template<typename V, typename E>
void Graph<V, E>::DeleteEdge(E edge)
{
	// traverse through all the vertices
	for (typename list<Vertex<V, E>>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		i->Disconnect(edge);
	}
}

/*
* Purpose:
*		clears the list of Vertices
* Precondition:
*		none
* Postcondition:
*		the list of Vertices is cleared
*/
template<typename V, typename E>
void Graph<V, E>::Purge()
{
	m_vertices.clear();
}

/*
* Purpose:
*		clears all Edges
* Precondition:
*		none
* Postcondition:
*		all Edges are deletes, while keeping the existing Vertices
*/
template<typename V, typename E>
void Graph<V, E>::PurgeEdges()
{
	for (typename list<Vertex<V, E>>::iterator vList = m_vertices.begin(); vList != m_vertices.end(); vList++)
	{
		vList->getEdges().clear();
	}
}

/*
* Purpose:
*		performs a BreadthFirst traversal using a visit function
* Precondition:
*		Graph must not be empty
* Postcondition:
*		all Vertices' data are exposed to the visiting function
*/
template<typename V, typename E>
void Graph<V, E>::BreadthFirst(void(*visit)(V data))
{
	if (m_vertices.size() == 0)
		throw Exception("empty graph");

	queue<Vertex<V, E>*> vQueue;
	m_vertices.begin()->setProcessed(true);
	vQueue.push(&*m_vertices.begin());
	while (!vQueue.empty())
	{
		Vertex<V, E>* cur = vQueue.front();
		vQueue.pop();

		visit(cur->getVData());

		for (typename list<Edge<V, E>>::iterator eList = cur->getEdges().begin(); eList != cur->getEdges().end(); eList++)
		{
			Vertex<V, E>* adj = eList->getDestination();

			if (!adj->isProcessed())
			{
				adj->setProcessed(true);
				vQueue.push(adj);
			}
		}
	}
	ClearProcessed();
}

/*
* Same as above, but can start at any Vertex
*/
template<typename V, typename E>
void Graph<V, E>::BreadthFirst(void(*visit)(V data), V start)
{
	// find the initial vertex location
	Vertex<V, E>* root = nullptr;
	for (typename list<Vertex<V, E>>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if (i->getVData() == start)
			root = &*i;
	}

	if (root == nullptr)
		throw Exception("root is nullptr");

	queue<Vertex<V, E>*> vQueue;
	root->setProcessed(true);
	vQueue.push(root);
	while (!vQueue.empty())
	{
		Vertex<V, E>* cur = vQueue.front();
		vQueue.pop();

		visit(cur->getVData());

		for (typename list<Edge<V, E>>::iterator eList = cur->getEdges().begin(); eList != cur->getEdges().end(); eList++)
		{
			Vertex<V, E>* adj = eList->getDestination();

			if (!adj->isProcessed())
			{
				adj->setProcessed(true);
				vQueue.push(adj);
			}
		}
	}
	ClearProcessed();
}

/*
* Purpose:
*		performs a DepthFirst traversal using a visit function
* Precondition:
*		Graph must not be empty
* Postcondition:
*		all Vertices' data are exposed to the visiting function
*/
template<typename V, typename E>
void Graph<V, E>::DepthFirst(void(*visit)(V data))
{
	stack<Vertex<V, E>*> vstack;
	m_vertices.begin()->setProcessed(true);
	vstack.push(&*m_vertices.begin());
	while (!vstack.empty())
	{
		Vertex<V, E>* cur = vstack.top();
		vstack.pop();

		visit(cur->getVData());

		for (typename list<Edge<V, E>>::iterator eList = cur->getEdges().begin(); eList != cur->getEdges().end(); eList++)
		{
			Vertex<V, E>* adj = eList->getDestination();

			if (!adj->isProcessed())
			{
				adj->setProcessed(true);
				vstack.push(adj);
			}
		}
	}
	ClearProcessed();
}

/*
* Same as above, but can start at any Vertex
*/
template<typename V, typename E>
void Graph<V, E>::DepthFirst(void(*visit)(V data), V start)
{
	// find the initial vertex location
	Vertex<V, E>* root = nullptr;
	for (typename list<Vertex<V, E>>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if (i->getVData() == start)
			root = &*i;
	}

	if (root == nullptr)
		throw Exception("root is nullptr");

	stack<Vertex<V, E>*> vstack;
	root->setProcessed(true);
	vstack.push(root);
	while (!vstack.empty())
	{
		Vertex<V, E>* cur = vstack.top();
		vstack.pop();

		visit(cur->getVData());

		for (typename list<Edge<V, E>>::iterator eList = cur->getEdges().begin(); eList != cur->getEdges().end(); eList++)
		{
			Vertex<V, E>* adj = eList->getDestination();

			if (!adj->isProcessed())
			{
				adj->setProcessed(true);
				vstack.push(adj);
			}
		}
	}
	ClearProcessed();
}

/*
* Purpose:
*		clears all Vertices' processed state
* Precondition:
*		none
* Postcondition:
*		all Vertices' processed state are set back to false
*/
template<typename V, typename E>
void Graph<V, E>::ClearProcessed()
{
	// traverse through the entire list of vertices
	for (typename list<Vertex<V, E>>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		i->setProcessed(false);
	}
}

#endif // !GRAPH_H