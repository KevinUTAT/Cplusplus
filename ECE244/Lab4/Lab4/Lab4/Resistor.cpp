//Resistor.cpp
//Kevin Xu
//this file is for function definition for class Resistor

#include "Resistor.h"
#include "Rparser.h" 
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


Resistor::Resistor() {
	next = NULL;
}


Resistor::Resistor(string name_, double resistance_, int endNode0_, int endNode1_)
	: name(name_), resistance(resistance_), endNode0(endNode0_), endNode1(endNode1_) {
	next = NULL;
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
	return endNode0;
}


int Resistor::getNode1() {
	return endNode1;
}


Resistor* Resistor::getNext() {
	return next;
}


void Resistor::setNext(Resistor* next_) {
	next = next_;
}


void Resistor::print() {
	cout << left << setw(20) << name << " " << right << setw(8)
		<< resistance << " Ohms " << endNode0 << " -> "
		<< endNode1 << endl;
}

