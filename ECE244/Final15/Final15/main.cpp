#include <iostream>

using namespace std;

class GNode
{
private:
	int value;
	int numEdge;
	GNode **edges; //array of pointers to other node
	bool visited;
public:
	int getValue() {
		return value;
	}


	int getNumEdge() {
		return numEdge;
	}


	GNode* getEdges(int index) {
		return edges[index];
	}


	bool ifVisited() {
		return visited;
	}


	void setVisFlag() {
		visited = true;
	}
};



class Graph
{
private:
	GNode *anchor;

};