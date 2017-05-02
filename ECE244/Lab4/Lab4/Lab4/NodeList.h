//this is the class declearation for node linked list
#ifndef NODELIST_H
#define NODELIST_H

#include "Node.h"
#include "Resistor.h"
#include <string>


class NodeList
{
private:
	Node* head;
	double numNode;
public:
	NodeList();

	~NodeList();

	//search a Node by ID, return a point point to the Node
	//return NULL if the Node DNE
	Node* searchNode(int NodeID_);

	Resistor* searchRes(string name_);

	//insert a new Node
	//in nodeID asanding order
	void insertNode(int NodeID_);

	bool deleteNode(int NodeID_);

	bool print(int NodeID_);

	void printAll();

	void resetAll();

	//check the list and delete empty Node
	void update();

	bool voltSet();

	double sumI(int NodeID_);

	double solveOne(int NodeID_);

	void solveAll();
};






#endif
