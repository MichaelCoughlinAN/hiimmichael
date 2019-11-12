#ifndef _DISC
#define _DISC

#include "Track.h"
#include "LinkedList.h"
#include "DiscList.h"

#include <string>
#include <iostream> 
#include <limits>

using namespace std;

class Track;

class Disc {
 private:
  string title;
  string artist;
  int year;
  string genre;
  int totalPlayTime;
  bool multiArtist;
  LinkedList<Track*>* trackListPtr;

 public:
    Disc();
    ~Disc();
    string getGenre() const;
    int getYear() const;
    int getTotalTime() const;
    void setArtist(bool input);
    bool isEmpty() const;
    int getNumberOfTracks() const;
    bool insertTrack(Track* trackPtr);
    Track* retrieveTrackByNumber(int trackNumber) const;
    string getArtist() const;
    string getTitle() const;
    bool isMultiArtist() const;
    void readDisc();
    void printDisc() const;
    void addToTotalPlayTime(int time);
    bool isLessThan(Disc aDisc) const;
    bool isLessThanOrEqualTo(Disc aDisc) const;
};

#endif
