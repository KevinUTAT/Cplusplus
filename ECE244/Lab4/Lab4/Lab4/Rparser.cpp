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
#include "NodeList.h"
#include "ResistorList.h"



using namespace std;


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
	else if ((nodeID1 < 0)) {
		cout << "Error: node " << nodeID1 << " is negitive"<< endl;
		return 1;
	}
	else if ((nodeID2 < 0)) {
		cout << "Error: node " << nodeID2 << " is negitive" << endl;
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
	int  nodeID1, nodeID2;
	double resistance, voltage;

	//____________________________set float precision
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	//_______________________________________________  

	NodeList MasterList;

	while (true) {


		cout << "> "; //insert sign
		getline(cin, line); // extracting the hole line of input
		stringstream lineStream(line);
		lineStream >> command;
		//if (lineStream.eof()) break;   //check for eptey input and quit

		if (command.compare("solve") == 0) {  //solve---------------------------
			if (!MasterList.voltSet()) {
				cout << "no nodes have their voltage set" << endl;
				continue;
			}

			MasterList.solveAll();

		}

		else if (command.compare("setV") == 0) {         // setV-----------------
			lineStream >> nodeID1 >> voltage;

			MasterList.searchNode(nodeID1)->setVoltage(voltage);

			cout << "Set: node " << nodeID1 << " to " << voltage << "Volts" << endl;
		}

		else if (command.compare("unsetV") == 0) {
			lineStream >> nodeID1;

			MasterList.searchNode(nodeID1)->unsetVoltage();

			cout << "the solver will determine the voltage of node " 
				<< nodeID1 << endl;
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

			if (MasterList.searchRes(name) != NULL) {  //check if the name already exist
				cout << "Error: resistor " << name << " already exists"
					<< endl;
				continue;
			}
			// error checking above
			// action below

			if (MasterList.searchNode(nodeID1) != NULL) { //check if the node is aready been made
				MasterList.searchNode(nodeID1)->addResistor(name, resistance, nodeID1, nodeID2);
			}
			else {                                        //node DNE, then insert a new node and insert
				MasterList.insertNode(nodeID1);           //the new res into the new node
				MasterList.searchNode(nodeID1)->addResistor(name, resistance, nodeID1, nodeID2);
			}
			if (MasterList.searchNode(nodeID2) != NULL) {
				MasterList.searchNode(nodeID2)->addResistor(name, resistance, nodeID1, nodeID2);
			}
			else {                                        //node DNE, then insert a new node and insert
				MasterList.insertNode(nodeID2);           //the new res into the new node
				MasterList.searchNode(nodeID2)->addResistor(name, resistance, nodeID1, nodeID2);
			}
			//insert Resistor success, now say something
			cout << "Inserted: resistor " << name << " " << resistance
				<< " Ohms " << nodeID1 << " -> " << nodeID2 << endl;
		}

		else if (command.compare("modifyR") == 0) {     // modifyR------------
			lineStream >> name;
			if (checkForName(lineStream, name)) continue;

			lineStream >> resistance;
			if (checkForResistance(lineStream, resistance)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof() && c != ' ') {
				cout << "Error: too many argument" << endl;
				continue;
			}
			//error check above

			int node0, node1;
			if (MasterList.searchRes(name) != NULL) {
				cout << "Modified: resistor " << name << " from "
				<< MasterList.searchRes(name)->getResistance() << " Ohms" << " to "
				<< resistance << " Ohms" << endl;

				node0 = MasterList.searchRes(name)->getNode0(); //get the 2 list this resistor is in
				node1 = MasterList.searchRes(name)->getNode1();

				MasterList.searchNode(node0)->searchRes(name)->setResistance(resistance); //set both resistor
				MasterList.searchNode(node1)->searchRes(name)->setResistance(resistance);

			}
			else {
				cout << "Error: resistor " << name << " not found" << std::endl;
			}
		}

		else if (command.compare("printR") == 0) {  // printR----------------
			lineStream >> name;

			if (checkForName(lineStream, name)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}

			else {
				cout << "Print:" << endl;
				MasterList.searchRes(name)->print();
			}
		}

		else if (command.compare("printNode") == 0) {  // printNode------------

			lineStream >> nodeID1;
			if (checkForNodeNotPrinting(lineStream, nodeID1, nodeID1 + 1)) {
				lineStream >> All;
				if (All.compare("all") == 0) {   //printNode all
					
					MasterList.printAll();
					
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

			else {                               //printNode not all
				cout << "Print:" << endl;

				MasterList.print(nodeID1);
			}

		}

		else if (command.compare("deleteR") == 0) { // deleteR-----------------
			lineStream >> name;
			if (name.compare("all") == 0) {                     //delete all
				cout << "Deleted: all resistors" << endl;
				MasterList.resetAll();
				MasterList.update();
				continue;
			}
			else if (checkForName(lineStream, name)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}

			else if (MasterList.searchRes(name) != NULL) {                                              //delete one
				int node0, node1;
				cout << "Deleted: resistor " << name << endl;

				node0 = MasterList.searchRes(name)->getNode0(); //get the 2 list this resistor is in
				node1 = MasterList.searchRes(name)->getNode1();

				MasterList.searchNode(node0)->deleteRes(name); //delete both resistor
				MasterList.searchNode(node1)->deleteRes(name);

				MasterList.update();
				continue;
			}

			cout << "Error: resistor " << name << " not found" << endl;
		}

		else if (command.compare("exit") == 0) break;

		else {
			cout << "Error: invalid command" << endl;
			continue;
		}

	}

	return;
}
