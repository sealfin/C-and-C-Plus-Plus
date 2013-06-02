#include "seal_intToHexString.h"
#include <stdlib.h>

char *f_seal_IntToHexString( int p_int, const bool p_uppercase, const bool p_prefix, const bool p_uppercasePrefix, const bool p_explicitSign )
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
  if( p_prefix )
    sLength += 2;
  do
  {
    if( divisor != 0 )
      divisor *= 16;
    else
      divisor = 1;
    sLength ++;
  }
  while( p_int / divisor >= 16 );
  s = ( char* )malloc( sizeof( char ) * sLength );
  if(( negative || p_explicitSign ) && ( p_int != 0 ))
    if( negative )
      s[ i ++ ] = '-';
    else
      s[ i ++ ] = '+';
  if( p_prefix )
  {
    s[ i ++ ] = '0';
    s[ i ++ ] = (( !p_uppercasePrefix )?'x':'X' );
  }
  do
  {
    const int divisionResult = p_int / divisor;
    p_int -= ( divisionResult * divisor );
    divisor /= 16;
    if( divisionResult < 10 )
      s[ i ++ ] = '0' + divisionResult;
    else
      s[ i ++ ] = (( !p_uppercase )?'a':'A' ) + ( divisionResult - 10 );
  }
  while( divisor != 0 );
  s[ i ] = '\0';
  return s;
}
