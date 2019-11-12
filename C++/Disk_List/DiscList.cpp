 #include "DiscList.h"

DiscList::DiscList(){
  discListPtr = new LinkedList<Disc*>();
}
DiscList::~DiscList(){
  delete discListPtr;
  discListPtr = NULL;
}

int DiscList::findDiscPosition(Disc* discPtr) const { 
 int position = 1;
 int length = discListPtr->getLength();

 for (int i = 1; i < length; ++i) {
    if (discListPtr->getEntry(i) == discPtr) {
      return position;
    }
    else position++;
  }
  if (position == length)
    return -1;
  
return position;
}

bool DiscList::isEmpty() const {
  return discListPtr->isEmpty();
}

int DiscList::getNumberOfDiscs() const {
  return discListPtr->getLength();
}

bool DiscList::insertDisc(Disc* aDiscPtr) {
  int position = getNumberOfDiscs() + 1;

 if(position == 1) {
    return discListPtr->insert(position, aDiscPtr);
  }
 else if(position > 1) {
 
  string title1 = aDiscPtr->getTitle();
  string title2 = retrieveDisc(position-1)->getTitle();
  cout << "What you are inserting: " << title1 << " The last inserted thing:  " << title2 << endl;
  cout << title1.at(0) <<  title2.at(0);
 
  if((tolower(title1.at(0)) - '0') < (tolower(title2.at(0)) - '0')) 		        
    return discListPtr->insert(position-1, aDiscPtr);
  else if((tolower(title1.at(0)) - '0') == (tolower(title2.at(0)) - '0')) 
    for(string::size_type i = 0; i < title1.length(); ++i) {
      if((tolower(title1.at(i)) - '0') < (tolower(title2.at(i)) - '0')) {
              return discListPtr->insert(position-1, aDiscPtr); 
      }
      else if((tolower(title1.at(i)) - '0') > (tolower(title2.at(i)) - '0'))
        return discListPtr->insert(position, aDiscPtr);
    } 

  else  return discListPtr->insert(position, aDiscPtr);

 }

   return discListPtr->insert(position, aDiscPtr);

}

bool DiscList::removeDisc(Disc* aDiscPtr) {
  int position = findDiscPosition(aDiscPtr);
  return discListPtr->remove(position);
}

Disc* DiscList::retrieveDisc(int number) const {
  return discListPtr->getEntry(number);
}
