// Michael Coughlin
// hiimmichael.com
// 2016

/*
This program calculates the approximate value of pi given the number
of terms in the approximation.
*/

#include <iostream>

using namespace std;

int main()
{
	// Declare Variables
	double pi = 0;
	bool end = true;
	char input;
	int n;
	double num = -1;
	bool fin = true;

	//Input data
	cout << "\tFind the approximate value of Pi!\n";

	while (end) {
		fin = true;

		while (fin) {
			cout << "How many terms would you like to approximate pi to?\n";
			cin >> n;

			if (n <= 0)
				cout << "Invalid input, cannot be negative or zero.\n";
			else 
				fin = false;
		}

		num = -1;
		pi = 0;

		//Processing
		for (int i = 0; i < n; i++) {
			num *= -1; // same as (-1)^n
			pi = pi + num / (2 * i + 1);
		} // End of for loop

		pi = pi * 4; //mult quantity by 4

		//Output data
		cout << "The approximate value of Pi with "
			<< n
			<< " term(s) is equal to: "
			<< pi
			<< endl;

		cout << "Do you wish to continue? (please enter 'y' or 'n')\n";
		cin >> input;

		if (input == 'y' || input == 'Y')
			end = true;
		else if (input == 'n' || input == 'N')
			end = false;
		else {
			cout << "Invalid input.\n";
			break;
		}

	} 

	cout << "Goodbye!\n";

	return 0;
}
