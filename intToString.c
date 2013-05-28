#include "seal_intToString.h"
#include <stdlib.h>

char *f_seal_IntToString( int p_int, const bool p_explicitSign )
{
  const bool negative = p_int < 0;
  size_t sLength = 1;
  int divisor = 0;
  char *s;
  size_t i = 0;
  if( negative )
    p_int = -p_int;
  if(( negative || p_explicitSign ) && ( p_int != 0 ))
    sLength ++;
  do
  {
    if( divisor != 0 )
      divisor *= 10;
    else
      divisor = 1;
    sLength ++;
  }
  while( p_int / divisor >= 10 );
  s = ( char* )malloc( sizeof( char ) * sLength );
  if(( negative || p_explicitSign ) && ( p_int != 0 ))
    if( negative )
      s[ i ++ ] = '-';
    else
      s[ i ++ ] = '+';
  do
  {
    const int divisionResult = p_int / divisor;
    p_int -= ( divisionResult * divisor );
    divisor /= 10;
    s[ i ++ ] = '0' + divisionResult;
  }
  while( divisor != 0 );
  s[ i ] = '\0';
  return s;
}
