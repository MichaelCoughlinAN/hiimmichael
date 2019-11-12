#include "Track.h"

using namespace std;


Track::Track() {
  discPtr = new Disc();
}


Track::Track(Disc* disc) { 
  discPtr = disc;  
}

void Track::readTrack() {
   string input;
   bool finished = false;
   bool validPlayTime;
   string title;

if (!discPtr->isMultiArtist()) {   

  while(!finished) {
  bool validPlayTime = false;

  cout << "Please enter the track title:\n";
   getline(cin, name);

  while (!validPlayTime) {
    cout << "Please enter the play time for the track:\n";
    cin >> play;

   bool firstCheck = true;
   bool secondCheck = false;
   bool thirdCheck = false;  
   string semiColon = ":";

   if(play.length() < 3) {
     cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
     firstCheck = false;
     validPlayTime = false;     
   }
      
   string firstHalf = play.substr(0, play.find_first_of(semiColon));
   if (firstCheck) {
     for (string::size_type i = 0; i < firstHalf.length(); ++i) {
       if (isdigit(firstHalf.at(i)) && (firstHalf.length() == 1 || firstHalf.length() == 2)) {
	 validPlayTime = true;
	 secondCheck = true;
       } else {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 secondCheck = false;
	 break;
       }
     }
   }

   string secondHalf = play.substr((play.find_first_of(semiColon) + 1));
   if (secondCheck) {
     for (string::size_type i = 0; i < secondHalf.length(); ++i) {
       if (isdigit(secondHalf.at(i)) && secondHalf.length() == 2)
	 thirdCheck = true;
       else {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 break;
       }
     }
   }
  
   while(thirdCheck) {
     if (firstHalf.length() == 2 && firstHalf.at(0) == '6') {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 thirdCheck = false;
     }
     else  if (firstHalf.length() == 3 && firstHalf.at(1) == '6') {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 thirdCheck = false;
     }
     else  if (atoi(secondHalf.c_str()) < 60 && atoi(secondHalf.c_str()) > -1) {
       validPlayTime = true;
       thirdCheck = false;
     }
     else {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 thirdCheck = false;
     }
   }
   int num =  atoi(firstHalf.c_str()) * 60;
   int combined = num + atoi(secondHalf.c_str());
   discPtr->addToTotalPlayTime(combined);
  } 

   cout << "Please enter the location of the track (complete path and filename):\n";
   cin >> location;

   finished = true;
  }
 }
  else {

   while (!finished){
   validPlayTime = false;
 
   cout << "Please enter the title of the track:\n";
   getline(cin, name);

   cout << "Please enter the name of the artist:\n";
   getline(cin, artist);
  
      validPlayTime = false; 
  while (!validPlayTime) {
    cout << "Please enter the play time for the track:\n";
   cin >> play;

   bool firstCheck = true;
   bool secondCheck = false;
   bool thirdCheck = false;
   string semiColon = ":";

   if(play.length() < 3) {
     cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
     firstCheck = false;
     validPlayTime = false;     
   }
      
   string firstHalf = play.substr(0, play.find_first_of(semiColon));
   if (firstCheck) {
     for (string::size_type i = 0; i < firstHalf.length(); ++i) {
       if (isdigit(firstHalf.at(i)) && (firstHalf.length() == 1 || firstHalf.length() == 2)) {
	 validPlayTime = true;
	 secondCheck = true;
       }
        else {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 secondCheck = false;
	 break;
       }
     }
   }

   string secondHalf = play.substr((play.find_first_of(semiColon) + 1));
   if (secondCheck) {
     for (string::size_type i = 0; i < secondHalf.length(); ++i) {
       if (isdigit(secondHalf.at(i)) && secondHalf.length() == 2)
	 thirdCheck = true;
       else {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 break;
       }
     }
   }

   while(thirdCheck) {
     if (firstHalf.length() == 2 && firstHalf.at(0) == '6') {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 thirdCheck = false;
     }
     else  if (firstHalf.length() == 3 && firstHalf.at(1) == '6') {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 thirdCheck = false;
     }
     else  if (atoi(secondHalf.c_str()) < 60 && atoi(secondHalf.c_str()) > -1) {
       validPlayTime = true;
       thirdCheck = false;
     }
     else {
	 cout << "Invalid input, please use two integers (0-59) seperated by ':'\n";
	 validPlayTime = false;
	 thirdCheck = false;
     }
   }
   int num =  atoi(firstHalf.c_str()) * 60;
   int combined = num + atoi(secondHalf.c_str());
   discPtr->addToTotalPlayTime(combined);
  }

  cout << "Please enter the location of the track (complete path and filename):\n";
   cin >> location;

   finished = true;
   }
  }
}

void Track::printTrack() const {   
  cout << " " << getName() << endl;

 if (discPtr->isMultiArtist() ) {    
    cout << "Artist: "
         << getArtist() 
         << endl;
}
 cout << "Playtime: " << getPlayTime()
      << endl
      << "Path/filename: " << getPath() 
      << endl;
}

string Track::getPath() const {
  return location;
}

string Track::getArtist() const {
  return artist;
}

string Track::getName() const {
  return name;
}

int Track::getNumber() const {
    return number;
}

string Track::getPlayTime() const {
    return play;
  }
