#ifndef _DISC_LIST
#define _DISC_LIST

#include "LinkedList.h"
#include "Disc.h"
#include <string>
#include <cctype>

class Disc;

using namespace std;

class DiscList {
 private:
  int findDiscPosition(Disc* discPtr) const;
  LinkedList<Disc*>* discListPtr;
 
 public:
  DiscList();
  ~DiscList();
  bool isEmpty() const;
  int getNumberOfDiscs() const;
  bool insertDisc(Disc* aDiscPtr);
  bool removeDisc(Disc* aDiscPtr);
  Disc* retrieveDisc(int number) const;

};

#endif
