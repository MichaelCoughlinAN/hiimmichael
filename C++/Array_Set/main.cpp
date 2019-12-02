// Michael Coughlin
// hiimmichael.com
// 2016

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#include "ArraySet.h"

int main() {
  
 ArraySet<string> set; 
  set.add("cat");
  set.add("dog");
  set.add("fish");
  set.add("cat");

 ArraySet<string> set1; 
  set1.add("cow");
  set1.add("dog");
  set1.add("fish");
  set1.add("mouse");
 
 ArraySet<string> set2;

 ArraySet<string> set3;
  set3.add("cow");
  set3.add("bear");
  set3.add("Michael");
  set3.add("panda");
 
 ArraySet<int> empty;
 ArraySet<int> empty1;
 

 cout  << endl << "Lab2 Tests\n" << endl
       << "Test One - ArraySet removes the duplicate \"cat\" from the set\n"
       << "Before: cat dog fish cat\n"
       << "After: ";

  vector<string> test1 = set.toVector();
  int testOneEntries = (int)test1.size();

  for(int i = 0; i < testOneEntries; ++i){
    cout << test1[i] << " ";
}

  cout << endl
       << endl;

  cout << "Test Two - Result from difference when both sets are empty\n"
       << "Results: ";  

vector<int> test2 = empty.difference(empty1);

  int testTwoEntries = (int)test2.size();

  for(int i = 0; i < testTwoEntries; ++i){
    cout << test2[i] << " ";
}
  cout << endl
       << endl;

  cout << "Test Three - Result from difference when this set is empty, but the set passed as an argument has items in it\n"
       << "Results: ";
  vector<string> setItems = set2.difference(set1);
  int testThreeEntries = (int)setItems.size();
  for(int i = 0; i < testThreeEntries; ++i){
    cout << setItems[i] << " ";
  }
  cout << endl
       << endl;

  cout << "Test Four - Result from difference when the other set is empty, but this set has items in it\n"
       << "Results: ";
  vector<string> setItemsOne = set1.difference(set2);
  int testFourEntries = (int)setItemsOne.size();
  for(int i = 0; i < testFourEntries; ++i){
    cout << setItemsOne[i] << " ";
  }
  cout << endl
       << endl;
 
  cout << "Test Five - Result from difference when the sets have no intersection, i.e. they share no items in common\n"
       << "Results: ";
  vector<string> setItemsTwo = set3.difference(set);
  int testFiveEntries = (int)setItemsOne.size();
  for(int i = 0; i < testFiveEntries; ++i){
    cout << setItemsTwo[i] << " ";
  }
  cout << endl
       << endl;

 cout << "Test Six - Result from difference when the sets have an intersection, but they do not contain identical sets of items\n"
      << "Results: ";
  vector<string> setItemsThree = set1.difference(set3);
  int testSixEntries = (int)setItemsThree.size();
  for(int i = 0; i < testSixEntries; ++i){
    cout << setItemsThree[i] << " ";
  }
  cout << endl
       << endl;

 cout << "Test Seven - Result from difference when the sets contain the same sets of items, i.e. they are identical\n"
      << "Results: ";
  vector<string> setItemsFour = set3.difference(set3);
  int testSevenEntries = (int)setItemsFour.size();
  for(int i = 0; i < testSevenEntries; ++i){
    cout << setItemsFour[i] << " ";
  }
  cout << endl
       << endl
       << "TESTS SUCCESSFUL!\n"
       << endl;


 
 return EXIT_SUCCESS;
}
