//Kevin Xu
//Node.cpp

#include "Node.h"
#include "Resistor.h"
#include "Rparser.h" 
#include <string>
#include <iostream>

#define MAX_RESISTORS_PER_NODE 5

using namespace std;


Node::Node() 
	: numRes(0), next_ID(0){
}


Node::~Node() {
}

bool Node::canAddResistor(int rIndex) {
	if (next_ID == MAX_RESISTORS_PER_NODE) {
		return false;
	}
	else return true;
}


void Node::addResistor(int rIndex) {

	resIDArray[next_ID] = rIndex;
	next_ID ++;
	return;
}


void Node::print(int nodeIndex) {
	cout << "Connections at node " << nodeIndex << ": " << numRes 
		<< " resistor(s) " << endl;

	for (int n = 0; n < next_ID; n++) {
		
	}
}


int Node::get_numRes() {
	return next_ID;
}