//Resistor.cpp
//Kevin Xu
//this file is for function definition for class Resistor

#include "Resistor.h"
#include "Rparser.h" 
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


Resistor::Resistor(int rIndex_, string name_, double resistance_, int endpoints_[2])
	: name(name_), resistance(resistance_), rIndex(rIndex_) {
	for (int n = 0; n < 2; n++) {  //set endpointNodeIDs to endpoints_
		endpointNodeIDs[n] = endpoints_[n];
	}
}


Resistor::~Resistor() {

}


string Resistor::getName() const {
	return name;
}


double Resistor::getResistance() const {
	return resistance;
}


void Resistor::setResistance(double resistance_) {
	resistance = resistance_;
}


int Resistor::getNode0() {
	return endpointNodeIDs[0];
}


int Resistor::getNode1() {
	return endpointNodeIDs[1];
}


void Resistor::print() {
	cout << left << setw(20) << name << " " << right << setw(8) 
		<< resistance << " Ohms " << endpointNodeIDs[0] << " -> " 
		<< endpointNodeIDs[1] << endl;
} 