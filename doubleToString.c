#include "seal_doubleToString.h"
#include <math.h>

static void p_private( char *p_string, size_t *p_i, int p_int, int p_divisor )
{
  do
  {
    const int divisionResult = p_int / p_divisor;
    p_int -= ( divisionResult * p_divisor );
    p_divisor /= 10;
    p_string[ ( *p_i ) ++ ] = '0' + divisionResult;
  }
  while( p_divisor != 0 );
}

char *f_seal_DoubleToString( double p_double, const size_t p_numberOfFractionalPartDigits, const bool p_explicitSign )
{
  const bool negative = p_double < 0;
  size_t sLength = 1;
  int i_part, divisor = 0;
  char *s;
  size_t i = 0;

  if( negative )
    p_double = -p_double;

  if(( negative || p_explicitSign ) && ( p_double != 0 ))
    sLength ++;
  i_part = p_double;
  do
  {
    if( divisor != 0 )
      divisor *= 10;
    else
      divisor = 1;
    sLength ++;
  }
  while( i_part / divisor >= 10 );
  if( p_numberOfFractionalPartDigits > 0 )
    sLength += ( p_numberOfFractionalPartDigits + 1 );

  s = ( char* )malloc( sizeof( char ) * sLength );

  if(( negative || p_explicitSign ) && ( p_double != 0 ))
    if( negative )
      s[ i ++ ] = '-';
    else
      s[ i ++ ] = '+';

  p_private( s, &i, i_part, divisor );

  if( p_numberOfFractionalPartDigits > 0 )
  {
    int f_part;
    s[ i ++ ] = '.';
    divisor = pow( 10, p_numberOfFractionalPartDigits );
    f_part = p_double * divisor;
    f_part -= (( int )p_double ) * divisor;
    p_private( s, &i, f_part, divisor / 10 );
  }

  s[ i ] = '\0';
  return s;
}
