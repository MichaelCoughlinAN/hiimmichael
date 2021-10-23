#include <stdio.h>
#include <math.h>

main()
{
  int i, j ;
  int i4, j4 ;

  printf( "\n        " ) ;
  for( j = 1 ; j < 10 ; j++ ) {
    printf( "%1d       ", j ) ;
  }
  printf( "\n\n" ) ;

  for( i = 1 ; i <= 10 ; i++ ) {
    i4 = i*i*i*i ;
    printf( "%2d| %5d %2d", i, i4, i4%15 ) ;
    for( j = 2 ; j < i ; j++ ) {
      j4 = j*j*j*j ;
      printf( " %4d %2d", i4 - j4 + 1, (i4 - j4 + 1)%15 ) ;
    }
    printf( "\n  |\n" ) ;
  }
/*
  printf( "%f\n", pow(5.0, 5.0) ) ;
*/
}

