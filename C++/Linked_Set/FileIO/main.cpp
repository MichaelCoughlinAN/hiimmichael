#include <iostream>
#include <string>

#include <fstream>

using namespace std;

int main() {

   ofstream outFile;
   ifstream inFile;

   string filename = "";

   cout << "Enter a filename: ";
   cin >> filename;

   // Open a stream on file named in 'filename' using default openmode

   outFile.open(filename.c_str() );

   // After opening an external file stream, you should test it for
   // successful opening:

   if (!outFile) {
      cerr << "File "
           << filename
           << " failed to open for output."
           << endl;
   }

   // Write things to output stream:

   outFile << "Hello world!"
           << endl
           << 12
           << 3.14159
           << 100
           << endl
           << "This file is: "
           << filename
           << endl;

   // Close the output stream as we're done writing to it.
   // This will flush the hard disk buffer and properly terminate the
   // file on disk.

   outFile.close();

   // Now that the file has content (it exists), open it (the same file
   // we just wrote to) for reading

   inFile.open(filename.c_str() );

   // Test that it opened successfully.  If it didn't prompt for a
   // new filename and try again

   while (!inFile) {
      cerr << "File "
           << filename
           << " failed to open for input."
           << endl;
      cout << "Enter a filename: ";
      cin >> filename;
      inFile.open(filename.c_str() );
   }

   string input = "";

   inFile >> input;

   cout << input
        << endl;

   inFile >> input;

   cout << input
        << endl;

   double value = 0.0;

   inFile >> value;

   cout << value
        << endl;

   // Read and ignore (throw out) up to 1000 characters and/or the
   // first '\n' (nwline) character, whichever is first, on this input
   // stream (note that ignore is also available for use with cin).

   inFile.ignore(1000, '\n');

   // Read an entire line (to the first newline) from the input stream
   // (first argument - cin can be used here too) into the string
   // (second argument). getline removes the newline from the input
   // stream, but it does *not* put it into the string.

   getline(inFile, input);

   cout << input
        << endl;

   // All file streams should be properly closed after using them:

   inFile.close();

   return 0;
}
