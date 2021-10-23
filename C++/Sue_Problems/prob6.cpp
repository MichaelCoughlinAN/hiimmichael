// Program to solve problem 6 of Oct 23

#include <iostream>
//using namespace std ;

bool solvesIt( int w1, int w2, int w3, int w4 ) ;
void printResults( int w1, int w2, int w3, int w4 ) ;

int coefs[41][5] ;

int main()
{
  int w1, w2, w3, w4, count = 0 ;

  for ( w1 = 1 ; w1 <= 10 ; w1++ ) {
    for ( w2 = w1 ; w2 <= (40 - w1)/3 ; w2++ ) {
      for ( w3 = w2 ; w3 <= (40 - w1 - w2)/2 ; w3++ ) {
        w4 = 40 - w1 - w2 - w3 ;
        if ( solvesIt( w1, w2, w3, w4 ) ) {
          printResults( w1, w2, w3, w4 ) ;
        }
//        count++ ;
      }
    }
  }

//  cout << "\nThere were " << count << " iterations\n" ;

/*
*/
}


bool solvesIt ( int w1, int w2, int w3, int w4 )
{
  int i, j, k, c1, c2, c3, c4 ;
  bool represented[41] ;
  bool solved = true ;
  
  for ( k = 1 ; k <= 40 ; k++ ) {
    represented[k] = false ;
  }

  for ( c1 = -1 ; c1 <= 1 ; c1 ++ ) {
    for ( c2 = -1 ; c2 <= 1 ; c2 ++ ) {
      for ( c3 = -1 ; c3 <= 1 ; c3 ++ ) {
        for ( c4 = -1 ; c4 <= 1 ; c4 ++ ) {
          i = c1*w1 + c2*w2 + c3*w3 + c4*w4 ;
          if ( i > 40 ) cout << "i: " << i << " is > 40n" ;
          if ( ( i > 0 ) && ( i <= 40 ) ) {
            represented[i] = true ;
            coefs[i][1] = c1 ;
            coefs[i][2] = c2 ;
            coefs[i][3] = c3 ;
            coefs[i][4] = c4 ;
          }
        }
      }
    }
  }
  
  for ( k = 1 ; k <= 40 ; k++ ) {
    solved = solved && represented[k] ;
  }

  return solved ;
}

void printResults ( int w1, int w2, int w3, int w4 )
{
  int i ;

  cout << "\nSolution:" 
       << "\nw1 = " << w1 
       << ", w2 = " << w2
       << ", w3 = " << w3
       << ", w4 = " << w4 << endl ;

  cout << "\nRepresentations:\n" ;
  for ( i = 1 ; i < 10 ; i++ ) {
    cout << " " << i << " = " 
         << ((coefs[i][1] < 0) ? "" : " ") << coefs[i][1] << "*" << w1 << " + "
         << ((coefs[i][2] < 0) ? "" : " ") << coefs[i][2] << "*" << w2 << " + "
         << ((coefs[i][3] < 0) ? "" : " ") << coefs[i][3] << "*" << w3 << " + "
         << ((coefs[i][4] < 0) ? "" : " ") << coefs[i][4] << "*" << w4 << endl ;
  }
  for ( i = 10 ; i <= 40 ; i++ ) {
    cout << i << " = " 
         << ((coefs[i][1] < 0) ? "" : " ") << coefs[i][1] << "*" << w1 << " + "
         << ((coefs[i][2] < 0) ? "" : " ") << coefs[i][2] << "*" << w2 << " + "
         << ((coefs[i][3] < 0) ? "" : " ") << coefs[i][3] << "*" << w3 << " + "
         << ((coefs[i][4] < 0) ? "" : " ") << coefs[i][4] << "*" << w4 << endl ;
  }
}

