#ifndef RPARCER_H
#define RPARCER_H

#include <string>
#include "Node.h"
#include "Resistor.h"

using namespace std;


int checkForName(stringstream& lineStream, string name);

int checkForResistance(stringstream& lineStream, double resistance);

int checkForNode(stringstream& lineStream, int nodeID1, int nodeID2);

int checkForNodeNotPrinting(stringstream& lineStream, int nodeID1, int nodeID2);

void parser();


#endif
