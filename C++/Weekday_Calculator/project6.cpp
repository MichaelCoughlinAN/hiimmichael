/*
This program calculates the day of the week based on given date,
month, and year.
*/

#include <iostream>
using namespace std;

bool isLeapYear(int year){
if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
return true;
else return false;
}//Precondition: Leap year is calculated using the year entered.
//Postcondition: Determines if the given year is a leap year.

int getCenturyValue(int year){
int first2, rem;
first2 = year / 100;
rem = first2 % 4;
return (3 - rem) * 2;
}//Precondition:Century value calculated by using first 2 digits of year.
//Postcondition:Input required to determine the century of given year.

int getYearValue(int year){
int last2, result;
last2 = year % 100;
result = last2 / 4;
return (last2 + result);
}//Precondition:Year value calculated by using last 2 digits of year.
//Postcondition:Stores the last two digits to help calculate result.

int getMonthValue(int month, int year){
bool leapYear = isLeapYear(year);
if(year == 1 && leapYear)
return 6;
else if(year == 2 && leapYear)
return 2;
switch(month){
case 1:
return 0;
case 2:
return 3;
case 3:
return 3;
case 4:
return 6;
case 5:
return 1;
case 6:
return 4;
case 7:
return 6;
case 8:
return 2;
case 9:
return 5;
case 10:
return 0;
case 11:
return 3;
case 12:
return 5;
}//Precondition:Requires the month number (and leapYear function) as input.
//Postcondition:Returns a given value.
}

int dayOfWeek(int month, int day, int year){
int theDay;
theDay = day + getMonthValue(month, year) + getYearValue(year) +
getCenturyValue(year);
theDay = theDay % 7;
if(theDay < 0 || theDay > 6)
return -1;
return theDay;
}//Precondition:Requires input from 3 different functions to calculate the day
//of the week.
//Postcondition:calculates which day of the week the date entered was.

void getInput(int& month, int& day, int& year){
int theDay = dayOfWeek(month, day, year);
switch(theDay){
case -1:
cout << "Invalid input \n";
break;
case 0:
cout << "Sunday \n";
break;
case 1:
cout << "Monday \n";
break;
case 2:
cout << "Tuesday \n";
break;
case 3:
cout << "Wednesday \n";
break;
case 4:
cout << "Thursday \n";
break;
case 5:
cout << "Friday \n";
break;
case 6:
cout << "Saturday \n";
break;
}//Precondition:Reads in number given by getMonthValue function.
//Postcondition:Matches numerical values to the corresponding day of the week.

}//Start of program
int main(){
char input;
bool end = true;
while(end){
int month, day, year;
cout << "Please enter the month: \n";
cin >> month;
cout << "Now enter the day: \n";
cin >> day;
cout << "Finally, enter the year: \n";
cin >> year;
getInput(month, day, year);
cout << "Would you like to enter another date?(Please enter 'y' or 'n')\n";
cin >> input;
if(input == 'y' || input == 'Y')
end = true;
else if(input == 'n' || input == 'N'){
cout << "Goodbye!\n";
end = false;}
}
return 0;
}
