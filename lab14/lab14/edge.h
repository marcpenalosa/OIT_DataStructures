/*********************************************
* Author:		Marc Penalosa
* Filename:		edge.h
* Date Created:	02/24/26
*********************************************/

#ifndef EDGE_H
#define EDGE_H

template<typename V, typename E>
class Vertex;

/*
* Class: Edge
* 
* Purpose:
*		Creates an Edge class that contains an identifier, a weight, and a Vertex desination pointer
* 
* Manager Functions:
*		Edge();
*			sets the data to it's type's default value, sets weight to 0, and sets the destination to nullptr
* 		Edge(E data, int weight, Vertex<V, E>* destination = nullptr);
*			sets the data and weight to their given values, sets the destination to the given Vertex pointer
*		Edge(const Edge& copy);
*		Edge(Edge&& copy) noexcept;
*		Edge& operator=(const Edge& rhs);
*		Edge& operator=(Edge&& rhs) noexcept;
*		~Edge();
* 
* Public Methods:
*		E getEData() const;
*		int getWeight() const;
*		Vertex<V, E>* getDestination();
*		const Vertex<V, E>* getDestination() const;
*/
template<typename V, typename E>
class Edge
{
	friend class Vertex<V, E>;
public:
	Edge();
	Edge(E data, int weight, Vertex<V, E>* destination);
	Edge(const Edge& copy);
	Edge(Edge&& copy) noexcept;
	Edge& operator=(const Edge& rhs);
	Edge& operator=(Edge&& rhs) noexcept;
	~Edge();

	E getEData() const;
	int getWeight() const;
	Vertex<V, E>* getDestination();
	const Vertex<V, E>* getDestination() const;
private:
	E m_data;	// data that is used to describe the edge
	int m_weight;
	Vertex<V, E>* m_destination;
};

template<typename V, typename E>
Edge<V, E>::Edge() : m_data(E()), m_weight(0), m_destination(nullptr)
{
}

template<typename V, typename E>
Edge<V, E>::Edge(E data, int weight, Vertex<V, E>* destination) : m_data(data), m_weight(weight), m_destination(destination)
{
}

template<typename V, typename E>
Edge<V, E>::Edge(const Edge& copy) : m_data(copy.m_data), m_weight(copy.m_weight), m_destination(nullptr)
{
}

template<typename V, typename E>
Edge<V, E>::Edge(Edge&& copy) noexcept : m_data(std::move(copy.m_data)), m_weight(copy.m_weight), m_destination(std::move(copy.m_destination))
{
	copy.m_destination = nullptr;
}

template<typename V, typename E>
Edge<V, E>& Edge<V, E>::operator=(const Edge& rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_weight = rhs.m_weight;
		m_destination = nullptr;
	}

	return *this;
}

template<typename V, typename E>
Edge<V, E>& Edge<V, E>::operator=(Edge&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_data = std::move(rhs.m_data);
		m_weight = rhs.m_weight;
		m_destination = std::move(rhs.m_destination);
		rhs.m_destination = nullptr;
	}
	
	return *this;
}

template<typename V, typename E>
Edge<V, E>::~Edge()
{
	m_data = E();
	m_weight = 0;
	m_destination = nullptr;
}

template<typename V, typename E>
E Edge<V, E>::getEData() const
{
	return m_data;
}

template<typename V, typename E>
int Edge<V, E>::getWeight() const
{
	return m_weight;
}

template<typename V, typename E>
Vertex<V, E>* Edge<V, E>::getDestination()
{
	return m_destination;
}

template<typename V, typename E>
const Vertex<V, E>* Edge<V, E>::getDestination() const
{
	return m_destination;
}

#endif // !EDGE_H