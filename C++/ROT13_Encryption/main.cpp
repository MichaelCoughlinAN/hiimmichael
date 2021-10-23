#include <algorithm> 
#include <iostream>
#include <string>
#include <cstdlib>
#include <iterator>

using namespace std;

template <typename ItemType>
void rotate5(ItemType& itemToChange) {
 switch (itemToChange) {
     case '0':
       {
	 itemToChange = '5';
	 break;
       }
     case '1':
       {
	 itemToChange = '6';
	 break;
       }
     case '2':
       {
	 itemToChange = '7';
	 break;
       }
     case '3':
       {
	 itemToChange = '8';
	 break;
       }
     case '4':
       {
	 itemToChange = '9';
	 break;
       }
     case '5':
       {
	 itemToChange = '0';
	 break;
       }
     case '6':
       {
	 itemToChange = '1';
	 break;
       }
     case '7':
       {
	 itemToChange = '2';
	 break;
       }
     case '8':
       {
	 itemToChange = '3';
	 break;
       }
     case '9':
       {
	 itemToChange = '4';
	 break;
       }
 };
 }

template <typename ItemType>
void rotate13(ItemType& itemToChange) {
   if(itemToChange == ' ')
     return; 
   if(isdigit(itemToChange))
     rotate5(itemToChange); 
 switch (itemToChange) {
     case 'A':
       {
	 itemToChange = 'N';
	 break;
       }
     case 'B':
       {
	 itemToChange = 'O';
	 break;
       }
     case 'C':
       {
	 itemToChange = 'P';
	 break;
       }
     case 'D':
       {
	 itemToChange = 'Q';
	 break;
       }
     case 'E':
       {
	 itemToChange = 'R';
	 break;
       }
     case 'F':
       {
	 itemToChange = 'S';
	 break;
       }
     case 'G':
       {
	 itemToChange = 'T';
	 break;
       }
     case 'H':
       {
	 itemToChange = 'U';
	 break;
       }
     case 'I':
       {
	 itemToChange = 'V';
	 break;
       }
     case 'J':
       {
	 itemToChange = 'W';
	 break;
       }
     case 'K':
       {
	 itemToChange = 'X';
	 break;
       }
     case 'L':
       {
	 itemToChange = 'Y';
	 break;
       }
     case 'M':
       {
	 itemToChange = 'Z';
	 break;
       }
     case 'N':
       {
	 itemToChange = 'A';
	 break;
       }
     case 'O':
       {
	 itemToChange = 'B';
	 break;
       }
     case 'P':
       {
	 itemToChange = 'C';
	 break;
       }
     case 'Q':
       {
	 itemToChange = 'D';
	 break;
       }
     case 'R':
       {
	 itemToChange = 'E';
	 break;
       }
     case 'S':
       {
	 itemToChange = 'F';
	 break;
       }
     case 'T':
       {
	 itemToChange = 'G';
	 break;
       }
     case 'U':
       {
	 itemToChange = 'H';
	 break;
       }
     case 'V':
       {
	 itemToChange = 'I';
	 break;
       }
     case 'W':
       {
	 itemToChange = 'J';
	 break;
       }
     case 'X':
       {
	 itemToChange = 'K';
	 break;
       }
     case 'Y':
       {
	 itemToChange = 'L';
	 break;
       }
     case 'Z':
       {
	 itemToChange = 'M';
	 break;
       }
     case 'a':
       {
	 itemToChange = 'n';
	 break;
       }
     case 'b':
       {
	 itemToChange = 'o';
	 break;
       }
     case 'c':
       {
	 itemToChange = 'p';
	 break;
       }
     case 'd':
       {
	 itemToChange = 'q';
	 break;
       }
     case 'e':
       {
	 itemToChange = 'r';
	 break;
       }
     case 'f':
       {
	 itemToChange = 's';
	 break;
       }
     case 'g':
       {
	 itemToChange = 't';
	 break;
       }
     case 'h':
       {
	 itemToChange = 'u';
	 break;
       }
     case 'i':
       {
	 itemToChange = 'v';
	 break;
       }
     case 'j':
       {
	 itemToChange = 'w';
	 break;
       }
     case 'k':
       {
	 itemToChange = 'x';
	 break;
       }
     case 'l':
       {
	 itemToChange = 'y';
	 break;
       }
     case 'm':
       {
	 itemToChange = 'z';
	 break;
       }
     case 'n':
       {
	 itemToChange = 'a';
	 break;
       }
     case 'o':
       {
	 itemToChange = 'b';
	 break;
       }
     case 'p':
       {
	 itemToChange = 'c';
	 break;
       }
     case 'q':
       {
	 itemToChange = 'd';
	 break;
       }
     case 'r':
       {
	 itemToChange = 'e';
	 break;
       }
     case 's':
       {
	 itemToChange = 'f';
	 break;
       }
     case 't':
       {
	 itemToChange = 'g';
	 break;
       }
     case 'u':
       {
	 itemToChange = 'h';
	 break;
       }
     case 'v':
       {
	 itemToChange = 'i';
	 break;
       }
     case 'w':
       {
	 itemToChange = 'j';
	 break;
       }
     case 'x':
       {
	 itemToChange = 'k';
	 break;
       }
     case 'y':
       {
	 itemToChange = 'l';
	 break;
       }
     case 'z':
       {
	 itemToChange = 'm';
	 break;
       }   
     };
  }


int main() {
  cout << endl
       << "Welcome to the Basic Cryptography Program\n"
       << endl;

 string str = "Jvgu 9 cnenzrgref V pna svg na ryrcunag, naq jvgu 0 V pna znxr uvz jvttyr uvf gehax. --Wbua iba Arhznaa";
  cout << "Encrypted: "
       << str
       << endl;
  for_each(str.begin(), str.end(), rotate13<char>);
  cout << "Decrypted: "
       << str 
       << endl;

  string input = "";
  string temp = "";

  do {
    cout << endl
	 << "Please enter a line to cipher, or enter '$' to exit: " 
	 << endl;
    getline(cin, input);
    if(input == "$")
      break;
    temp = input; 
    for_each(input.begin(), input.end(), rotate13<char>);
    cout << "Original input: " 
	 << temp
	 << endl
	 << "Encrypted input: "
	 << input
	 << endl
	 << "Decrypted input: ";
    for_each(input.begin(), input.end(), rotate13<char>);
    cout << input
	 << endl;
  }  while (input != "$");

  return EXIT_SUCCESS;
}
