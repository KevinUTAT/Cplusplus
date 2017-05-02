#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include "DBentry.h"
//#include "TreeDB.h"

using namespace std;

class TreeDB;

class TreeNode
{
private:
	DBentry* entry;
	TreeNode* left;
	TreeNode* right;
public:
	TreeNode();
	TreeNode(DBentry* entry_, TreeNode* left_, TreeNode* right_);
	TreeNode(string name_, unsigned int IP_, bool active_);
	~TreeNode();

	string getName();

	unsigned int getIP();

	bool getActive();

	//insert a node with name_ IP_ and active IN ORDER
	//return false if the name already exsit 
	bool insert(string name_, unsigned int IP_, bool active_);

	//search node by name
	//return a pointer to the data object
	//return NULL if name DNE
	DBentry* find(string name_);

	//return number of active node
	//as this node is the root
	int countActive();

	//print all node in ascending order
	//as if this object is the root
	void printAll();

	//search sub tree and print
	//return false if name_ DNE
	bool print(string name_);

	//return pointer pointing to the node have max key
	TreeNode* max();

	bool remove(string name_, TreeNode*& pp);

	void removeAll();

	//count number of probe wlked thourgh 
	//NOTE!!!
	//this assume name_ exist
	int probeCount(string name_, int probes);

	friend TreeDB;

	friend ostream& operator<<(ostream& out, TreeNode const & node);
};





#endif
