//this is the function definition for node linked list

#include "Node.h"
#include "NodeList.h"
#include "Resistor.h"
#include "Rparser.h" 
#include <string>
#include <iostream>

#define MIN_ITERATION_CHANGE 0.0001


NodeList::NodeList() {
	head = NULL;
	numNode = 0;
}

NodeList::~NodeList() {
	Node* current;

	while (head != NULL) {
		current = head;
		head = head->getNext();
		delete current;
	}
}


Node* NodeList::searchNode(int NodeID_) {
	Node* current;
	current = head;

	while (current != NULL) {
		if (current->getID() == NodeID_) return current;
		else current = current->getNext();
	}
	return NULL;
}


Resistor* NodeList::searchRes(string name_) {
	Node* current;
	current = head;

	while (current != NULL) {
		if (current->searchRes(name_) != NULL) {
			return current->searchRes(name_);
		}
		else current = current->getNext();
	}

	return NULL;
}


void NodeList::insertNode(int NodeID_) {
	Node* current;
	Node* prev;
	Node* newNode;
	current = head;
	prev = NULL;
	newNode = new Node(NodeID_); // make a new Node

	if (current == NULL) {  //when NodeList is empty
		head = newNode;
		head->setNext(NULL);
		numNode++;
		return;
	}

	while (current != NULL) { //NodeID- is not the biggest
		if (prev == NULL && current->getID() > NodeID_) { //NodeID_ is the smallest
			head = newNode;
			head->setNext(current);
			numNode++;
			return;
		}
		else if (current->getID() > NodeID_) {
			prev->setNext(newNode);
			newNode->setNext(current);
			numNode++;
			return;
		}
		else {
			prev = current;
			current = current->getNext();
		}
	}

	prev->setNext(newNode);  //NodeID_ is the lagest
	newNode->setNext(current);
	numNode++;
}


bool NodeList::deleteNode(int NodeID_) {
	Node* current;
	Node* prev;
	current = head;
	prev = NULL;

	while (current != NULL && current->getID() != NodeID_) {
		prev = current;
		current = current->getNext();
	}

	if (current == NULL) return false; //no Node exsit
	else if (prev == NULL) head = current->getNext();
	else
		prev->setNext(current->getNext());

	delete current;
	numNode--;
	return true;
}


bool NodeList::print(int NodeID_) {
	Node* node;

	node = searchNode(NodeID_);

	if (node != NULL) {
		node->print();
		return true;
	}
	else return false;
}


void NodeList::printAll() {
	Node* current;
	current = head;

	cout << "Print:" << endl;

	while (current != NULL) {
		current->print();
		current = current->getNext();
	}
}


void NodeList::resetAll() {
	Node* current;
	current = head;

	while (current != NULL) {
		current->resetList();
		current = current->getNext();
	}
}


void NodeList::update() {
	Node* current;
	current = head;

	while (current != NULL) {
		Node* next;
		if (current->getNumRes() == 0) {
			next = current->getNext();
			deleteNode(current->getID());
			numNode--;
		}
		current = next;
	}
}


bool NodeList::voltSet() {
	Node* current;
	current = head;

	while (current != NULL) {
		if (current->voltSet()) return true;
		current = current->getNext();
	}
	return false;
}


double NodeList::sumI(int NodeID_) {
	Resistor* current;
	double answer = 0;
	current = searchNode(NodeID_)->getHead();

	while (current != NULL) {
		double volt;
		if (current->getNode0() == NodeID_)
			volt = searchNode(current->getNode1())->getVoltage();
		else
			volt = searchNode(current->getNode0())->getVoltage();

		answer = answer + (volt / current->getResistance());

		current = current->getNext();
	}

	return answer;
}


double NodeList::solveOne(int NodeID_) {
	double sumRinv = searchNode(NodeID_)->sumRPar();
	double sumofI = sumI(NodeID_);

	double newVolt = sumRinv * sumofI;

	return searchNode(NodeID_)->changeVoltage(newVolt);
}


void NodeList::solveAll() {
	Node* current;
	
	double stable = 4.44;

	while (stable > (MIN_ITERATION_CHANGE * numNode)) {
		current = head;
		stable = 0;
		while (current != NULL) {
			stable = stable + solveOne(current->getID());
			current = current->getNext();
		}
	}

	Node* printCurrent;
	cout << "Solve:" << endl;
	printCurrent = head;
	while (printCurrent != NULL) {
		cout << "Node " << printCurrent->getID() << ": " 
			<< printCurrent->getVoltage() << endl;

		printCurrent = printCurrent->getNext();
	}
}
