#include "Disjoint_Sets.h"
#include <iostream>
#include "Graph.h"

/* Postconditions: Inserts a bi-directional between node1 and node2 with the given weight
*/
void Graph::insertEdge(int node1, int node2, int weight) {
	node[node1].push_back(Edge(node1,node2,weight));
	//since it is an undirected graph, the other way also has an edge
	node[node2].push_back(Edge(node2,node1,weight));
	totalEdges++;

}

/* Preconditions: From and to are of vertices of the graph
   Postconditions: Returns true if there is an edge between from and to and false otherwise
*/
bool Graph::isEdge(int from, int to) {
	vector<Edge> allEdgeFrom = node[from];
	for (int i=0; i< allEdgeFrom.size();i++)
	{
		if (allEdgeFrom[i].to==to)
			return true;
	}
	return  false;
}

/* Preconditions: From and to are vertices of the graph between which there is an edge
   Postconditions: Returns the weight of the edge between from and to
*/
int Graph::getWeight(int from, int to) {
	int vectorNumber;
	vector<Edge> allEdgeFrom = node[from];
	for (int i = 0; i < allEdgeFrom.size(); i++)
	{
		if (allEdgeFrom[i].to == to)
			vectorNumber = i;;
	}
	return  allEdgeFrom[vectorNumber].weight;
}

/* Preconditions: The graph is connected
   Postconditions: Returns a new graph object containing only the edges representing
   the minimum spanning tree of the graph
*/

Graph Graph::generateMST() {
   //Implementing Kruskals Algorithm to find MST
	vector <Edge> sortedEdges;
	Edge minimum = Edge(-1,-1,100000);
	Graph calculatedMST;
	//STEP 1: Get All Sorted Edges by selection sort
	for (int n = 0; n < totalEdges; n++)
	{
		minimum.weight = 100000;
		for (map<int, vector<Edge>>::iterator i = node.begin(); i != node.end(); i++)
		{
			for (int j = 0; j < i->second.size(); j++)
			{
				if (i->second[j].weight < minimum.weight & (!isAdded(sortedEdges,i->second[j].from, i->second[j].to)))
					minimum = i->second[j];
			}
		}
			sortedEdges.push_back(minimum);	
	}

	Disjoint_Sets set(node.size());
	//STEP 2 IMPLEMENT DISJOINT TO AND SETS TO FIND KRUSKALS
	//**GO TO THE SMALLEST UNVISITED EDGE AND CHECK IF IT CREATES CYCLE**//
	for(int i=0; i<sortedEdges.size();i++)
	{
			//CHECK IF IT CREATES A CYCLE
			if ((set.find(sortedEdges[i].from)) != (set.find(sortedEdges[i].to)))
			{
				if (set.find(sortedEdges[i].from) != -1)
				{
					set.union_set(set.find(sortedEdges[i].from), set.find(sortedEdges[i].to));
					calculatedMST.insertEdge(sortedEdges[i].from, sortedEdges[i].to, sortedEdges[i].weight);
				}
			}
	}

/*#pragma region Debugging
	for (int i=0; i<sortedEdges.size(); i++)
	{
		cout << "From: "<<sortedEdges[i].from<<" To: "<<sortedEdges[i].to<<" Weight: "<<sortedEdges[i].weight<<endl;
	}
#pragma endregion */
	return calculatedMST;
}
bool Graph::isAdded(vector<Edge>& sortedEdges, int from, int to)
{
	for (int i=0; i< sortedEdges.size();i++)
	{
		if (sortedEdges[i].from == from & sortedEdges[i].to == to)
			return true;
		if (sortedEdges[i].from == to & sortedEdges[i].to == from)
			return true;
	}
	return false;
}

int Graph::getVerticeCount()
{
	int count = 0;
	map<int, vector<Edge>>::iterator iter;
	for (iter = node.begin(); iter != node.end(); iter++)
	{
		//increment count for each vertex visited
		count++;
	}
	return count;
}

/*	returns lowest distance univisited vertex
	and marks the vertex visited
	Takes in a reference to the added paths*/
int Graph::getLowestVertexFromPath(vector<Paths>& thePaths)
{
	int minimum = 2000;	//2000 considered as infinite in this case
	int minIndex = 0;
	for (int i=0; i<thePaths.size(); i++)
	{
		if (thePaths[i].dis < minimum & !thePaths[i].visited)
		{
			minimum = thePaths[i].dis;
			minIndex = i;
		}
		//After this for loop, minimum shall contain the lowest index
	}
	//mark the vertex in the path visited and return the vertex number for next current
	thePaths[minIndex].visited = true;
	return minIndex;
}


/* Preconditions: The graph is connected
   Postconditions: Runs Dijkstra's Algorithm from source, printing to cout a line for
   each vertex (except the source). Each line should contain the vertex number, the shortest
   distance to that vertex, and the previous vertex on the shortest path to that vertex.
   Each value on the line should be separated by a single space. The vertices should be printed
   in order from lowest numbered vertex to highest numbered vertex.
*/

/*Considering -2000 as NULL and 2000 as infinite*/
void Graph:: printDijkstra(int source) {
	//Creating a vector of paths for Dijkstra
	int preDis = 0;	//Keeps track of the distance to current in order to make calculation
	vector<Paths> paths;
	/*Considering 2000 as inf, add all path as distance infinite and prev null*/
	for (int i = 0; i < getVerticeCount(); i++)
	{
		paths.push_back(Paths(2000, -2000));
	}
	/*Considering -2000 as null add the source to the list*/
	paths[source].Replace(0, -2000);
	for (int i=0; i< getVerticeCount()-1; i++)
	{
		//select current vertex as the one that can be reached in shortest time.
		int currentVertex = getLowestVertexFromPath(paths);
		preDis = paths[currentVertex].dis;
		//go through all edges of currentVertex and check if path needs to be updated
		for (int n=0; n<node[currentVertex].size();n++)
		{
			 if (node[currentVertex][n].weight+preDis<paths[node[currentVertex][n].to].dis)
			 {
				 //update required now
				 paths[node[currentVertex][n].to].Replace(node[currentVertex][n].weight + preDis, currentVertex);
			 }
		}
	}
	//Passing the paths to cout as needed
	for (int i=0; i<paths.size();i++)
	{
		if (i!=source)
			cout << i << " " << paths[i].dis << " " <<paths[i].previous<<endl;
	}
}

/* Optional Function: You may use this function for debugging purposes if you wish
   Preconditions: None
   Postconditions: Prints the graph in any format you wish
*/
void Graph::printGraph() {
	//iterate through the maps
	map<int, vector<Edge>>::iterator iter;
	for(iter=node.begin();iter!=node.end();iter++)
	{
		//iterate throught the edge list to show edges-
		cout << "Node Integer: " << iter->first << " \n Edges: \n";
		for(int i=0; i< iter->second.size(); i++)
		{
			cout << (iter->second)[i].to<<endl;
		}
		cout << "------"<<endl;
	}
}