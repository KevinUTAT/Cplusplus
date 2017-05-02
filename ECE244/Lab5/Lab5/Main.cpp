#include <iostream>
#include <string>
#include <sstream>
#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"

using namespace std;


ostream& operator<<(ostream& out, const DBentry& rhs) {

	out << rhs.name << " : " << rhs.IP << " : ";

	if (rhs.active) out << "active";
	else out << "inactive";

	return out;
}


ostream& operator<<(ostream& out, TreeNode const & node) {
	
	out << *node.entry;

	return out;
}


void parser() {

	TreeDB MasterTree;

	while (true) { //infiniate loop until break is hitted
		string command, name, status, line;
		int IP;

		cout << "> ";
		getline(cin, line);
		stringstream lineStream(line);
		lineStream >> command;                   //--------------command list

		if (command.compare("insert") == 0) {  //----------------------insert
			bool active = false;

			lineStream >> name >> IP >> status;

			if (status.compare("active") == 0) active = true;

			if (MasterTree.insert(name, IP, active)) {
				cout << "Success" << endl;
			}
			else
				cout << "Error: entry already exists" << endl;
		}

		else if (command.compare("find") == 0) {//-----------------------find
			lineStream >> name;

			if (MasterTree.find(name) == NULL)
				cout << "Error: entry does not exist" << endl;
			else cout << *MasterTree.find(name) << endl;

		}

		else if (command.compare("remove") == 0) { //------------------remove
			lineStream >> name;

			if (MasterTree.remove(name))
				cout << "Success" << endl;
			else
				cout << "Error: entry dose not exist" << endl;
		}

		else if (command.compare("printall") == 0) { //--------------printall
			MasterTree.printAll();
		}

		else if (command.compare("printprobes") == 0) { //--------printprobes
			lineStream >> name;

			if (MasterTree.probeCount(name) == 0)
				cout << "Error: entry dose not exist" << endl;
			else 
				cout << MasterTree.probeCount(name) << endl;
		}

		else if (command.compare("removeall") == 0) { //------------removeall

			MasterTree.removeAll();
			cout << "Success" << endl;
		}

		else if (command.compare("countactive") == 0) { //--------countactive
			cout << MasterTree.countActive() << endl;
		}

		else if (command.compare("updatestatus") == 0) { //-----updtatestatus
			bool active = false;
			lineStream >> name >> status;

			if (status.compare("active") == 0) active = true;

			if (MasterTree.find(name) == NULL)
				cout << "Error: entry dose not exist" << endl;
			else {
				MasterTree.updateStatus(name, active);
				cout << "Success" << endl;
			}
		}

		else {
			if (lineStream.eof()) break;
			cout << "Error: invalid command" << endl;
		}

		
	}

}


int main() {
	parser();

	//the following code is for debuging
	cout << "Program terminatend, ENTER to exit";
	cin.get();
	//dubuging code end
}