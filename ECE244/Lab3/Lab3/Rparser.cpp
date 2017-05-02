/*
* File:   Parcer.cpp
* Author: Kevin Xu
* ECE244 Lab2
*
* Created on September 27, 2016, 11:12 PM
*/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "Node.h"
#include "Resistor.h"
#include "Rparser.h"



#define MAX_NODE_NUMBER 5000

using namespace std;



ResNet::ResNet(int const maxResistors, int maxNodes)
	: maxResistors(maxResistors),
	maxNodes(maxNodes),
	all_resistor(new Resistor *[maxResistors]),
	all_node(new Node *[maxNodes]),
	nextnIndex(0),
	nextrIndex(0) {
}


ResNet::~ResNet() {
	for (int n = 0; n < nextrIndex; n++) {
		if (all_resistor[n] != NULL) {
			delete all_resistor[n];
		}
	}
	delete[] all_resistor;

	for (int n = 0; n < nextnIndex; n++) {
		if (all_node[n] != NULL) {
			delete all_node[n];
		}
	}
	delete[] all_node;
}


void ResNet::reset(int const maxNodes_, int const maxResistors_) {
	maxResistors = maxResistors_;
	maxNodes = maxNodes_;
	nextnIndex = 0;
	nextrIndex = 0;

	for (int n = 0; n < nextrIndex; n++) { //delete all resistors
		if (all_resistor[n] != NULL) {
			delete all_resistor[n];
		}
	}

	for (int n = 0; n < nextnIndex; n++) { //delete all nodes
		if (all_node[n] != NULL) {
			delete all_node[n];
		}
	}

	for (int n = 0; n < maxNodes; n++) { //make new nodes
		all_node[n] = new Node;
	}
}



int ResNet::insertResistor(string name_, double resistance_, int endpoints_[2]) {

	if (endpoints_[0] >= maxNodes) {
		
		return 2;
	    
	}
	else if (endpoints_[1] >= maxNodes) {
		
		return 3;
	}
	else {
		if (!(all_node[endpoints_[0]]->canAddResistor(nextrIndex) & all_node[endpoints_[1]]->canAddResistor(nextrIndex))) {
			return 1;
		}

		all_resistor[nextrIndex] = new Resistor(nextrIndex, name_, resistance_, endpoints_);

		all_node[endpoints_[0]]->addResistor(nextrIndex);
		all_node[endpoints_[1]]->addResistor(nextrIndex);

		nextrIndex++;
	}
    return 0;
}

Resistor* ResNet::get_resistor(int rIndex) {
	if (rIndex >= nextrIndex) return NULL;
	else return all_resistor[rIndex];
}


int ResNet::printR(string name_) {
	int rIndex = -1;
	for (int n = 0; n < nextrIndex; n++) {
		if (name_.compare(all_resistor[n]->getName()) == 0) {
			rIndex = n;
			break;
		}
		
	}
	if (rIndex == -1) {
		return 1;
	}
	else {
		all_resistor[rIndex]->print();
		return 0;
	}
}


void ResNet::printAll() {
	for (int n = 0; n < nextrIndex; n++) {
		all_resistor[n]->print();
	}
	return;
}


int ResNet::printNode(int nodeID_) {
	if (nodeID_ >= maxNodes) return 1;
	else {
		for (int n = 0; n < nextrIndex; n++) {
			if ((all_resistor[n]->getNode0() == nodeID_) 
				| (all_resistor[n]->getNode1() == nodeID_)) {
				all_resistor[n]->print();
			}
		}
	}
	return 0;
}


bool ResNet::checkRFull() {
	if (nextrIndex == maxResistors) return true;
	else return false;
}


bool ResNet::nameExist(string name_) {
	bool out = false;
	for (int n = 0; n < nextrIndex; n++) {
		if (name_.compare(all_resistor[n]->getName()) == 0) {
			out = true;
		}
	}
	return out;
}


int ResNet::get_maxNodes() {
	return maxNodes;
}


