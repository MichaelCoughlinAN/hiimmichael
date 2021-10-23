// Michael Coughlin
// hiimmichael.com
// 2016

/*
This program calculates the amount of candy bars
that can be eaten to maintain one's weight without any exercise.
*/

#include <iostream>
using namespace std;

int main()
{
	//Declare variables
double weight, height, age, BMR, candy;
char gender;

	//Input
	cout << "Please enter your weight in pounds\n";
	cin >> weight;
	cout << "Please enter your height in inches\n";
	cin >> height;
	cout << "Please enter your age in years\n";
	cin >> age;
	cout << "Are you male or female (enter 'M' or 'F').\n";
	cin >> gender;

//processing: first "if" statement with equations
if(gender == 'M' || gender == 'm'){
BMR = 66 + (6.3 * weight) + (12.9 * height) - (6.8 * age);
} else if(gender == 'F' || gender == 'f'){
BMR = 655 + (4.3 * weight) + (4.7 * height) - (4.7 * age);
}
candy = BMR/230;

	//output
	cout << "Your weight is: " << weight << " pounds\n"
	<< "Your height is: " << height << " inches\n"
	<< "Your age is: " << age << " years\n"
	<< "Your gender is: ";

//second "if" statement
if(gender == 'M' || gender == 'm')
cout << "Male" << endl;
else cout<< "Female\n";
cout << "You can eat " << candy << " candy bars!\n";

return 0;
}
