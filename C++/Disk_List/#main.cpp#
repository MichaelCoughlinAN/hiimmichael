#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <cctype>

using namespace std;

#include "LinkedList.h"
#include "Disc.h"
#include "Track.h"
#include "DiscList.h"

int main() {
  Disc* discClass = NULL;
  DiscList discListClass;

  string discName;
  string input;  
  bool done = false;

do {
    cout << "\n\tMusic Storage Program\n"
         << endl
	 << "(A)dd a new disc.\n"
	 << "(R)emove an disc.\n"
	 << "(P)rint an disc.\n"
	 << "(L)ist discs.\n"
	 << "(Q)uit\n"
	 << "\nPlease enter a command: ";

    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

 if (input == "q" || input == "Q"){
    cout << endl
         << "Thank you and have a nice day!\n"
	 << endl;
    done = true;
    }
 else if (input == "a" || input == "A"){
   discClass = new Disc();
   discClass->readDisc(); 
   discListClass.insertDisc(discClass);   
 }
 else if (input == "r" || input == "R") {
   cout << endl 
        << "\tThese are the current discs:\n"
	<< endl;
   
 for(int i = 1; i <= discListClass.getNumberOfDiscs(); ++i) {
   Disc* discPtr = discListClass.retrieveDisc(i);
     discPtr->printDisc();
     cout << endl;
   }
   cout << "Please enter the name of the disk you want to remove:\n";
   cin >> discName;

 Disc* discPtr = NULL;
 for(int i = 1; i <= discListClass.getNumberOfDiscs(); ++i) {
  discPtr = discListClass.retrieveDisc(i);  
 if(discName == discPtr->getTitle()) {
   discListClass.removeDisc(discPtr); 
   break;
 } 
 }
 }
 else if (input == "p" || input == "P") {
   cout << endl 
        << "\tThese are the current discs:\n"
	<< endl;
 for(int i = 1; i <= discListClass.getNumberOfDiscs(); ++i) {
     Disc* discPtr = discListClass.retrieveDisc(i);
     discPtr->printDisc();
     cout << endl;
   }
   cout << "Please enter the name of the disk you would like to print:\n";
   cin >> discName;
   cout << endl;

   Track* trackPtr = NULL;
   Disc* discPtr = NULL;

 for(int i = 1; i <= discListClass.getNumberOfDiscs(); ++i) {
   discPtr = discListClass.retrieveDisc(i);

 if(discName == discPtr->getTitle()) {
    for(int n = 1; n <= discPtr->getNumberOfTracks(); ++n) {
       cout << "Track " << n << ":";     
       trackPtr  = discPtr->retrieveTrackByNumber(n);
       trackPtr->printTrack();
       cout << endl;
   }
 }
 }   
 }
 else if (input == "l" || input == "L") {    
   cout << "\n\tThese are the current discs:\n"
	<< endl;
   for(int i = 1; i <= discListClass.getNumberOfDiscs(); ++i) {
     Disc* discPtr = discListClass.retrieveDisc(i);
     discPtr->printDisc();
     cout << endl;
   }

     


 }
 else cout << endl
	   << "Incorrect menu option, please enter one of the following commands.\n";

 } while(!done);

 return EXIT_SUCCESS;
}
