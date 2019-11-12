#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

#include "isPalindrome.h"

int main() {
  cout << "\nRunning Palindrome Tests\n" 
       << endl;

   vector<string> strVec = { "",
                             "a",
                             "aba",
                             "abba",
                             "deleveled",
                             "a man a plan a canal panama",
                             "ab",
                             "abbc" };

   for (vector<string>::iterator vIter = strVec.begin();
        vIter != strVec.end();
        ++vIter) {

      // Get the current string from the vector:
      string currStr = *vIter;

      // Initialize a clean string to empty:
      string clean = "";

      // Iterate over the string currStr and remove all space characters:
      for (string::iterator sIter = currStr.begin();
           sIter != currStr.end();
           ++sIter) {

         if (*sIter != ' ') {
            clean += *sIter;
         }
      }

      // Test and report whether the string in clean is a palindrome:

      if (isPalindrome(clean) ) {
         cout << "YES "
              << clean
              << " is a palindrome."
              << endl;
      }
      else {
         cout << "NO "
              << clean
              << " is not a palindrome."
              << endl;
      }
   }
   cout << endl;

   bool done = false;
   while(!done) {
     string clean = "";
     cout << "Please enter your own word:\n";
     cin >> clean;
  if (isPalindrome(clean) ) {
         cout << "YES "
              << clean
              << " is a palindrome."
              << endl;
      }
      else {
         cout << "NO "
              << clean
              << " is not a palindrome."
              << endl;
      }
  bool fin = false;
  while(!fin) {
    cout << "Would you like to enter another word? (y/n):\n";
    cin >> clean;
  if(clean == "n" || clean == "N") {
    cout << "Have a great day!\n";
    done = true;
    fin = true;
  }
  else  if(clean == "y" || clean == "Y") {
    fin = true;
  }
  else cout << "Incorrect Input. ";
  }
   }
   return EXIT_SUCCESS;
}
