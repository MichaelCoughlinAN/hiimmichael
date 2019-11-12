/*
Outputs day of the week from any given day, month, and year
*/

#include <iostream>
#include <string>

using namespace std;

//This class creates objects that hold data members of day, month, and year
//and finds the corresponding day of the week associated with those values.
class Date {
private:
    int day;//Day of the month
    int month;//Month of the year
    int year;//Year
int leapYear;//Leap year value
    int dayOfWeek(int theMonth, int theDay, int theYear) ;

    int getMonthlyValue(int theMonth, int theYear);

    int getYearValue(int theYear);

    int getCenturyValue(int theYear);

    bool isLeapYear(int theYear);

public:
Date();
    int getDay();

    void setMonth(int theMonth);

    void setDay(int theDay);

    void setYear(int theYear);

    void getInput();
};
Date::Date(){
leapYear = 1752;
year = 0;
month = 0;
day = 0;
}

//Pre:Takes in day,month,and year
int Date::dayOfWeek(int theMonth, int theDay, int theYear) {
        int aDay = day + getMonthlyValue(theMonth, theYear) + getYearValue(theYear) + getCenturyValue(theYear);
        aDay = aDay % 7;
        if (aDay < 0 || aDay > 6)
            return -1;
        else return aDay;
    }
//Post:Makes sure day value is a day of the week
//Pre:Takes in month and year
    int Date::getMonthlyValue(int theMonth, int theYear) {
        bool league = isLeapYear(theYear);//Checks for leap year
        if (theMonth == 1 && league)
            return 6;
        else if (theMonth == 2 && league)
            return 2;
        switch(theMonth){
            case 1: return 0;
            case 2: return 3;
            case 3: return 3;
            case 4: return 6;
            case 5: return 1;
            case 6: return 4;
            case 7: return 6;
            case 8: return 2;
            case 9: return 5;
            case 10: return 0;
            case 11: return 3;
            case 12: return 5;
        }
//Post:Makes sure of a valid month value
        }
//Pre:Takes in year
    int Date::getYearValue(int theYear) {
        int last2, result;//Last 2 digits of year and result
        last2 = theYear % 100;
        result = last2 /4;
        return last2 + result;
    }
//Post:Gets year value
//Pre:Requires first 2 digits of year and remainder
int Date::getCenturyValue(int theYear) {
        int first2, rem;//First 2 digits of year and remainder
        first2 = year /100;
        rem = first2 % 4;
        return ((3-rem)*2);
    }
//Post:Outputs the century value
//Pre:Takes in year
bool Date::isLeapYear(int theYear) {
    if (theYear / 400 == 0 || (theYear / 4 == 0 && theYear / 100 != 0))
        return true;
        else return false;
    }
//Post:Tells if given year is a leap year
//Pre:Gets the day
int Date::getDay() {
        return day;
    }
//Post:Returns the day
//Pre:Takes in the month
void Date::setMonth(int theMonth) {
	while (theMonth < 1 || theMonth > 12) {
	cout << "Invalid input, please enter again.\n";
	cin >> theMonth;
}

 month = theMonth;
    }
//Post:Sets the month, checks for errors
//Pre:Takes in the day and month
void Date::setDay(int theDay) {
	while (isLeapYear(year) && month == 2 &&(theDay < 1 || theDay > 29)){
	cout << "Invalid input, please enter again.\n";
	cin >> theDay;
}
while((month == 2) && (theDay < 1 || theDay > 28)){
cout << "Invalid input, please enter again.\n";
cin >> theDay;
}
while((month == 4 || month == 6 || month == 9 || month == 11) && (theDay < 1 || theDay > 30)){
cout << "invalid input, please enter again.\n";
cin >> theDay;

}
while((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (theDay <1 || theDay >31)){
cout << "Invalid input, please enter again. \n";
cin >> theDay;

}//while
	 day = theDay;
    }
//Post:Returns the day, checks for errors
//Pre:Takes in the year
void Date::setYear(int theYear) {
while(theYear < leapYear){
cout << "Invalid year, please enter again. \n";
cin >> theYear;
}
 year = theYear;
    }
//Post:Outputs the year, checks year value for errors
//Pre:Takes in day of the week
void Date::getInput() {
        int aDay = dayOfWeek(month, day, year);
        switch(aDay){
            case -1: day = -1; break;
            case 0: day = 0; break;
            case 1: day = 1; break;
            case 2: day = 2; break;
            case 3: day = 3; break;
            case 4: day = 4; break;
            case 5: day = 5; break;
            case 6: day = 6; break;
        }
}//Post:Makes sure day value is a day of the week
//Main
int main() {
    Date date;
    string dayString;
    int day, month, year;

    cout << "Enter Month \n";
    cin >> month;
    date.setMonth(month);

    cout << "Enter year \n";
    cin >> year;
    date.setYear(year);

    cout << "Enter Day \n";
    cin >> day;
    date.setDay(day);
//Calls month, year, and day

    date.getInput();

    switch(date.getDay() ) {
        case -1: dayString = "does not exist!"; break;
        case 0: dayString = "Sunday!"; break;
        case 1: dayString = "Monday!"; break;
        case 2: dayString = "Tuesday!"; break;
        case 3: dayString = "Wednesday!"; break;
        case 4: dayString = "Thursday!"; break;
        case 5: dayString = "Friday!"; break;
        case 6: dayString = "Saturday!"; break;
    }//Finds day of the week
    cout << "The day is: " << dayString << endl;

    return 0;
}
//End of program
