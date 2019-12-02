// Michael Coughlin
// hiimmichael.com
// 2016

/*
This program computes the annual after-tax cost of a new house for
the first year of ownership.
*/

#include <iostream>

using namespace std;

//function 1
double annualMortgage(double balance) {
	double interest = .06*balance;

	return .03*balance + interest;
}

//function 2
double taxSavings(double balance) {
	return 0.35*0.06*balance;
}

int main() {

	// Declare Variables
	bool end = true;
	bool neg1 = true;
	bool neg2 = true;
	char input;
	double house, downPayment;

	// Ask for price of house and down payment
	// Loan balance is price of house minus down payment

	//Input
	while (end) {
		neg1 = true;

		while (neg1) {
			cout << "Please enter the price of your house:\n";
			cin >> house;

			if (house <= 0)
				cout << "Invalid input, cannot be negative or zero.\n";
			else 
				neg1 = false;
		}

		neg2 = true;

		while (neg2) {
			cout << "Please enter your down payment:\n";
			cin >> downPayment;

			if (downPayment <= 0)
				cout << "Invalid input, cannot be negative or zero.\n";
			else 
				neg2 = false;
		}

		//Processing
		double balance = house - downPayment;
		double afterTaxCost = annualMortgage(balance) - taxSavings(balance);

		//Output
		cout << "your after tax cost of your house for the first year of ownership is: $"
			 << afterTaxCost << endl;
		cout << "Do you wish to continue?(please enter 'y' or 'n')\n";
		cin >> input;

		if (input == 'y' || input == 'Y')
			end = true;
		else if (input == 'n' || input == 'N')
			end = false;
	}

	cout << "The End :)\n";

	return 0;
}
