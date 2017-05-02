#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
using namespace std;

class Resistor
{
private:
	double resistance; // resistance (in Ohms)
	string name; // C++ string holding the label
	int endNode0;
	int endNode1;
	Resistor* next;  // pointer to the next Resistor

public:
	Resistor();

	Resistor(string name_, double resistance_, int endNode0, int endNode1);

	string getName() const; // returns the name
	double getResistance() const; // returns the resistance

	void setResistance(double resistance_);

	int getNode0();

	int getNode1();

	//this return a point same as next
	Resistor* getNext();

	void setNext(Resistor* next_);

	// you *may* create either of the below to print your resistor
	void print();

};



#endif


