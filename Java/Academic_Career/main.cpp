/* 
 * File:   main.cpp
 * Author: Michael
 *
 * Created on May 16, 2015, 5:44 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>


#include "filter.h"


using namespace std;


int main() {
    Filter* filterPtr = new Filter();
    string temp; 
    cout << "Please enter a string: ";
    cin >> temp;
    string* temp1 = filterPtr->getFilter();
    for(int i = 0; i < 10; ++i) {
         string temp2 = temp1[1];
        if (temp2[i] == temp) {
                      
         

            cout << "invalid word!";
            return 0;
        }
    }
        cout << "word is fine";
    
    
    
    
    
    return 0;
}

