//this is the function definition for resistor linked list
#include <string>
#include <iostream>
#include "Resistor.h"
#include "ResistorList.h"

using namespace std;

ResistorList::ResistorList() {
	head = NULL;
}

ResistorList::~ResistorList() {
	Resistor* current;
	while (head != NULL) {
		current = head;
		head = head->getNext();
		delete current;
	}
}


//ResistorList::ResistorList(const ResistorList& original) {
//	Resistor* current = original.head;
//	Resistor* newCurrent = NULL;
//	head = NULL;
//	while (current != NULL) {
//		Resistor* newRes = new Resistor(current->getName, current->getResistance,
//			current->getNode0, current->getNode1);
//		if (newCurrent == NULL) head = newRes;
//		else newCurrent->setNext(newRes);
//		current = current->getNext();
//		newCurrent = newRes;
//	}
//
//}


void ResistorList::resetList() {
	Resistor* current;
	while (head != NULL) {
		current = head;
		head = head->getNext();
		delete current;
	}
}


void ResistorList::setHead(Resistor* head_) {
	head = head_;
}


Resistor* ResistorList::getHead() {
	return head;
}


void ResistorList::insertResistor(string name_, double resistence_,
	int endNode0, int endNode1) {

	Resistor* current;
	Resistor* newRes;
	current = head;
	newRes = new Resistor(name_, resistence_, endNode0, endNode1);

	if (current == NULL) {
		head = newRes;
		newRes->setNext(NULL);
		return;
	}

	while (current->getNext() != NULL) current = current->getNext();
	current->setNext(newRes);
	newRes->setNext(NULL);

}


Resistor* ResistorList::searchResistor(string name_) {
	Resistor* current;
	current = head;
	while (current != NULL) {
		if ((current->getName()).compare(name_) == 0)
			return current;
		else
			current = current->getNext();
	}
	return NULL;
}


bool ResistorList::deletResistor(string name_) {
	Resistor* current;
	Resistor* previous;
	current = head;
	previous = NULL;

	while (current != NULL && (current->getName()).compare(name_) != 0) {
		previous = current;
		current = current->getNext();
	}

	if (current == NULL) return false; //Resistor DNE
	else if (previous == NULL) head = current->getNext(); //try to delete the first item
	else
		previous->setNext(current->getNext());

	delete current;
	return true;
}


void ResistorList::printAll() {
	Resistor* current;
	current = head;

	while (current != NULL) {
		current->print();
		current = current->getNext();


	}
}


double ResistorList::sumRpar() {
	Resistor* current;
	double answer = 0;
	current = head;

	while (current != NULL) {
		answer = answer + (1 / current->getResistance());
		current = current->getNext();
	}
	return (1 / answer);
}