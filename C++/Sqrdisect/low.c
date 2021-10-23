#include <stdio.h>
#include <math.h>

main()
{
  int i, j, k, l, m, n, iton, sum, mod15 ;
  int result[15][7] ;

  for( i = 0 ; i < 15 ; i++ ) {
    result[i][0] = 1300 ;
  }

  for( i = 0 ; i <= 16 ; i++ ) {
  for( j = 0 ; j <= 8 ; j++ ) {
  for( k = 0 ; k <= 3 ; k++ ) {
  for( l = 0 ; l <= 2 ; l++ ) {
  for( m = 0 ; m <= 2 ; m++ ) {
  for( n = 0 ; n <= 1 ; n++ ) {
    iton = i + j + k + l + m + n ;
    if ( (1 <= iton) && (iton <= 16) ) {
      sum = i*66 + j*146 + k*370 + l*450 + m*672 + n*754 + 16 - iton ;
      mod15 = sum%15 ;
      if ( sum < result[mod15][0] ) {
        result[mod15][0] = sum ;
        result[mod15][1] = i ;
        result[mod15][2] = j ;
        result[mod15][3] = k ;
        result[mod15][4] = l ;
        result[mod15][5] = m ;
        result[mod15][6] = n ;
      }
    }
  }
  }
  }
  }
  }
  }

  printf( "\nMod   Sum   66  146  370  450  672  754\n   |\n" ) ;
  for( i = 0 ; i < 15 ; i++ ) {
    printf( "%2d | %4d", i, result[i][0] ) ;
    for( j = 1 ; j <= 6 ; j++ ) {
      printf( "%5d", result[i][j] ) ;
    }
    printf( "\n   |\n" ) ;
  }
}
