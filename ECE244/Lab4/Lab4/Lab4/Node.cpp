//Kevin Xu
//Node.cpp

#include "Node.h"
#include "Resistor.h"
#include "Rparser.h" 
#include <string>
#include <iostream>
#include <cmath>


using namespace std;


Node::Node(int NodeID_)
	: NodeID(NodeID_) {

	next = NULL;
	numRes = 0;
	voltage = 4.44;
	setted = false;
}


int Node::getID() {
	return NodeID;
}


Node* Node::getNext() {
	return next;
}


Resistor* Node::getHead() {
	return resList.getHead();
}


int Node::getNumRes() {
	return numRes;
}


void Node::setNext(Node* next_) {
	next = next_;
}


double Node::getVoltage() {
	return voltage;
}

void Node::setVoltage(double volt_) {
	voltage = volt_;
	setted = true;
}


void Node::unsetVoltage() {
	voltage = 0;
	setted = false;
}


double Node::changeVoltage(double newvolt) {
	if (!setted) {
		double diff = fabs(voltage - newvolt);
		voltage = newvolt;
		return diff;
	}
	else return 0;
}


void Node::addResistor(string name_, double resistence_, int endNode0_, int endNode1_) {
	resList.insertResistor(name_, resistence_, endNode0_, endNode1_);
	numRes++;
}


Resistor* Node::searchRes(string name_) {
	return resList.searchResistor(name_);
}


void Node::print() {
	cout << "Connections at node " << NodeID << ": " << numRes
		<< " resistor(s) " << endl;

	resList.printAll();

}


bool Node::deleteRes(string name_) {
	numRes--;
	return resList.deletResistor(name_);
}


void Node::resetList() {
	resList.resetList();
	numRes = 0;
}


double Node::sumRPar() {
	return resList.sumRpar();
}


bool Node::voltSet() {
	return setted;
}