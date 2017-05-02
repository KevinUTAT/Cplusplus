#include "DBentry.h"
#include <string>
#include <iostream>

using namespace std;


DBentry::DBentry() {}


DBentry::DBentry(string name_, unsigned int IP_, bool active_)
	: name(name_), IP(IP_), active(active_) {}


void DBentry::setActive(bool active_) {
	active = active_;
}