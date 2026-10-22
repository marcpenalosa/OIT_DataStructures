/*********************************************
* Author:		Marc Penalosa
* Filename:		vertex.h
* Date Created:	02/24/26
*********************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include <list>
using std::list;
#include "edge.h"
#include "exception.h"

/*
* Class: Vertex
* 
* Purpose:
*		Creates a Vertex that contains data, and has a list of Edges
* 
* Manager Functions:
*		Vertex();
*			sets the data to its type's default value, processed to false, and delegates settings other defaults to list and Edge
*		Vertex(V data);
*			sets the data to the given value, processed to false, and delegates setting other defaults to list and Edge
*		Vertex(const Vertex& copy);
*		Vertex(Vertex&& copy) noexcept;
*		Vertex& operator=(const Vertex& rhs);
*		Vertex& operator=(Vertex&& rhs) noexcept;
*		~Vertex();
* 
* Public Methods:
*		V getVData() const;
*		list<Edge<V, E>>& getEdges();
*		const list<Edge<V, E>>& getEdges() const;
*		bool isProcessed() const;
*		void setProcessed(bool processed);
* 
*		void Connect(E edge, int weight, Vertex<V, E>* destination);
*			pushes an Edge that contains an identifier, weight, and destination Vertex, into this Vertex's list of Edges
*		void Disconnect(E edge);
*			disconnects all Edges containing the matching identifier
*		void Disconnect(Vertex<V, E>* destination);	
*			disconnects all Edges that contain the matching destination Vertex
*/
template<typename V, typename E>
class Vertex
{
public:
	Vertex();
	Vertex(V data);
	Vertex(const Vertex& copy);
	Vertex(Vertex&& copy) noexcept;
	Vertex& operator=(const Vertex& rhs);
	Vertex& operator=(Vertex&& rhs) noexcept;
	~Vertex();

	V getVData() const;
	list<Edge<V, E>>& getEdges();
	const list<Edge<V, E>>& getEdges() const;
	bool isProcessed() const;
	void setProcessed(bool processed);
	void Connect(E edge, int weight, Vertex<V, E>* destination);
	void Disconnect(E edge);
	void Disconnect(Vertex<V, E>* destination);
private:
	V m_data;
	bool m_processed;
	list<Edge<V, E>> m_edges;
};

template<typename V, typename E>
Vertex<V, E>::Vertex() : m_data(V()), m_processed(false)
{
}

template<typename V, typename E>
Vertex<V, E>::Vertex(V data) : m_data(data), m_processed(false)
{
}

template<typename V, typename E>
Vertex<V, E>::Vertex(const Vertex& copy) : m_data(copy.m_data), m_processed(copy.m_processed), m_edges(copy.m_edges)
{
}

template<typename V, typename E>
Vertex<V, E>::Vertex(Vertex&& copy) noexcept : m_data(std::move(copy.m_data)), m_processed(copy.m_processed), m_edges(std::move(copy.m_edges))
{
	copy.m_data = V();
	copy.m_processed = false;
}

template<typename V, typename E>
Vertex<V, E>& Vertex<V, E>::operator=(const Vertex& rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_processed = rhs.m_processed;
		m_edges = rhs.m_edges;
	}

	return *this;
}

template<typename V, typename E>
Vertex<V, E>& Vertex<V, E>::operator=(Vertex&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_data = std::move(rhs.m_data);
		m_processed = rhs.m_processed;
		m_edges = std::move(rhs.m_edges);
		
		rhs.m_data = V();
		rhs.m_processed = false;
	}
	
	return *this;
}

template<typename V, typename E>
Vertex<V, E>::~Vertex()
{
	m_data = V();
	m_processed = false;
	m_edges.clear();
}

template<typename V, typename E>
V Vertex<V, E>::getVData() const
{
	return m_data;
}

template<typename V, typename E>
list<Edge<V, E>>& Vertex<V, E>::getEdges()
{
	return m_edges;
}

template<typename V, typename E>
const list<Edge<V, E>>& Vertex<V, E>::getEdges() const
{
	return m_edges;
}

template<typename V, typename E>
bool Vertex<V, E>::isProcessed() const
{
	return m_processed;
}

template<typename V, typename E>
void Vertex<V, E>::setProcessed(bool processed)
{
	m_processed = processed;
}

/*
* Purpose:
*		pushes an Edge that contains an identifier, weight, and destination Vertex, into this Vertex's list of Edges
* Precondition:
*		destination must exist
* Postcondition:
*		an Edge is created and pushed into this Vertex's list of Edges
*/
template<typename V, typename E>
void Vertex<V, E>::Connect(E edge, int weight, Vertex<V, E>* destination)
{
	if (destination == nullptr)
		throw Exception("destination is nullptr");

	// initial push
	if (m_edges.size() == 0)
	{
		m_edges.push_back(Edge<V, E>(edge, weight, destination));
	}
	// check if edge already exist
	else
	{
		bool found = false;
		for (typename list<Edge<V, E>>::iterator i = m_edges.begin(); i != m_edges.end(); i++)
		{
			if (i->m_data == edge && i->m_weight == weight && i->m_destination == destination)
				found = true;
		}
		if (!found)
			m_edges.push_back(Edge<V, E>(edge, weight, destination));
	}
}

/*
* Purpose:
*		disconnects all Edges with the matching identifier
* Precondition:
*		Edge must exist
* Postcondition:
*		deletes all Edges with the matching identifier from this Vertex's list of Edges
*/
template<typename V, typename E>
void Vertex<V, E>::Disconnect(E edge)
{
	bool found = false;

	// go through the list of edges
	typename list<Edge<V, E>>::iterator i = m_edges.begin();
	while (i != m_edges.end())
	{
		// if the edge identifier matches, delete it
		if (edge == i->m_data)
		{
			typename list<Edge<V, E>>::iterator nodeLocation = i;
			i++;
			m_edges.erase(nodeLocation);
			found = true;
		}
		else
			i++;
	}

	if (!found)
		throw Exception("edge not found");
}

/*
* Purpose:
*		disconnects all Edges with the matching Vertex destination pointer
* Precondition:
*		destination Vertex must exist
* Postcondition:
*		deletes all Edges with the matching Vertex destination pointer from this Vertex's list of Edges
*/
template<typename V, typename E>
void Vertex<V, E>::Disconnect(Vertex<V, E>* destination)
{
	bool found = false;

	// go through the list of edges
	typename list<Edge<V, E>>::iterator i = m_edges.begin();
	while (i != m_edges.end())
	{
		// if the edge desstination matches, delete it
		if (destination == i->getDestination())
		{
			typename list<Edge<V, E>>::iterator nodeLocation = i;
			i++;
			m_edges.erase(nodeLocation);
			found = true;
		}
		else
			i++;
	}

	if (!found)
		throw Exception("destination not found");
}

#endif // !VERTEX_H