void ResNet::change_resistance(string name_, double value_) {
	for (int n = 0; n < nextrIndex; n++) {
		if (name_.compare(all_resistor[n]->getName()) == 0) {
			all_resistor[n]->setResistance(value_);
		}
	}
}


double ResNet::get_resistance(string name_) {
	for (int n = 0; n < nextrIndex; n++) {
		if (name_.compare(all_resistor[n]->getName()) == 0) {
			return all_resistor[n]->getResistance();
		}
	}
	return 0;
}


int ResNet::nodeResNum(int nodeID_) {
	return all_node[nodeID_]->get_numRes();
}

	//function DEF for class ResNet
//--------------------------------------------------------------------------------------------------
	//globle funtions

int checkForName(stringstream& lineStream, string name) {
	if (lineStream.fail()) {
		cout << "Error: invalid argument" << endl;
		lineStream.clear();
		return 1;
	}
	if (name.compare("all") == 0) {
		cout << "Error: resistor name cannot be keyword \"all\"" << endl;
		return 1;
	}
	else return 0;

}


int checkForResistance(stringstream& lineStream, double resistance) {
	if (lineStream.fail()) {
		cout << "Error: invalid argument" << endl;
		lineStream.clear();
		return 1;
	}
	if (resistance < 0) {
		cout << "Error: negative resistance" << endl;
		return 1;
	}
	else return 0;
}


int checkForNode(stringstream& lineStream, int nodeID1, int nodeID2) {

	if (lineStream.fail()) {
		cout << "Error: invalid argument" << endl;
		lineStream.clear();
		return 1;
	}
	else if ((nodeID1 > MAX_NODE_NUMBER) | (nodeID1 < 0)) {
		cout << "Error: node " << nodeID1 << " is out of permitted range 0-"
			<< MAX_NODE_NUMBER << endl;
		return 1;
	}
	else if ((nodeID2 > MAX_NODE_NUMBER) | (nodeID2 < 0)) {
		cout << "Error: node " << nodeID2 << " is out of permitted range 0-"
			<< MAX_NODE_NUMBER << endl;
		return 1;
	}
	else if (nodeID1 == nodeID2) {
		cout << "Error: both terminals of resistor connect to node " << nodeID1
			<< endl;
		return 1;
	}
	else return 0;
}


int checkForNodeNotPrinting(stringstream& lineStream, int nodeID1, int nodeID2) {
	if (lineStream.fail()) {
		lineStream.clear();
		return 1;
	}
	else return 0;
}




