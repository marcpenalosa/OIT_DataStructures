/*********************************************
* Author:		Marc Penalosa
* Filename:		graph.h
* Date Created:	02/24/26
*********************************************/
/**********************************************************************************
*
* Lab Assignment: Lab 13 - Graph
*
* Overview:
*		This program performs a series of tests to Graph, Vertex, and Edge classes to make
*		sure their function behaves as intended
*
* Input:
*		None
*
* Output:
*		Print strings on the console window that depends on whether or not
*		each tests passed
**********************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "graph.h"
#include "vertex.h"

void Display(int data);
void Display(string data);

// Edge Class
bool Edge_DefaultCtor();
bool Edge_ArgCtor();
bool Edge_CopyCtor();
bool Edge_MoveCtor();
bool Edge_OpEqCopy();
bool Edge_OpEqMove();

// Vertex Class
bool Vertex_DefaultCtor();
bool Vertex_ArgCtor();
bool Vertex_CopyCtor();
bool Vertex_MoveCtor();
bool Vertex_OpEqCopy();
bool Vertex_OpEqMove();
bool Vertex_setProcessed();
bool Vertex_Connect();
bool Vertex_ConnectEdgeAlreadyExist();
bool Vertex_DisconnectEdge();
bool Vertex_DisconnectEdgeEmpty();
bool Vertex_DisconnectEdgeDoesNotExist();
bool Vertex_DisconnectVertex();

// Graph Class
bool Graph_DefaultCtor();
bool Graph_CopyCtor();
bool Graph_MoveCtor();
bool Graph_OpEqCopy();
bool Graph_OpEqMove();
bool Graph_getNumVertices();
bool Graph_getVertices();
bool Graph_OpSubscript();
bool Graph_InsertVertex();
bool Graph_InsertEdge();
bool Graph_DeleteVertex();
bool Graph_DeleteEdge();
bool Graph_Purge();
bool Graph_PurgeEdges();

typedef bool(*FunctionPointer)();
FunctionPointer edge_functions[] = { Edge_DefaultCtor, Edge_ArgCtor, Edge_CopyCtor, Edge_MoveCtor, Edge_OpEqCopy, Edge_OpEqMove };
FunctionPointer vertex_functions[] = { Vertex_DefaultCtor, Vertex_ArgCtor, Vertex_CopyCtor, Vertex_MoveCtor, Vertex_OpEqCopy,
Vertex_OpEqMove, Vertex_setProcessed, Vertex_Connect, Vertex_ConnectEdgeAlreadyExist, Vertex_DisconnectEdge, Vertex_DisconnectEdgeEmpty,
Vertex_DisconnectEdgeDoesNotExist, Vertex_DisconnectVertex };
FunctionPointer graph_functions[] = { Graph_DefaultCtor, Graph_CopyCtor, Graph_MoveCtor, Graph_OpEqCopy, Graph_OpEqMove,
Graph_getNumVertices, Graph_getVertices, Graph_OpSubscript, Graph_InsertVertex, Graph_InsertEdge, Graph_DeleteVertex, 
Graph_DeleteEdge, Graph_Purge, Graph_PurgeEdges };

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for (FunctionPointer func : edge_functions)
	{
		if (func())
			cout << "passed" << endl;
		else
			cout << "***** FAILED *****" << endl;
	}

	for (FunctionPointer func : vertex_functions)
	{
		if (func())
			cout << "passed" << endl;
		else
			cout << "***** FAILED *****" << endl;
	}

	for (FunctionPointer func : graph_functions)
	{
		if (func())
			cout << "passed" << endl;
		else
			cout << "***** FAILED *****" << endl;
	}

	return 0;
}

void Display(int data)
{
	cout << "Vertex data: " << data << endl;
}

void Display(string data)
{
	cout << "Vertex data: " << data << endl;
}

bool Edge_DefaultCtor()
{
	cout << "*********************************************" << endl;
	cout << "Edge Functions" << endl;
	cout << "*********************************************" << endl;
	bool pass = true;

	Edge<string, string> edge;

	if (edge.getEData() != string())
		pass = false;
	if (edge.getWeight() != 0)
		pass = false;
	if (edge.getDestination() != nullptr)
		pass = false;

	cout << "Edge_DefaultCtor ";

	return pass;
}

bool Edge_ArgCtor()
{
	bool pass = true;

	Edge<string, string> edge("Baker Street", 100, nullptr);

	if (edge.getEData() != "Baker Street")
		pass = false;
	if (edge.getWeight() != 100)
		pass = false;
	if (edge.getDestination() != nullptr)
		pass = false;

	cout << "Edge_ArgCtor ";

	return pass;
}

bool Edge_CopyCtor()
{
	bool pass = true;

	Edge<string, string> edge("Baker Street", 100, nullptr);
	Edge<string, string> edgeCopy(edge);

	if (edgeCopy.getEData() != "Baker Street")
		pass = false;
	if (edgeCopy.getWeight() != 100)
		pass = false;
	if (edgeCopy.getDestination() != nullptr)
		pass = false;

	cout << "Edge_CopyCtor ";

	return pass;
}

bool Edge_MoveCtor()
{
	bool pass = true;

	Edge<string, string> edge("Baker Street", 100, nullptr);
	Edge<string, string> edgeCopy(std::move(edge));

	if (edgeCopy.getEData() != "Baker Street")
		pass = false;
	if (edgeCopy.getWeight() != 100)
		pass = false;
	if (edgeCopy.getDestination() != nullptr)
		pass = false;

	cout << "Edge_MoveCtor ";

	return pass;
}

bool Edge_OpEqCopy()
{
	bool pass = true;

	Edge<string, string> edge("Baker Street", 100, nullptr);
	Edge<string, string> edgeCopy = edge;

	if (edgeCopy.getEData() != "Baker Street")
		pass = false;
	if (edgeCopy.getWeight() != 100)
		pass = false;
	if (edgeCopy.getDestination() != nullptr)
		pass = false;

	cout << "Edge_OpEqCopy ";

	return pass;
}

bool Edge_OpEqMove()
{
	bool pass = true;

	Edge<string, string> edge("Baker Street", 100, nullptr);
	Edge<string, string> edgeCopy = std::move(edge);

	if (edgeCopy.getEData() != "Baker Street")
		pass = false;
	if (edgeCopy.getWeight() != 100)
		pass = false;
	if (edgeCopy.getDestination() != nullptr)
		pass = false;

	cout << "Edge_OpEqMove ";

	return pass;
}

bool Vertex_DefaultCtor()
{
	cout << endl << "*********************************************" << endl;
	cout << "Vertex Functions" << endl;
	cout << "*********************************************" << endl;
	bool pass = true;

	Vertex<string, string> vertex;

	if (vertex.getVData() != string())
		pass = false;
	if (vertex.isProcessed() != false)
		pass = false;
	if (vertex.getEdges().size() != 0)
		pass = false;

	cout << "Vertex_DefaultCtor ";
	return pass;
}

bool Vertex_ArgCtor()
{
	bool pass = true;

	Vertex<string, string> vertex("City of Marc");

	if (vertex.getVData() != "City of Marc")
		pass = false;
	if (vertex.isProcessed() != false)
		pass = false;
	if (vertex.getEdges().size() != 0)
		pass = false;

	cout << "Vertex_ArgCtor ";
	return pass;
}

bool Vertex_CopyCtor()
{
	bool pass = true;

	Vertex<string, string> vertex("City of Marc");
	Vertex<string, string> vertexCopy(vertex);

	if (vertexCopy.getVData() != "City of Marc")
		pass = false;
	if (vertexCopy.isProcessed() != false)
		pass = false;
	if (vertexCopy.getEdges().size() != 0)
		pass = false;

	cout << "Vertex_CopyCtor ";
	return pass;
}

bool Vertex_MoveCtor()
{
	bool pass = true;

	Vertex<string, string> vertex("City of Marc");
	Vertex<string, string> vertexCopy(std::move(vertex));

	if (vertexCopy.getVData() != "City of Marc")
		pass = false;
	if (vertexCopy.isProcessed() != false)
		pass = false;
	if (vertexCopy.getEdges().size() != 0)
		pass = false;

	cout << "Vertex_MoveCtor ";
	return pass;
}

bool Vertex_OpEqCopy()
{
	bool pass = true;

	Vertex<string, string> vertex("City of Marc");
	Vertex<string, string> vertexCopy = vertex;

	if (vertexCopy.getVData() != "City of Marc")
		pass = false;
	if (vertexCopy.isProcessed() != false)
		pass = false;
	if (vertexCopy.getEdges().size() != 0)
		pass = false;

	cout << "Vertex_OpEqCopy ";
	return pass;
}

bool Vertex_OpEqMove()
{
	bool pass = true;

	Vertex<string, string> vertex("City of Marc");
	Vertex<string, string> vertexCopy = std::move(vertex);

	if (vertexCopy.getVData() != "City of Marc")
		pass = false;
	if (vertexCopy.isProcessed() != false)
		pass = false;
	if (vertexCopy.getEdges().size() != 0)
		pass = false;

	cout << "Vertex_OpEqMove ";
	return pass;
}

bool Vertex_setProcessed()
{
	bool pass = true;

	Vertex<string, string> vertex;
	vertex.setProcessed(true);

	if (vertex.isProcessed() != true)
		pass = false;

	cout << "Vertex_setProcessed ";
	return pass;
}

bool Vertex_Connect()
{
	bool pass = true;
	bool passException = false;

	Vertex<string, string> vertex;
	Vertex<string, string> vertex2;
	vertex.Connect("Gay Street", 100, &vertex2);

	if (vertex.getEdges().front().getEData() != "Gay Street")
		pass = false;
	if (vertex.getEdges().front().getWeight() != 100)
		pass = false;
	if (vertex.getEdges().front().getDestination() != &vertex2)
		pass = false;

	try
	{
		vertex.Connect("Gay Street", 100, nullptr);
	}
	catch (Exception& ex)
	{
		passException = true;
	}

	cout << "Vertex_Connect ";
	return pass && passException;
}

bool Vertex_ConnectEdgeAlreadyExist()
{
	bool pass = true;

	Vertex<string, string> vertex;
	Vertex<string, string> vertex2;
	vertex.Connect("Gay Street", 100, &vertex2);
	vertex.Connect("Gay Street", 100, &vertex2);

	if (vertex.getEdges().size() != 1)
		pass = false;
	if (vertex.getEdges().front().getEData() != "Gay Street")
		pass = false;
	if (vertex.getEdges().front().getWeight() != 100)
		pass = false;
	if (vertex.getEdges().front().getDestination() != &vertex2)
		pass = false;

	cout << "Vertex_ConnectEdgeAlreadyExist ";
	return pass;
}

bool Vertex_DisconnectEdge()
{
	bool pass = true;

	Vertex<string, string> vertex;
	Vertex<string, string> vertex2;
	vertex.Connect("Gay Street", 100, &vertex2);
	vertex.Disconnect("Gay Street");

	if (!vertex.getEdges().empty())
		pass = false;

	cout << "Vertex_DisconnectEdge ";
	return pass;
}

bool Vertex_DisconnectEdgeEmpty()
{
	bool pass = true;

	Vertex<string, string> vertex;
	try
	{
		vertex.Disconnect("Gay Street");
	}
	catch (Exception& ex)
	{
		pass = true;
	}

	cout << "Vertex_DisconnectEdgeEmpty ";
	return pass;
}

bool Vertex_DisconnectEdgeDoesNotExist()
{
	bool pass = false;

	Vertex<string, string> vertex;
	Vertex<string, string> vertex2;
	vertex.Connect("Marc Street", 500, &vertex2);

	try
	{
		vertex.Disconnect("Gay Street");
	}
	catch (Exception& ex)
	{
		pass = true;
	}

	cout << "Vertex_DisconnectEdgeDoesNotExist ";
	return pass;
}

bool Vertex_DisconnectVertex()
{
	bool pass = true;
	bool passException = false;

	Vertex<string, string> vertex1;
	Vertex<string, string> vertex2;
	vertex1.Connect("Marc Street", 500, &vertex2);
	vertex1.Disconnect(&vertex2);

	if (!vertex1.getEdges().empty())
		pass = false;

	try
	{
		vertex1.Disconnect(&vertex2);
	}
	catch (Exception& ex)
	{
		passException = true;
	}

	cout << "Vertex_DisconnectVertex ";
	return pass && passException;
}

bool Graph_DefaultCtor()
{
	cout << endl << "*********************************************" << endl;
	cout << "Graph Functions" << endl;
	cout << "*********************************************" << endl;
	bool pass = true;
	
	Graph<string, string> graph;

	if (graph.getNumVertices() != 0)
		pass = false;

	cout << "Graph_DefaultCtor ";
	return pass;
}

bool Graph_CopyCtor()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Raccoon City");
	graph.InsertEdge("Marc Town", "Raccoon City", "Highway to Hell", 50);
	Graph<string, string> graphCopy(graph);

	// Delete the edge in the old graph to check that the new edges doesn't point to old data
	graph.DeleteEdge("Highway to Hell");

	if (graphCopy.getNumVertices() != 2)
		pass = false;
	if (graphCopy["Marc Town"].front().getDestination()->getVData() != "Raccoon City")
		pass = false;

	cout << "Graph_CopyCtor ";
	return pass;
}

bool Graph_MoveCtor()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Raccoon City");
	graph.InsertEdge("Marc Town", "Raccoon City", "Highway to Hell", 50);
	Graph<string, string> graphCopy(std::move(graph));

	if (graphCopy.getNumVertices() != 2)
		pass = false;
	if (graphCopy["Marc Town"].front().getDestination()->getVData() != "Raccoon City")
		pass = false;

	cout << "Graph_MoveCtor ";
	return pass;
}

bool Graph_OpEqCopy()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Raccoon City");
	graph.InsertEdge("Marc Town", "Raccoon City", "Highway to Hell", 50);
	Graph<string, string> graphCopy = graph;

	// Delete the edge in the old graph to check that the new edges doesn't point to old data
	graph.DeleteEdge("Highway to Hell");

	if (graphCopy.getNumVertices() != 2)
		pass = false;
	if (graphCopy["Marc Town"].front().getDestination()->getVData() != "Raccoon City")
		pass = false;

	cout << "Graph_OpEqCopy ";
	return pass;
}

bool Graph_OpEqMove()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Raccoon City");
	graph.InsertEdge("Marc Town", "Raccoon City", "Highway to Hell", 50);
	Graph<string, string> graphCopy = std::move(graph);

	if (graphCopy.getNumVertices() != 2)
		pass = false;
	if (graphCopy["Marc Town"].front().getDestination()->getVData() != "Raccoon City")
		pass = false;

	cout << "Graph_OpEqMove ";
	return pass;
}

bool Graph_getNumVertices()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Stardew Valley");
	graph.InsertVertex("Otter Town");

	if (graph.getNumVertices() != 3)
		pass = false;

	cout << "Graph_getNumVertices ";
	return pass;
}

bool Graph_getVertices()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Otter Town");

	if (graph.getVertices().begin()->getVData() != "Otter Town")
		pass = false;

	cout << "Graph_getVertices ";
	return pass;
}

bool Graph_OpSubscript()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Otter Town");
	graph.InsertEdge("Otter Town", "Marc Town", "Bear Highway", 50);
	const Graph<string, string> constGraph = graph;

	if (graph["Marc Town"].front().getEData() != "Bear Highway")
		pass = false;
	if (graph["Otter Town"].front().getEData() != "Bear Highway")
		pass = false;
	if (graph["Marc Town"].front().getDestination()->getVData() != "Otter Town")
		pass = false;
	if (graph["Otter Town"].front().getDestination()->getVData() != "Marc Town")
		pass = false;

	// constGraph can only read data. Nice
	constGraph["Marc Town"].front().getDestination()->isProcessed();

	cout << "Graph_OpSubscript ";
	return pass;
}

bool Graph_InsertVertex()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Otter Town");
	// double insertion
	graph.InsertVertex("Otter Town");
	// triple insertion
	graph.InsertVertex("Otter Town");
	// quadruple insertion
	graph.InsertVertex("Otter Town");

	if (graph.getNumVertices() != 2)
		pass = false;

	cout << "Graph_InsertVertex ";
	return pass;
}

bool Graph_InsertEdge()
{
	bool pass = true;
	bool passException = false;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Otter Town");
	graph.InsertEdge("Marc Town", "Otter Town", "Bear Highway", 50);

	// test non-existent Vertices
	try
	{
		graph.InsertEdge("MAAAARC TOWWWWWNNNN", "OTTER TOWNN", "Yowza", 60);
	}
	catch (Exception& ex)
	{
		passException = true;
	}

	cout << "Graph_InsertEdge ";
	return pass && passException;
}

bool Graph_DeleteVertex()
{
	bool pass = true;
	bool passException = false;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Otter Town");
	graph.InsertVertex("Bear Town");
	graph.InsertEdge("Marc Town", "Otter Town", "Road", 50);
	graph.InsertEdge("Marc Town", "Bear Town", "Road", 50);
	graph.InsertEdge("Otter Town", "Bear Town", "Road", 50);
	graph.DeleteVertex("Marc Town");

	if (graph.getNumVertices() != 2)
		pass = false;

	try
	{
		graph.DeleteVertex("AAAAAAAAAAAAAAAAAAAAAAAAA");
	}
	catch (Exception& ex)
	{
		passException = true;
	}

	cout << "Graph_DeleteVertex ";
	return pass && passException;
}

bool Graph_DeleteEdge()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Otter Town");
	graph.InsertVertex("Bear Town");
	graph.InsertEdge("Marc Town", "Otter Town", "Road", 50);
	graph.InsertEdge("Marc Town", "Otter Town", "Faster Road", 10);
	graph.InsertEdge("Marc Town", "Bear Town", "Road", 50);
	graph.InsertEdge("Otter Town", "Bear Town", "Road", 50);
	Graph<string, string> graphCopy(graph);

	// Delete Edge that deletes all Edges in between two Vertices
	graph.DeleteEdge("Marc Town", "Otter Town");
	if (graph["Marc Town"].size() != 1)
		pass = false;
	if (graph["Otter Town"].size() != 1)
		pass = false;
	if (graph["Bear Town"].size() != 2)
		pass = false;

	// DeleteEdge that deletes all Edges with the matching identifier
	graphCopy.DeleteEdge("Road");
	if (graphCopy["Marc Town"].size() != 1)
		pass = false;
	if (graphCopy["Otter Town"].size() != 1)
		pass = false;
	if (graphCopy["Bear Town"].size() != 0)
		pass = false;

	cout << "Graph_DeleteEdge ";
	return pass;
}

bool Graph_Purge()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Otter Town");
	graph.InsertVertex("Bear Town");
	graph.InsertEdge("Marc Town", "Otter Town", "Road", 50);
	graph.InsertEdge("Marc Town", "Otter Town", "Faster Road", 10);
	graph.InsertEdge("Marc Town", "Bear Town", "Road", 50);
	graph.InsertEdge("Otter Town", "Bear Town", "Road", 50);

	graph.Purge();
	if (graph.getNumVertices() != 0)
		pass = false;

	cout << "Graph_Purge ";
	return pass;
}

bool Graph_PurgeEdges()
{
	bool pass = true;

	Graph<string, string> graph;
	graph.InsertVertex("Marc Town");
	graph.InsertVertex("Otter Town");
	graph.InsertVertex("Bear Town");
	graph.InsertEdge("Marc Town", "Otter Town", "Road", 50);
	graph.InsertEdge("Marc Town", "Otter Town", "Faster Road", 10);
	graph.InsertEdge("Marc Town", "Bear Town", "Road", 50);
	graph.InsertEdge("Otter Town", "Bear Town", "Road", 50);

	graph.PurgeEdges();
	if (graph.getNumVertices() != 3)
		pass = false;

	cout << "Graph_PurgeEdges ";
	return pass;
}
