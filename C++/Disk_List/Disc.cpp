#include "Disc.h"

using namespace std;

Disc::Disc() {
  trackListPtr = new LinkedList<Track*>();
}

Disc::~Disc() {
  delete trackListPtr;
  trackListPtr = NULL;
}

bool Disc::isEmpty() const {
  return trackListPtr->isEmpty();
}

int Disc::getNumberOfTracks() const {
 return trackListPtr->getLength();
}

bool Disc::insertTrack(Track* trackPtr) {
  int position = getNumberOfTracks() + 1;
  return trackListPtr->insert(position, trackPtr);
}

Track* Disc::retrieveTrackByNumber(int trackNumber) const {
  return trackListPtr->getEntry(trackNumber);
}

string Disc::getArtist() const {
  return artist;
}

string Disc::getTitle() const {
  return title;
}

bool Disc::isMultiArtist() const { 
  return multiArtist;
}

int Disc::getTotalTime() const {
  return totalPlayTime;
}

void Disc::readDisc() { 
  bool fin = false;
  string input;
  string yearStr;
  bool validYear;

  cout << endl
       << "Please enter the name of the disc:\n";
  getline(cin, title);
 
 while(!fin) {   
    cout << "Is this a multi-artist disc? (y/n):\n";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

 if (input == "y" || input == "Y") {
   fin = true;
   multiArtist = true;
 }
 else if (input == "n" || input == "N") { 
   multiArtist = false;
   fin = true;
 }
 else cout << "Incorrect Input. ";
 }

validYear = false;

 if(!multiArtist) {
   cout << "Please enter the name of the artist:\n";
   getline(cin, artist);

   while(!validYear) {
       cout << "Please enter the year this disc was recorded:\n";
       getline(cin, yearStr);
    
     if (atoi(yearStr.c_str()) > 2014 || atoi(yearStr.c_str()) < 1800) {
      cout << "Invalid year. ";
     }
     else {
       for (string::size_type i = 0; i < yearStr.length(); ++i) {
	 if (!(yearStr[i] >= '0' && yearStr[i] <= '9') || yearStr[i] == ' ') {
	     cout << "Invalid year. ";
	   }
	 else {
          year = atoi(yearStr.c_str());
          validYear= true;
	 }
       }
     }
   }	 
     cout << "Please enter the genre of this disc:\n";
     getline(cin, genre);
 }
 else {
   while(!validYear) {
       cout << "Please enter the year this disc was recorded:\n";
       getline(cin, yearStr);

     if (atoi(yearStr.c_str()) > 2014 || atoi(yearStr.c_str()) < 1800) {
       cout << "Invalid year. ";
     }
     else {
       for (string::size_type i = 0; i < yearStr.length(); ++i) {
	 if (!(yearStr[i] >= '0' && yearStr[i] <= '9') || yearStr[i] == ' ') {
	     cout << "Invalid year. ";
	   }
	 else {
           year = atoi(yearStr.c_str());
           validYear= true;
	 }
       }
     }
   }
     cout << "Please enter the genre of this disc:\n";
     getline(cin, genre);
 }

  Track* trackPtr = new Track(this);
  trackPtr->readTrack();
  insertTrack(trackPtr);

 fin = false;

 while(!fin) {
   cout << "Would you like to add another track to the current disc? (y/n):\n";
   cin >> input;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   if (input == "y" || input == "Y") {
     Track* trackPtr = new Track(this);
     trackPtr->readTrack();
     insertTrack(trackPtr);
    
   }
   else if (input == "n" || input == "N") {    
     fin = true;
   }
   else cout << "Incorrect Input. ";
}
} 
	    	   
void Disc::printDisc() const {  
  cout << "Title: " << getTitle()
       << endl;
  if(!isMultiArtist()) {
    cout << "Artist: " << getArtist()
	 << endl;
  }
  cout << "Year: " << getYear()
       << endl
       << "Genre: " << getGenre()
       << endl
       << "Number of tracks: " << getNumberOfTracks()
       << endl
       << "Total playtime: " << getTotalTime() << " seconds."
       << endl;
   
}

string Disc::getGenre() const {
  return genre;
}

int Disc::getYear() const {
  return year;
}

void Disc::addToTotalPlayTime(int time){
  totalPlayTime = time + totalPlayTime;
}

bool Disc::isLessThan(Disc aDisc) const {
  //wrote the functionality of this method in insertDisc() instead, works the same. 
 return true;
}

bool Disc::isLessThanOrEqualTo(Disc aDisc) const {
 //wrote the functionality of this method in insertDisc() instead, works the same.
 return true;
}
