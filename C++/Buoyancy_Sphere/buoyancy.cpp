// Michael Coughlin
// hiimmichael.com
// 2016

/*
This program calculates the buoyacny of a sphere given the radius and weight,
and determines if the given sphere will sink or float in water.
*/

#include <iostream>
using namespace std;

int main()
{
//Declare variables
double y, volume, buoyancy;
int r, weight;
bool fin = true;
char input;

//Input data
//Beginning of while
while(fin){
cout << "Input weight in pounds of the sphere:"<<endl;
cin >> weight;
cout << "Input the radius of the sphere (in feet):"<<endl;
cin >> r;

//Process data
volume = (4/3) * (3.14 * (r^3));
y = 62.4;
buoyancy = volume * y;

//Display results
cout << "This is your buoyancy: " << buoyancy  << endl;
if(buoyancy < 0)
cout << "Error: Cannot have negative answer." << endl;
if(buoyancy >= weight)
cout << "It will float!" << endl;
else if (buoyancy > 0 && buoyancy < weight)
cout << "It will sink!" << endl;
cout << "Would you like to continue? (enter 'y' or 'n')\n";
cin >> input;
if(tolower(input == 'y'))
fin = true; //is this needed?
else if(tolower(input =='n'))
fin = false;
}//end of while
cout << "Thank you!\n";

return 0;
}
