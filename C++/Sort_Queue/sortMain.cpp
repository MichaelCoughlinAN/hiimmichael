/*
 * File:   sortMain.cpp
 * Author: Michael Coughlin
 * Honors Computer Science I, Fall 2013
 * Created on December 3, 2010
 */

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <assert.h>
using namespace std;

const int MAX_ITEM = 999;

/*
 * Fills an array with random elements in
 * the range [0..MAX_ITEM].
 */
void fill(int a[], int n) {
  for (int i = 0; i < n; i++) {
    a[i] = rand() % (MAX_ITEM+1);
  }
}

const int ROW_SIZE = 10;

/*
 * Displays the contents of an array, adding
 * a new line break every ROW_SIZE elements.
 */
void display(int a[], int n) {
  for (int i = 0; i < n; i++) {
    if ( i % ROW_SIZE == 0 ) {
      cout << endl;
    }
    cout << setw(5) << a[i];
  }
  cout << endl;
}

/*
 * Tests if an integer array is arranged in ascending order.
 */
bool inOrder(int a[], int n) {
  for (int i = 0; i < n-1; i++) {
    if (a[i] > a[i+1]) return false;
  }
  return true;
}

/*
 *  Merges two adjacent subranges of an array.
 *  "a" is the array with entries to be merged.
 *  "from" is the index of the first element of the first range.
 *  "mid" is the index of the last element of the first range.
 *  "to" is the index of the last element of the second range.
 *  A temporary array should be created to receive the merged elements.
 *  Then the temporary array elements should be copied back to "a".
 */
void merge(int a[], int from, int mid, int to) {
    int x,y,j,m;
    int b[100];
    x = from;
    y = from;
    j = mid + 1;
    
    while((x <= mid) && (j <= to))
    {
        if(a[x] <= a[j])
        {
            b[y] = a[x];
                x++;
        }
        else
        {
            b[y] = a[j];
                 j++;
        }
                 y++; 
    }
    if(x > mid)
    {
        for(m=j; m<=to; m++)
        {
            b[y]=a[m];
            y++;
        }
    }
else
{
                 for(m=x; m<=mid; m++)
                 {
                     b[y]=a[m];
                         y++;
    }
}
    for(m=from; m<=to; m++) 
        a[m] = b[m];             

}
        
    
    
  


/*
 *  Sorts a range of an array, using the merge sort algorithm.
 *  "a" is the array to sort.
 *  "from" is the first index of the range to sort.
 *  "to" is the last index of the range to sort.
 */
void mergeSort(int a[], int from, int to) {
  if (from == to) return; // array portion is just one element
  int mid = (from + to) / 2;
  mergeSort(a, from, mid);
  mergeSort(a, mid + 1, to);
  merge(a, from, mid, to);
}

/*
 * This tests your merge sort.
 */
int main(int argc, char** argv) {

  // Testing Exercise 13.1
  const int n = 100;
  int a1[n];
  fill(a1, n);                // fill the array with random integers
  display(a1, n);             // display the unsorted array
  assert( !inOrder(a1, n) );  // array will not be in order at this point
  mergeSort(a1, 0, n-1);      // carry out the merge sort
  display(a1, n);             // display again
  assert( inOrder(a1, n) );   // array should be in order

  cout << "Exercise 13.1 Passed" << endl;
}

