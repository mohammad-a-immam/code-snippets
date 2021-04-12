//
//  Graph.h
//  
//
//  Created by Resch,Cheryl on 7/12/19.
//  Assignment Worked on by Mohammad Immam 11/08/19
//

#ifndef Graph_h
#define Graph_h
#include <map>
#include <vector>

using namespace std;

struct Edge
{
	int from;
    int to;
    int weight;
    bool visited;

	//to Create an Edge of a node
	Edge(int from, int to, int weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
		this->visited = false;
	}
};

//This Struct will be used by Dijkstra to hold shortest Path information//
//The struct serves as a 3D array//
struct Paths
{
	//Vertex number is the index number of the path
	int dis;		//shortest distance from source to the given vertex
	int previous;		//The previous vertex to reach this vertex;
	bool visited;

	Paths(int sDis, int prev)
	{
		this->dis = sDis;
		this->previous = prev;
		this->visited = false;
	}

	void Replace(int sDis, int prev)
	{
		this->dis = sDis;
		this->previous = prev;
	}
};

class Graph
//assume vertices are numbered consecutively and start with 0?
//otherwise disjoint sets becomes more complicated.  do we want that?

{
    //Graph data structure here or create another class to implement it
public:
    void insertEdge(int node1, int node2, int weight);  //inserts new edge in graph
    bool isEdge(int from, int to);  //returns true if there is an edge between the vertices from and to
    int getWeight(int from, int to);  //returns the weight of the edge between the vertices from and to
    Graph generateMST();
	void printDijkstra(int source);
    void printGraph(); //prints graph in a format sorted by ascending vertex and edge list

	//All private members of the Graph that returns information About the Graph.
private:
	//All data nodes will be stored as maps<int, vector<int>> list will return all adjacent edges
	map<int, vector<Edge>> node;
	int totalEdges = 0;
	int totalVertices = 0;

	//helper to find sorted Edge
	bool isAdded(vector <Edge>& sortedEdges, int from, int to);
	//helpers for Dijkstras
	int getVerticeCount();
	/*returns lowest distance univisited path*/
	int getLowestVertexFromPath(vector<Paths>& thePaths);	
};

#endif /* Graph_h */
