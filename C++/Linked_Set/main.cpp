#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

#include "LinkedSet.h"

int main(){  
  LinkedSet<string> set;
  LinkedSet<string> set1;
  ofstream outFile;
  ifstream inFile;
  string filename = "";
  string input = "";
  bool done = false;
  bool fin; 
  char response;

  cout << endl << "Welcome to the Spell Checker!\n" << endl
       << "Please enter the filename of the dictonary file containing\n" 
       << "the correctly spelled words: ";
  cin >> filename;
  inFile.open(filename.c_str());

  while (!inFile) {
    cerr << "File "
	 << filename
	 << " failed to open for input."
	 << endl;
    cout << "Enter a filename: ";
    cin >> filename;
    inFile.open(filename.c_str());
  }

 while(!inFile.eof()){
  inFile >> input;
  set.add(input);  
  }

  inFile.close();
 
  do {
    fin = false;
    cout << "Please enter the filename to spell check: ";   
    cin >> filename;
    inFile.open(filename.c_str());   

 while(!inFile) {
    cerr << "File "
	 << filename
	 << " failed to open for input."
	 << endl;
    cout << "Enter a filename: ";
    cin >> filename;
    inFile.open(filename.c_str());
 }
 while(!inFile.eof()){
  inFile >> input;
  input = set1.clean(input);
  input = set1.toLower(input);
  set1.add(input);  
  }

  inFile.close();

  cout << "Results: ";
  vector<string> dictonary = set1.difference(set);
  int displayEntries = (int)dictonary.size();
  for(int i = 0; i < displayEntries; ++i){
    cout << dictonary[i] << " ";
  }

 while(fin == false){
   cout << endl << "Do you wish to continue? (y/n): ";
  cin >> response;
  if(response == 'Y' || response == 'y'){
    fin = true;
    set1.clear();
  }
  else if(response == 'N' || response == 'n'){
    fin = true;
    done = true;
    cout <<  "Have a nice day!\n";
    } else cout << "Incorrect Input. "; 
}	   
  }while(done == false);

 return EXIT_SUCCESS;
}

