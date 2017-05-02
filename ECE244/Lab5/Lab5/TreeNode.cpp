#include <string>
#include <iostream>
#include "TreeNode.h"
#include "DBentry.h"

using namespace std;


TreeNode::TreeNode()
	: entry(NULL), left(NULL), right(NULL) {}


TreeNode::TreeNode(DBentry* entry_, TreeNode* left_, TreeNode* right_)
	: entry(entry_), left(left_), right(right_) {}


TreeNode::TreeNode(string name_, unsigned int IP_, bool active_) 
	: left(NULL), right(NULL) {
	entry = new DBentry(name_, IP_, active_);
}


TreeNode::~TreeNode() {
	delete entry;

}


string TreeNode::getName() {
	return entry->name;
}


unsigned int TreeNode::getIP() {
	return entry->IP;
}

bool TreeNode::getActive() {
	return entry->active;
}


bool TreeNode::insert(string name_, unsigned int IP_, bool active_) {
	if (entry->name.compare(name_) == 0) return false;
	//insert to left
	if (entry->name.compare(name_) > 0) { //name_ is lower
		if (left == NULL)
			left = new TreeNode(name_, IP_, active_);
		else return left->insert(name_, IP_, active_);
	}
	//insert to right
	else
		if (entry->name.compare(name_) < 0) { //name_ is greater
			if (right == NULL)
				right = new TreeNode(name_, IP_, active_);
			else return right->insert(name_, IP_, active_);
		}
	return true;
}


DBentry* TreeNode::find(string name_) {

	if (entry->name.compare(name_) == 0) return entry; //base case

	if (entry->name.compare(name_) > 0) {
		if (left == NULL) return NULL;
		else return left->find(name_);
	}
	else {
		if (right == NULL) return NULL;
		else return right->find(name_);
	}
}


int TreeNode::countActive() {
	int count = 0;

	if (left != NULL) count += left->countActive();
	if (entry->active) count++;
	if (right != NULL) count += right->countActive();

	return count;

}


void TreeNode::printAll() {
	if (left != NULL) left->printAll();
	cout << *entry << endl;
	if (right != NULL) right->printAll();
}


bool TreeNode::print(string name_) {
	if (find(name_) != NULL) {
		cout << *find(name_) << endl;
		return true;
	}
	return false;
}


TreeNode* TreeNode::max() {

	if (right == NULL) return this;

	return right->max();
}


bool TreeNode::remove(string name_, TreeNode*& pp) {
	if (entry->name.compare(name_) > 0) {
		if (left != NULL)
			return left->remove(name_, left);
		else return false;
	}
	if (entry->name.compare(name_) < 0) {
		if (right != NULL)
			return right->remove(name_, right);
 		else return false;
	}
	if ((left == NULL) && (right == NULL)) { //this is a leaf
		pp = NULL;
		delete this;
	}
	else if ((left == NULL) && (right != NULL)) { //only have right child
		pp = right;                          //replaced by right child
		right = NULL;
		delete this;
	}
	else if ((left != NULL) && (right == NULL)) { //only have left child
		pp = left;                          //replaced by left child
		left = NULL;
		delete this;
	}
	else { //have two branch
		DBentry copymax;
		TreeNode* max;
		max = left->max();
		copymax = *(max->entry);
		*entry = copymax;//replaced by max from left branch
		left->remove(max->getName(), left); //delete the left max node
	}
	return true;
}


void TreeNode::removeAll() {
	if (left != NULL) left->removeAll();
	if (right != NULL) right->removeAll();
	delete this;
}


int TreeNode::probeCount(string name_, int probes) {
	int count = 0;

	if (entry->name.compare(name_) == 0) {//base case
		return probes + 1;
	}
	if (entry->name.compare(name_) > 0) {
		count = left->probeCount(name_, probes + 1);
	}
	else {
		count = right->probeCount(name_, probes + 1);
	}
	return count;
}