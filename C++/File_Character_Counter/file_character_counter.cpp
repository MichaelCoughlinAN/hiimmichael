// Michael Coughlin
// hiimmichael.com
// 2016

/*
This program counts the number of characters, letters, and white spaces in a given file.
*/

#include <iostream>
#include <fstream>
using namespace std;

//Array declaration
int anArray[150];
ifstream inFile;

//Function 1 characters with spaces
int numOfChar()
{
int charCount = 0;
for(int i=0;i<150;i++){
anArray[i] = 0;
}
inFile.open("project7.dat");
while(inFile)
{
char testChar = inFile.get();
int k = (int)testChar;
anArray[k] += 1;
charCount++;
}
inFile.close();
return charCount;
}

//Function 2 characters w/o white spaces
int noWhiteSpace()
{
int charCount = 0;
inFile.open("project7.dat");
while(inFile)
{
char testChar = inFile.get();
int i = (int)testChar;
if(i!=32)
charCount++;
}
inFile.close();
return charCount;
}

//Function 3 letters
int letters()
{
int letterCount = 0;
inFile.open("text.dat");
while(inFile)
{
char testChar = inFile.get();
if(testChar >='A' && testChar <='Z')
letterCount++;
else if(testChar >='a' && testChar <='z')
letterCount++;
}
inFile.close();
return letterCount;
}

//Main
int main()
{
int charNum=numOfChar();
for(int i=32;i<127;i++){
unsigned char currentChar=(unsigned char)i;
cout << currentChar << " occurs: "<< anArray[i] << "times\n";
}
cout << "There are: "<< charNum << " characters in the file (including white spaces).\n";
cout << "There are: "<< noWhiteSpace() << " characters in the file (not including white spaces).\n";
cout << "There are: "<< letters() << " letters in the file.\n";
return 0;
}
