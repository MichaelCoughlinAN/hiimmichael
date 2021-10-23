#include <stdio.h>
#include <math.h>

main()
{
  int i, j ;
  int i3, j3 ;

  printf( "\n        " ) ;
  for( j = 1 ; j < 10 ; j++ ) {
    printf( "%1d       ", j ) ;
  }
  printf( "\n\n" ) ;

  for( i = 1 ; i <= 10 ; i++ ) {
    i3 = i*i*i ;
    printf( "%2d| %5d %2d", i, i3, i3%7 ) ;
    for( j = 2 ; j < i ; j++ ) {
      j3 = j*j*j ;
      printf( " %4d %2d", i3 - j3 + 1, (i3 - j3 + 1)%7 ) ;
    }
    printf( "\n  |\n" ) ;
  }
/*
  printf( "%f\n", pow(5.0, 5.0) ) ;
*/
}

