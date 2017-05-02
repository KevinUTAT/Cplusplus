#include <string>
#include <iostream>
#include "TreeDB.h"
#include "TreeNode.h"
#include "DBentry.h"

using namespace std;


TreeDB::TreeDB() 
	: root(NULL) {}


TreeDB::TreeDB(TreeNode* root_) 
	: root(root_) {}


TreeDB::~TreeDB() {
	removeAll();
}   


bool TreeDB::insert(string name_, unsigned int IP_, bool active_) {
	if (root == NULL) { //if tree is empty
		root = new TreeNode(name_, IP_, active_);
		return true;
	}
	else return root->insert(name_, IP_, active_);
}


DBentry* TreeDB::find(string name_) {
	if (root == NULL) return NULL;
	else return root->find(name_);
}


int TreeDB::countActive() {
	if (root == NULL) return 0;
	else return root->countActive();
}


bool TreeDB::remove(string name_) {
	if (root == NULL) return false;
	else return root->remove(name_, root);
}


void TreeDB::removeAll() {
	if (root == NULL) return;
	else {
		root->removeAll();
		root = NULL;
	}
}


void TreeDB::printAll() {
	if (root == NULL) return;
	else root->printAll();
}


int TreeDB::probeCount(string name_) {
	if (root == NULL) return 0;
	else if (root->find(name_) == NULL) return 0;
	else return root->probeCount(name_, 0);
}


void TreeDB::updateStatus(string name_, bool active_) {
	find(name_)->setActive(active_);
}
