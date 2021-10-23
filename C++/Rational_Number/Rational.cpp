#include <iostream>

using namespace std;

#include "Rational.h"

int gcd(const int&,
        const int&);

Rational::Rational(int num,
                   int den)
   : numerator(num),
     denominator(den) {

   lowTerms();
}

Rational::Rational(const Rational& rhs)
   : numerator(rhs.numerator),
     denominator(rhs.denominator) {
}

Rational::~Rational() {
}

Rational& Rational::operator++() {

   numerator += denominator;

   return *this;
}

Rational Rational::operator++(int) {

   Rational temp = *this;

   numerator += denominator;

   return temp;
}

Rational& Rational::operator--() {

   numerator -= denominator;

   return *this;
}

Rational Rational::operator--(int) {

   Rational temp = *this;

   numerator -= denominator;

   return temp;
}

Rational& Rational::operator=(const Rational& rhs) {

   numerator = rhs.numerator;
   denominator = rhs.denominator;

   return *this;
}

Rational& Rational::operator=(const int& rhs) {

   numerator = rhs;
   denominator = 1;

   return *this;
}

Rational::operator double() const {

   return (double)numerator / (double)denominator;
}

Rational& Rational::operator+=(const Rational& rhs) {

   numerator = numerator * rhs.denominator + denominator * rhs.numerator;
   denominator = denominator * rhs.denominator;

   lowTerms();

   return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {

   numerator = numerator * rhs.denominator - denominator * rhs.numerator;
   denominator = denominator * rhs.denominator;

   lowTerms();

   return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {

   numerator = numerator * rhs.numerator;
   denominator = denominator * rhs.denominator;

   lowTerms();

   return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {

   numerator = numerator * rhs.denominator;
   denominator = denominator * rhs.numerator;

   lowTerms();

   return *this;
}

bool operator<(const Rational& lhs,
               const Rational& rhs) {

   return ((double)lhs.numerator / (double)lhs.denominator) <
      ((double)rhs.numerator / (double)rhs.denominator);
}

bool operator>(const Rational& lhs,
               const Rational& rhs) {

   return ((double)lhs.numerator / (double)lhs.denominator) >
      ((double)rhs.numerator / (double)rhs.denominator);
}

   bool operator<=(const Rational& lhs,
                   const Rational& rhs) {

   return ((double)lhs.numerator / (double)lhs.denominator) <=
      ((double)rhs.numerator / (double)rhs.denominator);
}

bool operator>=(const Rational& lhs,
                const Rational& rhs) {

   return ((double)lhs.numerator / (double)lhs.denominator) >=
      ((double)rhs.numerator / (double)rhs.denominator);
}

bool operator==(const Rational& lhs,
                const Rational& rhs) {

   return lhs.numerator == rhs.numerator &&
      lhs.denominator == rhs.denominator;
}

bool operator!=(const Rational& lhs,
                const Rational& rhs) {

   return !(lhs == rhs);
}

const Rational operator+(const Rational& lhs,
                         const Rational& rhs) {

   Rational sum(lhs.numerator * rhs.denominator + lhs.denominator * rhs.numerator,
                lhs.denominator * rhs.denominator);

   sum.lowTerms();

   return sum;
}

const Rational operator-(const Rational& lhs,
                         const Rational& rhs) {

   Rational dif(lhs.numerator * rhs.denominator - lhs.denominator * rhs.numerator,
                lhs.denominator * rhs.denominator);

   dif.lowTerms();

   return dif;
}

const Rational operator*(const Rational& lhs,
                         const Rational& rhs) {

   Rational prod(lhs.numerator * rhs.numerator,
                lhs.denominator * rhs.denominator);

   prod.lowTerms();

   return prod;
}

const Rational operator/(const Rational& lhs,
                         const Rational& rhs) {

   Rational quo(lhs.numerator * rhs.denominator,
                lhs.denominator * rhs.numerator);

   quo.lowTerms();

   if (quo.denominator == 0) {
      cerr << "WARNING: Infinite Rational object created."
           << endl;
   }

   return quo;
}

istream& operator>>(istream& s,
                    Rational& rhs) {

   char dummy;

   s >> rhs.numerator
     >> dummy
     >> rhs.denominator;

   rhs.lowTerms();

   return s;
}

ostream& operator<<(ostream& s, const Rational& rhs) {

  s << rhs.numerator << '/' << rhs.denominator;

  return s;
}

void Rational::lowTerms() {

   normalize();

   int num = numerator;
   int den = denominator;

   // Get the absolute value of num for calculating greatest common divisor.
   int absNum = num;
   if (absNum < 0) absNum = -absNum;

   // Get the gcd of abs(num) and den.
   int greatestCommonDivisor = gcd(absNum, den);

   // Set the data members so this Rational number is in lowest terms.
   numerator = num / greatestCommonDivisor;
   denominator = den / greatestCommonDivisor;
}

void Rational::normalize() {

   if (denominator < 0) {
      numerator = -numerator;
      denominator = -denominator;
   }

   if (numerator == 0) {
      denominator = 1;
   }
}

int gcd(const int& a,
        const int& b) {

   int returnVal = b;

   if (a % b != 0) {
      returnVal = gcd(b, a % b);
   }

   return returnVal;
}
