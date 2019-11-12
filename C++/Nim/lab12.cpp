/*
 * File:   lab12.cpp
 * Author: Michael Coughlin
 * Course: CS 1581 Honors Computer Science 1
 */

#include <math.h>
#include <iostream>
#include <assert.h>
using namespace std;

/*
 * Exercise 12.1
 */
int numSixes(int n) {
    if (n < 0) return numSixes(-n);
    if (n == 0) return 0;
    if ((n % 10) == 6)
        return 1 + numSixes(n / 10);
    else 
        return numSixes(n / 10);
}

/*
 * Exercise 12.2
 */
int square(int x) {
  return x * x;
}

int cube(int x) {
    return x * square(x);
}

int raiseToSelf(int x) {
    return pow(x, x);
}

int sumFunc(int low, int high, int f(int)) {
    if (low < high)
        return f(low) + sumFunc(low+1, high, f);
    if (high < low)
        return f(high) + sumFunc(high+1, low, f);
    return f(low);
}


/*
 * The main function tests the exercises.  Testing succeeds if
 * no assertion errors occur.
 */
int main(int argc, char** argv) {

    // Testing Exercise 12.1
    assert( numSixes(0) == 0);
    assert( numSixes(606060606) == 5 );
    assert( numSixes(123457890) == 0 );
    assert( numSixes(6666) == 4 );
    assert( numSixes(-6666) == 4 );

    cout << "Exercise 12.1 Passed" << endl;

    // Testing Exercise 12.2
    assert( square(5) == 25 );
    assert( cube(5) == 125 );
    assert( raiseToSelf(5) == 3125 );

    assert( sumFunc(1, 9, square) == 285 );
    assert( sumFunc(1, 9, cube) == 2025 );
    assert( sumFunc(1, 9, raiseToSelf) == 405071317 );

    cout << "Exercise 12.2 Passed" << endl;

}