void parser() {       //----------------------------Parser Here

	string line, command, name, node, All;
	int  nodeID1, nodeID2, maxNodeNumber, maxResistors;
	double resistance;

	//____________________________set float precision
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	//_______________________________________________  

	ResNet NewRNet(0, 0);  // set up the network
	ResNet* NewRNetLocation = &NewRNet;

	while (true) {


		cout << ">"; //insert sign
		getline(cin, line); // extracting the hole line of input
		stringstream lineStream(line);
		lineStream >> command;
		if (lineStream.eof()) break;   //check for eptey input and quit


		if (command.compare("maxVal") == 0) {   //maxVal-------------------------
			lineStream >> maxNodeNumber >> maxResistors;

			if ((maxNodeNumber <= 0) | (maxResistors <= 0)) {   // error checking
				cout << "Error: maxVal argument must be greater than o" << endl;
				continue;
			}

			else {
				cout << "New network: max node number is " << maxNodeNumber
					<< "; max resistors is " << maxResistors << endl;
				NewRNet.reset(maxNodeNumber, maxResistors);
			}
		}

		else if (command.compare("insertR") == 0) {     //insertR---------------


			lineStream >> name;                //check for error on name
			if (checkForName(lineStream, name)) continue;
			else if (lineStream.eof()) {    //check for too little argument
				lineStream.clear();
				cout << "Error: too little argument" << endl;
				continue;
			}

			lineStream >> resistance;         // check for error on resistance
			if (checkForResistance(lineStream, resistance)) continue;
			else if (lineStream.eof()) {    //check for too little argument
				lineStream.clear();
				cout << "Error: too little argument" << endl;
				continue;
			}

			lineStream >> nodeID1;
			if (checkForNode(lineStream, nodeID1, nodeID1 + 1)) continue;
			else if (lineStream.eof()) {    //check for too little argument
				lineStream.clear();
				cout << "Error: too little argument" << endl;
				continue;
			}

			lineStream >> nodeID2; //check for error on nodeID
			if (checkForNode(lineStream, nodeID1, nodeID2)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}
			if (NewRNet.checkRFull()) {  //check if the resistor array is full
				cout << "Error: resistor array is full" << endl;
				continue;
			}

			if (NewRNet.nameExist(name)) {  //check if the name already exist
				cout << "Error: resistor " << name << " already exists"
					<< endl;
				continue;
			}
			// error checking above
			//------------------------------------------------------
			// action below

			int nodes[2] = { nodeID1, nodeID2 };  //array of endpoints
			int errorCode = NewRNet.insertResistor(name, resistance, nodes);


			if (errorCode == 1) {
				cout << "Error: node is full" << endl;
				continue;
			}
			else if (errorCode == 2) {
				cout << "Error: node " << nodes[0] << " is out of permitted range 0-"
					<< (NewRNet.get_maxNodes() - 1) << endl;
				continue;
			}
			else if (errorCode == 3) {
				cout << "Error: node " << nodes[1] << " is out of permitted range 0-"
					<< (NewRNet.get_maxNodes() - 1) << endl;
				continue;
			}

			cout << "Inserted: resistor " << name << " " << resistance
				<< " Ohms " << nodeID1 << " -> " << nodeID2 << endl;

		}

		else if (command.compare("modifyR") == 0) {     //modifyR------------
			lineStream >> name;
			if (checkForName(lineStream, name)) continue;

			lineStream >> resistance;
			if (checkForResistance(lineStream, resistance)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}

			cout << "Modified: resistor " << name << " from " 
				<< NewRNet.get_resistance(name) << " Ohms" << " to " 
				<< resistance << " Ohms" << endl;

			NewRNet.change_resistance(name, resistance);
		}

		else if (command.compare("printR") == 0) {  // printR----------------
			lineStream >> name;
			if (name.compare("all") == 0) {
				cout << "Print:" << endl;
				NewRNet.printAll();
				continue;
			}
			else if (checkForName(lineStream, name)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}

			else {
				cout << "Print:" << endl;
				NewRNet.printR(name);
			}
		}

		else if (command.compare("printNode") == 0) {  // printNode------------

			lineStream >> nodeID1;
			if (checkForNodeNotPrinting(lineStream, nodeID1, nodeID1 + 1)) {
				lineStream >> All;
				if (All.compare("all") == 0) {
					cout << "Print:" << endl;
					for (int n = 0; n < NewRNet.get_maxNodes(); n++) {
						cout << "Connections at node " << n << ": "
							<< NewRNet.nodeResNum(n) << " resistor(s)" << endl;
						NewRNet.printNode(n);
					}
					continue;
				}

				else cout << "Error: invalid argument" << endl;
			}

			else if (checkForNode(lineStream, nodeID1, nodeID1 + 1)) {
				continue;
			}

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}

			else {
				cout << "Print:" << endl;

				cout << "Connections at node " << nodeID1 << ": " 
					<< NewRNet.nodeResNum(nodeID1) << " resistor(s)" << endl;

				if (NewRNet.printNode(nodeID1) == 1) {
					cout << "Error: node " << nodeID1 << " is out of permitted range 0-"
						<< (NewRNet.get_maxNodes() - 1) << endl;
					continue;
				}
			}

		}

		else if (command.compare("deleteR") == 0) { // deleteR-----------------
			lineStream >> name;
			if (name.compare("all") == 0) {
				cout << "Deleted: all resistors" << endl;
				NewRNet.reset(0, 0);
				continue;
			}
			else if (checkForName(lineStream, name)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}

			else cout << "Deleted: resistor " << name << endl;
		}

		else {
			cout << "Error: invalid command" << endl;
			continue;
		}

	}

	return;
}
