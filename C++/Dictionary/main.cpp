/**
 * This Dictionary ADT is fully functional! I spent 
 * the majority of May 2nd - May 4th getting it to work.
 * I have altered A LOT of the functionality including the 
 * Dictionary Interface and its methods along with the BST 
 * ADT and its methods. Almost all of my methods meet the 
 * efficiency requirements. However, I focused on just 
 * getting a working ADT by May 6th, because of that, some 
 * methods may be slightly greated than the (O)log2 
 * efficiency. I tried my best for that not to happen.
 *
 * Thank you! 
 **/

#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <cctype>

#include "ArrayDictionary.h"

using namespace std;

void visit(const string& item) {
  cout << item << endl;
}

int main() {

  cout << "\nWelcome to the Two Layered Organization Program\n";

  ArrayDictionary<string, string> dic;
  string name, socialSecNum, ethnicity, age;
  ifstream inFile;
  string filename, input;
  bool done = false;
  bool fin;

  cout << "\nPlease enter a filename: ";
  cin >> filename;

  inFile.open(filename.c_str() );

  while (!inFile) {
    cerr << "File "
	 << filename
	 << " failed to open for input."
	 << endl;
    cout << "Please enter a filename: ";
    cin >> filename;
    inFile.open(filename.c_str() );
  }
  while (inFile >> name >> socialSecNum >> ethnicity >> age) { //if not at end of file, continue reading
    //       dic.add(name, socialSecNum);
    dic.add(name, socialSecNum, ethnicity, age);   
   
 }
  inFile.close(); // close the file

 do { 
   fin = false;
    cout << endl
	 << "\tMenu Options\n"
	 << endl
	 << "(A)dd an item.\n"
	 << "(R)emove an item.\n"
	 << "(L)ist all items.\n"
	 << "(D)isplay item information.\n"
	 << "(Q)uit\n"
	 << "\nPlease enter a command: ";

    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (input == "q" || input == "Q") {
      cout << "\nThank you and have a nice day!\n"
	   << endl;
      done = true;
    }
    else if (input == "r" || input == "R") {
       while(!fin) {
      cout << "Which search-key would you like to remove from?\n"
	   << endl
	   << "(N)ames\n"
	   << "(S)ocial-Security Numbers\n"
	   << endl
	   << "Please enter a command: ";
      cin >> input;
      if (input == "n" || input == "N") {
	fin = true;	
	cout << endl
	     << "Names List:\n"
	     << endl;
	dic.traverseKey(visit);
	cout << "\nPlease enter the name you would like to remove:\n";
             cin >> input;
	     int position = dic.getPositionKey(input);
	     if(dic.remove(position) )
	       cout << input << " and its corresponding information has been successfully removed!\n";
	     else cout << "Failed to remove " << input << " and its corresponding information.\n";
      }
      else if (input == "s" || input == "S") {
	fin = true;
	cout << endl
	     << "SSN List:\n"
	     << endl;
	dic.traverse(visit);
	cout << "\nPlease enter the SSN you would like to remove:\n";
             cin >> input;
	     int position = dic.getPosition(input);
	     if(dic.remove(position) )
	       cout << "The information corresponding with " << input << " has been successfully removed!\n";
	     else cout << "Failed to remove information corresponding with " << input << ".\n";
      }
      else cout << "Incorrect input. ";
      }
    }
    else if (input == "l" || input == "L") { //list all items
      while(!fin) {
      cout << "Which search-key would you like to display from?\n"
	   << endl
	   << "(N)ames\n"
	   << "(S)ocial-Security Numbers\n"
	   << endl
	   << "Please enter a command: ";
      cin >> input;
      if (input == "n" || input == "N") {
	fin = true;	
	cout << endl
	     << "Names List:\n"
	     << endl;
	dic.traverseKey(visit);
      }
      else if (input == "s" || input == "S") {
	fin = true;
	cout << endl
	     << "SSN List:\n"
	     << endl;
	dic.traverse(visit);
      }
      else cout << "Incorrect input. ";
      }
    }
    else if (input == "d" || input == "D") {
             while(!fin) {
      cout << "Which search-key would you like to display from?\n"
	   << endl
	   << "(N)ames\n"
	   << "(S)ocial-Security Numbers\n"
	   << endl
	   << "Please enter a command: ";
      cin >> input;
      if (input == "n" || input == "N") {
	fin = true;	
	cout << endl
	     << "Names List:\n"
	     << endl;
	dic.traverseKey(visit);
	cout << "\nPlease enter the name you would like to display:\n";
             cin >> input;
	     int position = dic.getPositionKey(input);
	     dic.displayEntry(position);

      }
      else if (input == "s" || input == "S") {
	fin = true;
	cout << endl
	     << "SSN List:\n"
	     << endl;
	dic.traverse(visit);
	cout << "\nPlease enter the SSN you would like to display:\n";
             cin >> input;
	     int position = dic.getPosition(input);
	     dic.displayEntry(position);

      }
      else cout << "Incorrect input. ";
      } 
		    
    }
    else if (input == "a" || input == "A") {
      cout << "Please enter the name of the person: ";
      cin >> name;
      cout << "Please enter " << name << "'s" << " social-security number: ";
      cin >> socialSecNum;
      cout << "Please enter " << name << "'s" << " age: ";
      cin >> age;
      cout << "Please enter " << name << "'s" << " ethnic background: ";
      cin >> ethnicity;
    
      if(dic.add(name, socialSecNum, ethnicity, age) ) {
	cout << name << "'s" << " information was successfully added!\n";
      }
      else cout << "Array is full\n";
      } 
 else cout << endl
	   << "Incorrect menu option, please enter one of the following commands.\n";
 } while(!done);
   

  return EXIT_SUCCESS;
}
