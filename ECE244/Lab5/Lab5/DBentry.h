#ifndef DBENTRY_H
#define DBENTRY_H

#include <string>
#include <iostream>
//#include "TreeNode.h"

using namespace std;

class TreeNode; //frend to DBentry

class DBentry
{
private:
	string name;
	unsigned int IP;
	bool active;
public:
	DBentry();
	DBentry(string name_, unsigned int IP_, bool active_);

	void setActive(bool active_);

	friend ostream& operator<<(ostream& out, const DBentry& rhs);

	friend TreeNode;
	//void setName(string const name_);

	//void setIP(int IP_);

	//void setActive(bool active_);

	//
};













#endif
