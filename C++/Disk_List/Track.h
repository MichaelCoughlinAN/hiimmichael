#ifndef _TRACK
#define _TRACK

#include "Disc.h"
#include <string>
#include <iostream>
#include <limits>

using namespace std;

class Disc;

class Track {
 private:
  string name;
  string location;
  string artist;
  int number;
  string play;
  Disc* discPtr;
  Track();

 public:
  Track(Disc* discPtr);
  void readTrack();
  void setNumber();
  void printTrack() const;
  int getNumber() const;
  string getPlayTime() const;
  string getArtist() const;
  string getName() const;
  string getPath() const;
};

#endif
