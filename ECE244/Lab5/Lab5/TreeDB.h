#ifndef TREEDB_H
#define TREEDB_H

#include <string>
#include <iostream>
#include "TreeNode.h"
#include "DBentry.h"

using namespace std;


class TreeDB
{
private:
	TreeNode* root;
public:
	TreeDB();
	TreeDB(TreeNode* root_);
	~TreeDB();

	//insert a node with name_ IP_ and active IN ORDER
	//return false if the name already exsit 
	bool insert(string name_, unsigned int IP_, bool active_);

	//search node by name
	//return a pointer to the data object
	//return NULL if name DNE
	DBentry* find(string name_);

	//return number of active node
	int countActive();

	bool remove(string name_);

	void removeAll();

	void printAll();

	int probeCount(string name_);

	void updateStatus(string name_, bool active_);
};






#endif
