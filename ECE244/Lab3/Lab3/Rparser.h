#ifndef RPARCER_H
#define RPARCER_H

#include <string>
#include "Node.h"
#include "Resistor.h"

using namespace std;

class ResNet {
private:
	int maxResistors;
	int maxNodes;
	Node ** all_node;
	Resistor ** all_resistor;
	int nextrIndex, nextnIndex;
public:
	ResNet(int const maxResistors, int maxNodes);
	~ResNet();

	//reset the object
	void ResNet::reset(int const maxResistors, int maxNodes);

	//return 1 means insert unsuccessfull with node full
	int insertResistor(string name_, double resistance_, int endpoints_[2]);

	Resistor *get_resistor(int rIndex);

	// this will print out the risistor with name name_
	//return 1 means name not fund
	int printR(string name_);

	// this will print all risistors on the R-array
	void printAll();

	//this will print out all risistor connected to this node
	//return 1 means out of bound
	int printNode(int nodeID_);

	//cehck if the array is full, return trun if it is
	bool checkRFull();

	//check if name_ already in the R-array
	bool nameExist(string name_);

	int get_maxNodes();

	void change_resistance(string name_, double value_);

	double get_resistance(string name_);

	//this will return the number of risistors connected to this node
	int nodeResNum(int nodeID_);

};


int checkForName(stringstream& lineStream, string name);

int checkForResistance(stringstream& lineStream, double resistance);

int checkForNode(stringstream& lineStream, int nodeID1, int nodeID2);

int checkForNodeNotPrinting(stringstream& lineStream, int nodeID1, int nodeID2);

void parser();


#endif
