#include <string>
#include <iostream>

using namespace std;

int main() {
  string str("Great dog!");
  string letter = "e";
  int pos = str.find_first_of(letter);

  cout << str.substr(pos, 3)
       << endl;



  return 0;
}
