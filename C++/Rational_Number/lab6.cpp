#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#include "LinkedList.h"
#include "Rational.h"

int main() {

   cout << "Test Rational methods:"
        << endl;

   Rational zero;

   cout << "Default ctor = "
        << zero
        << endl;

   Rational one(1);

   cout << "One-arg ctor = "
        << one
        << endl;

   Rational oneHalf(17, 34);

   cout << "Two-arg ctor = "
        << oneHalf
        << endl;

   Rational anotherHalf(oneHalf);

   cout << "Copy ctor = "
        << anotherHalf
        << endl;

   cout << "Prefix Increment = "
        << ++oneHalf;
   cout << " 1/2 = "
        << oneHalf
        << endl;

   cout << "Postfix Increment = "
        << oneHalf++;
   cout << " 1/2 = "
        << oneHalf
        << endl;

   cout << "Prefix Decrement = "
        << --oneHalf;
   cout << " 1/2 = "
        << oneHalf
        << endl;

   cout << "Postfix Decrement = "
        << oneHalf--;
   cout << " 1/2 = "
        << oneHalf
        << endl;

   Rational twoThirds(2, 3);

   cout << "1/2 Less Than 2/3: ";

   if (oneHalf < twoThirds) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "2/3 Less Than 1/2: ";

   if (twoThirds < oneHalf) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "1/2 Less Than 1/2: ";

   if (oneHalf < anotherHalf) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "1/2 Greater Than 2/3: ";

   if (oneHalf > twoThirds) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "2/3 Greater Than 1/2: ";

   if (twoThirds > oneHalf) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "1/2 Greater Than 1/2: ";

   if (oneHalf > anotherHalf) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "1/2 Less Than Or Equal To 2/3: ";

   if (oneHalf <= twoThirds) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "2/3 Less Than Or Equal To 1/2: ";

   if (twoThirds <= oneHalf) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "1/2 Less Than Or Equal To 1/2: ";

   if (oneHalf <= anotherHalf) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "1/2 Greater Than Or Equal To 2/3: ";

   if (oneHalf >= twoThirds) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "2/3 Greater Than Or Equal To 1/2: ";

   if (twoThirds >= oneHalf) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "1/2 Greater Than Or Equal To 1/2: ";

   if (oneHalf >= anotherHalf) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "1/2 Equal To 2/3: ";

   if (oneHalf == twoThirds) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "2/3 Equal To 1/2: ";

   if (twoThirds == oneHalf) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "1/2 Equal To 1/2: ";

   if (oneHalf == anotherHalf) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "1/2 Not Equal To 2/3: ";

   if (oneHalf != twoThirds) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "2/3 Not Equal To 1/2: ";

   if (twoThirds != oneHalf) {
      cout << "OK."
           << endl;
   }
   else {
      cout << "ERROR."
           << endl;
   }

   cout << "1/2 Not Equal To 1/2: ";

   if (oneHalf != anotherHalf) {
      cout << "ERROR."
           << endl;
   }
   else {
      cout << "OK."
           << endl;
   }

   cout << "Addition:"
        << endl;

   cout << oneHalf
        << " + "
        << twoThirds
        << " = "
        << oneHalf + twoThirds
        << "; should be 7/6"
        << endl;

   cout << "Subtraction:"
        << endl;

   cout << oneHalf
        << " - "
        << twoThirds
        << " = "
        << oneHalf - twoThirds
        << "; should be -1/6"
        << endl;

   cout << "Multiplication:"
        << endl;

   cout << oneHalf
        << " * "
        << twoThirds
        << " = "
        << oneHalf * twoThirds
        << "; should be 1/3"
        << endl;

   cout << "Division:"
        << endl;

   cout << oneHalf
        << " / "
        << twoThirds
        << " = "
        << oneHalf / twoThirds
        << "; should be 3/4"
        << endl;


   cout << "Add and Assign:"
        << endl;

   Rational r(3, 4);

   cout << r
        << " += "
        << twoThirds
        << " = ";

   r += twoThirds;

   cout << r
        << "; should be 17/12"
        << endl;

   cout << "Subtract and Assign:"
        << endl;

   r = Rational(3, 4);

   cout << r
        << " -= "
        << twoThirds
        << " = ";

   r -= twoThirds;

   cout << r
        << "; should be 1/12"
        << endl;

   cout << "Multiply and Assign:"
        << endl;

   r = Rational(3, 4);

   cout << r
        << " *= "
        << twoThirds
        << " = ";

   r *= twoThirds;

   cout << r
        << "; should be 1/2"
        << endl;

   cout << "Divide and Assign:"
        << endl;

   r = Rational(3, 4);

   cout << r
        << " /= "
        << twoThirds
        << " = ";

   r /= twoThirds;

   cout << r
        << "; should be 9/8"
        << endl;

   cout << "Test of Double Conversion Operator:"
        << endl
        << twoThirds
        << " = "
        << (double)twoThirds
        << "; should be "
        << 2.0 / 3.0
        << endl;

   cout << "Test of Assign an Integer:"
        << endl;

   Rational three;

   three = 3;

   cout << "Three = "
        << three
        << "; should be 3/1"
        << endl;

   cout << "Test of Assign a Rational:"
        << endl;

   Rational anotherTwoThirds;

   anotherTwoThirds = twoThirds;

   cout << "anotherTwoThirds = "
        << anotherTwoThirds
        << "; should be 2/3"
        << endl;

   cout << "Test input streaming:"
        << endl;

   LinkedList<Rational> lR;

   while (one != zero) {
      cout << "Enter a rational (zero quits): ";
      cin >> one;
    
      lR.insert(lR.getLength() + 1, one);
   }

   cout << "Here are the rationals you entered:"
        << endl;

   cout << lR
        << endl;

   LinkedList<int> lI;

   int in = 1;

   while (in != 0) {
      cout << "Enter an int: ";
      cin >> in;

      lI.insert(lI.getLength() + 1, in);
   }

   cout << "Here are the integers you entered:"
        << endl;

   cout << lI
        << endl;

   cout << "All done!"
        << endl;

   return EXIT_SUCCESS;
}
