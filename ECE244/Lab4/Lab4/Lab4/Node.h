
/*
* File:   Node.h
* Author: JC and VB
* Author: TSA
*
* Updated on August 24, 2016, 01:40 PM
* Created on October 6, 2013, 12:58 PM
*/

#ifndef NODE_H
#define NODE_H

#include <string>
#include "ResistorList.h"
#include "Resistor.h"


class Node
{
private:
	int NodeID;
	int numRes;
	double voltage;
	bool setted;
	ResistorList resList;
	Node* next;


public:
	Node(int NodeID_);

	int getID();

	Node* getNext();

	Resistor* getHead();

	int getNumRes();

	void setNext(Node* next_);

	double getVoltage();

	void setVoltage(double volt);

	void unsetVoltage();

	double changeVoltage(double volt);

	//add a new Resisitor into the resList (not in order)
	void addResistor(string name_, double resistence_, int endNode0_, int endNode1_);

	Resistor* searchRes(string name_);

	// prints the whole node
	// nodeIndex is the position of this node in the node array.
	void print();

	bool deleteRes(string name_);

	void resetList();

	double sumRPar();

	bool voltSet();

};

#endif	/* NODE_H */


