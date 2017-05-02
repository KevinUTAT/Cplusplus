#include <iostream> 

using namespace std; 

int main() {
	char firstInitial;   
	char lastInitial;

	cout << "Enter your first name followed by your last name: ";

	cin >> firstInitial;
	cin.ignore();
	cin >> lastInitial;
	cin.ignore();

	cout << "Your initials are: " << firstInitial << lastInitial << endl;

	cin.get();

	return (0);
}
