#include <iostream>
#include <string>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

    int dayOfWeek(int theMonth, int theDay, int theYear) {
        int aDay = day + getMonthlyValue(theMonth, theYear) + getYearValue(theYear) + getCenturyValue(theYear);
        aDay = aDay % 7;
        if (aDay < 0 || aDay > 6)
            return -1;
        else return aDay;
    }

    int getMonthlyValue(int theMonth, int theYear) {
        bool league = isLeapYear(theYear);
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
    }

    int getYearValue(int theYear) {
        int last2, result;
        last2 = theYear % 100;
        result = last2 /4;
        return last2 + result;
    }

    int getCenturyValue(int theYear) {
        int first2, rem;
        first2 = year /100;
        rem = first2 % 4;
        return ((3-rem)*2);
    }

    bool isLeapYear(int theYear) {
    if (theYear / 400 == 0 || (theYear / 4 == 0 && theYear / 100 != 0))
        return true;
        else return false;
    }

public:
    int getDay() {
        return day;
    }

    void setMonth(int theMonth) {
        month = theMonth;
    }

    void setDay(int theDay) {
        day = theDay;
    }

    void setYear(int theYear) {
        year = theYear;
    }

    void getInput() {
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
    }
};

int main() {
    Date date;
    string dayString;
    int day, month, year;

    cout << "Enter Month \n";
    cin >> month;
    date.setMonth(month);
    cout << "Enter Day \n";
    cin >> day;
    date.setDay(day);
    cout << "Enter Year \n";
    cin >> year;
    date.setYear(year);
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
    }
    cout << "The day is: " << dayString << endl;

    return 0;
}
