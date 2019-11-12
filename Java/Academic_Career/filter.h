#ifndef DATA_H
#define	DATA_H

#include <string>

using namespace std;

class Filter  {
 private:
     string badWords[10];
 public:
     Filter();
     string* getFilter();
  
         
};

#endif



