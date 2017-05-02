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


#define MAX_NODE_NUMBER 5000

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
		//        cout << "Error: invalid argument" << endl;
		lineStream.clear();
		return 1;
	}
	else return 0;
}




void parcer() {

	string line, command, name, node, All;
	int  nodeID1, nodeID2;
	double resistance;

	//____________________________set float precision
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	//_______________________________________________  


	while (true) {

		cout << '>';  // insert sign 
		getline(cin, line); // extracting the hole line of input
		stringstream lineStream(line);
		lineStream >> command;
		if (lineStream.eof()) break;



		if (command.compare("insertR") == 0) {     //insertR


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

			cout << "Inserted: resistor " << name << " " << resistance
				<< " Ohms " << nodeID1 << " -> " << nodeID2 << endl;

		}

		else if (command.compare("modifyR") == 0) {     //modifyR
			lineStream >> name;
			if (checkForName(lineStream, name)) continue;

			lineStream >> resistance;
			if (checkForResistance(lineStream, resistance)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}

			cout << "Modified: resistor " << name << " to " << resistance
				<< " Ohms" << endl;
		}

		else if (command.compare("printR") == 0) {  // printR
			lineStream >> name;
			if (name.compare("all") == 0) {
				cout << "Print: all resistors" << endl;
				continue;
			}
			else if (checkForName(lineStream, name)) continue;

			int c = lineStream.peek();
			if (!lineStream.eof()) {
				cout << "Error: too many argument" << endl;
				continue;
			}

			else cout << "Print: resistor " << name << endl;
		}

		else if (command.compare("printNode") == 0) {  // printNode

			lineStream >> nodeID1;
			if (checkForNodeNotPrinting(lineStream, nodeID1, nodeID1 + 1)) {
				lineStream >> All;
				if (All.compare("all") == 0) {
					cout << "Print: all nodes" << endl;
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

			else cout << "Print: node " << nodeID1 << endl;


		}

		else if (command.compare("deleteR") == 0) {
			lineStream >> name;
			if (name.compare("all") == 0) {
				cout << "Deleted: all resistors" << endl;
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




}



/*
*
*/
int main(void) {

	parcer();
	
	cout << "Program finished, ENTER to exit" << endl;
	cin.get();  //Pause the console for debug 
}