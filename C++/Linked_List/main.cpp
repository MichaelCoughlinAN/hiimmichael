#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#include "LinkedList.h"

int getPosition(ListInterface<string>* aList, string entry){
  int position = 1;
 
 for (int i = 1; i < 7; ++i) {
  if (aList->getEntry(i) == entry){
    return position;
    } 
    else position++;
  }
 if (position == 7)
   return -1;
 else  return position;
}

int main() {
  ListInterface<string>* listPtr = new LinkedList<string>();
  int size = 6;
 
  string input;
  bool fin;
  bool done = false; 
  string response;
  string data[size];

 cout << "Please enter " << size << " list entries (do not use spaces)." << endl;

  for (int i = 0; i < 6; i++) {     
      cin >> data[i];
    }

  cout << endl
       << endl
       << "\tNow running the getPosition function.\n"
       << endl
       << "The current list holds the following values:\n"
       << endl;

  for (int i = 0; i < 6; ++i) {
    if (listPtr->insert(i + 1, data[i]) ) {
      cout << listPtr->getEntry(i + 1)
	   << endl
	   << endl;
     }
  }
  
  do {
    fin = false;

  cout << "Please enter one of the above entries to reveal its given position in the list.\n"
       << "Entry name: ";
  cin >> input;
 
  if (getPosition(listPtr, input) != -1){
  cout << "The current position of " << input << " is " << getPosition(listPtr, input) << ".\n";
  }
  else {
    cout << "Entry " << input << " does not exist within the given list.\n";
  }
 while (!fin){
  cout << "Would you like to continue? (y/n): ";
  cin >> response;
 
 if (response == "y" || response == "Y"){
    fin = true;
  }
  else if (response == "n" || response == "N"){
    fin = true;
    done = true;
    cout << endl
	 << "Have a nice day!\n"
	 << endl;
  }
  else cout << "Incorrect input. ";
 }
  } 
 while (!done);
  
  return EXIT_SUCCESS;
}
