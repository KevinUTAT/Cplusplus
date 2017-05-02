//this is the class declearation for resistor linked list
#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include <string>
#include <iostream>
#include "Resistor.h"

using namespace std;


class ResistorList
{
private:
	Resistor* head;
public:
	ResistorList();

	~ResistorList();

	//ResistorList(const ResistorList& orignial);  //copy constructor, not needed yet

	void resetList();

	//set pointer next 
	void setHead(Resistor* head_);

	Resistor* getHead();

	//insert a new resistor into the list
	//new Resisitor will always been added to the last of the linked list
	void insertResistor(string name_, double resisitence, int endNode0, int endNode1);

	//search for risisitor by name, return true for exsit
	Resistor* searchResistor(string name_);

	//delet a resistor by name, return false for 
	//resistor DNE
	bool deletResistor(string name_);

	void printAll();

	double sumRpar();
};


#endif
