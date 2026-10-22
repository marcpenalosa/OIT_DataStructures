/*********************************************
* Author:		Marc Penalosa
* Filename:		vertex.h
* Date Created:	02/24/26
*********************************************/
/**********************************************************************************
*
* Lab Assignment: Lab 14 - Shortest Path
*
* Overview:
*		This program implements Dijkstra's Shortest Path Algorithm to calculate the shortest distance between
*		two locations, their path, and provide an estimated time of arrival
*
* Input:
*		"Dijkstra Data.txt"
*
* Output:
*		Prints the path to take, the shortest distance, and the estimated time of arrival
*		Prompts the user if they want to continue
**********************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::getline;
#include <fstream>
using std::ifstream;
#include <cstring>
using std::strtok;
#include <iterator>
using std::iterator;
#include <list>
using std::list;
#include <vector>
using std::vector;
#include <stack>
using std::stack;

#include "graph.h"
#include "exception.h"

void Dijkstra(Graph<string, string> graph, string startNode, string endNode);
Graph<string, string> CreateGraph(string filename);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	string file = "Dijkstra Data.txt";
	Graph<string, string> graph = CreateGraph(file);
	string startNode;
	string endNode;
	bool done = false;

	while (!done)
	{
		cout << "Enter startNode: ";
		std::getline(cin, startNode);
		cout << "Enter endNode: ";
		std::getline(cin, endNode);

		try
		{
			Dijkstra(graph, startNode, endNode);
			cout << endl;
		}
		catch (Exception& ex)
		{
			cout << ex.getMessage() << endl << endl;
		}

		cout << "-- N/n for No" << endl;
		cout << "-- any other input you want for Yes" << endl;
		cout << "Continue?: ";
		// re-use startNode cause I can't be bothered :^)
		std::getline(cin, startNode);
		if (startNode == "N" || startNode == "n")
		{
			done = true;
		}
		cout << endl;
	}

	return 0;
}

/*
* Purpose:
*		calculates the shortest distance between two locations
* Precondition:
*		Graph must not be empty
*		startNode and endNode must exist
* Postcondition:
*		shortest distance, path taken, and estimated time of arrival are printed on console window
*/
void Dijkstra(Graph<string, string> graph, string startNode, string endNode)
{
	bool done = false;			// used to stop multiple while loops
	bool foundStart = false;	// checks to see if the starting node is found
	bool foundEnd = false;		// checks to see if the ending node is found
	int current = 0;			// a moving index for the vectors

	vector<Vertex<string, string>*> vertices;
	vector<int> distance;
	vector<string> predecessor;

	// **********************************************************
	// push back distance, vertex pointer, and predecessor as vData in different vectors
	// **********************************************************
	for (typename list<Vertex<string, string>>::iterator vList = graph.getVertices().begin(); vList != graph.getVertices().end(); vList++)
	{
		// push back the list of vertices
		vertices.push_back(&*vList);

		// initialize the distance vector to known values
		if (_stricmp(startNode.c_str(), vList->getVData().c_str()) == 0)
		{
			// change startNode to math the casing in the list so I don't have to do a bunch of stricmp later if needed
			startNode = vList->getVData();
			// algorithm wants the distance of starting node to 0
			distance.push_back(0);
			foundStart = true;
		}
		else
			distance.push_back(-1);

		// push back null values to predecessor vector
		predecessor.push_back("\0");

		// this increments current until I find the startNode index
		if (!foundStart)
			current++;

		// if this data is the end node
		if (_stricmp(endNode.c_str(), vList->getVData().c_str()) == 0)
		{
			// change endNode to math the casing in the list so I don't have to do a bunch of stricmp later if needed
			endNode = vList->getVData();
			foundEnd = true;
		}
	}
	if (!foundStart)
		throw Exception("could not find startNode");
	if (!foundEnd)
		throw Exception("could not find endNode");

	// **********************************************************
	// Calculate distance and predecessors
	// **********************************************************
	while (!done)
	{
		// get the list of edges of the current vertices to be used by an iterator, could have been done inside the for loop
		list<Edge<string, string>>& edges = vertices[current]->getEdges();

		// get the destination information using the current vertex's Edge list
		for (typename list<Edge<string, string>>::iterator eList = edges.begin(); eList != edges.end(); eList++)
		{
			if (!eList->getDestination()->isProcessed())
			{
				int destIndex = graph.getVertIndex(eList->getDestination()->getVData());	// index of destination vertex
				int newDistance = distance[current] + eList->getWeight();

				// if the destination vertex distance is untouched
				// or if the destination vertex's distance is bigger than the newDistance
				if (distance[destIndex] == -1 || newDistance <= distance[destIndex])
				{
					distance[destIndex] = newDistance;
					predecessor[destIndex] = vertices[current]->getVData();
				}
			}
		}
		vertices[current]->setProcessed(true);

		int distanceCheck = 0;
		bool foundUnprocessed = false;
		// check for the lowest distance
		for (int i = 0; i < vertices.size(); i++)
		{
			// if it's not processed and it's not untouched
			if (!vertices[i]->isProcessed() && distance[i] != -1)
			{
				// if this is the first unprocessed found
				if (foundUnprocessed == false)
				{
					distanceCheck = distance[i];
					current = i;
					foundUnprocessed = true;
				}
				else if (distance[i] < distanceCheck)
				{
					distanceCheck = distance[i];
					current = i;
				}
			}
		}

		if (!foundUnprocessed)
			done = true;
	}

	// **********************************************************
	// calculate shortest distance and estimated time
	// **********************************************************
	done = false;
	float time = 0;
	float totalTime = 0;
	int speed = 0;
	current = graph.getVertIndex(endNode);
	cout << "The shortest distance is " << distance[current] << endl;
	stack<string> paths;
	paths.push(vertices[current]->getVData());
	while (!done)
	{
		// if the predecessor isn't the starting node with the invalid value
		if (predecessor[current] != "\0")
		{
			// iterate through the edge list to find the edge that connects to the next vector
			// accumulates the time it take to go from one vertex to another
			for (typename list<Edge<string, string>>::iterator eList = vertices[current]->getEdges().begin(); eList != vertices[current]->getEdges().end(); eList++)
			{
				if (eList->getDestination()->getVData() == predecessor[current])
				{
					// adjust speed based on edge data
					if (eList->getEData() == "I-5")
						speed = 65;
					else
						speed = 55;

					// time = distance / speed. This formula will give you time in hours with decimal as minutes
					// rhs are both ints so promote one
					totalTime += (float)eList->getWeight() / speed;
				}
			}
			// push the predecessor of the current, then set current to that predecessor
			paths.push(predecessor[current]);
			current = graph.getVertIndex(predecessor[current]);
		}
		else
		{
			done = true;
		}
	}

	// print that shit
	cout << "Using the path of: ";
	while (!paths.empty())
	{
		// checks so that it doesn't append a ", " at the end
		if (paths.top() != endNode)
			cout << paths.top() << ", ";
		else
			cout << paths.top();
		paths.pop();
	}
	int hours = (int)totalTime;	// convert totalTime to int so that it tosses away the decimals
	int minutes = (totalTime - hours) * 60;	// takes the tossed decimal from above, multiplies it by 60 to convert it to int minutes
	cout << endl << "Estimated Time: " << hours << " hours and " << minutes << " minutes" << endl;
}

/*
* Purpose:
*		creates a Graph from a given input file
* Precondition:
*		file must exist in the directory
* Postcondition:
*		returns a Graph<string, string> using the given inputs
*/
Graph<string, string> CreateGraph(string filename)
{
	ifstream file;
	const int bufferSize = 256;
	char inputData[bufferSize];
	string startNode;
	string endNode;
	string path;
	int mileage;
	Graph<string, string> graph;
	file.open(filename);

	if (file.is_open())
	{
		// while you can get input from the file
		// getline( BUFFER, BUFFERSIZE, [Optional] DELIMITER )
		while (file.getline(inputData, bufferSize))
		{
			// strtok destructively parses an input until the delimiter
			startNode = strtok(inputData, ",");
			endNode = strtok(nullptr, ",");
			path = strtok(nullptr, ",");
			mileage = atoi(strtok(nullptr, "\n"));

			// insert all the inputs, ignores duplicates
			graph.InsertVertex(startNode);
			graph.InsertVertex(endNode);
			graph.InsertEdge(startNode, endNode, path, mileage);
		}
		file.close();
	}
	else
	{
		cout << "Could not open file" << endl;
	}

	return graph;
}