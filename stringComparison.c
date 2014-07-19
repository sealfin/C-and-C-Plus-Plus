#include "seal_stringComparison.h"
#include <string.h>
#include <ctype.h>

bool f_seal_CompareStrings_IgnoreCase( const char * const a, const char * const b )
{
  if(( a == NULL ) && ( b == NULL ))
    return true;
  if(( a == NULL ) || ( b == NULL ))
    return false;
  {
    const size_t a_length = strlen( a );
    size_t i = 0;
    if( a_length != strlen( b ))
      return false;
    for( ; i < a_length; i ++ )
      if( tolower( a[ i ] ) != tolower( b[ i ] ))
        return false;
    return true;
  }
}

int f_seal_CompareStringsLexicographically_IgnoreCase( const char * const a, const char * const b )
{
  if(( a == NULL ) && ( b == NULL ))
    return 0;
  if(( a != NULL ) && ( b == NULL ))
    return 1;
  if(( a == NULL ) && ( b != NULL ))
    return -1;
  {
    const size_t a_length = strlen( a ), b_length = strlen( b );
    size_t i = 0;
    for( ; ( i < a_length ) && ( i < b_length ); i ++ )
    {
      const char a_lowercase = tolower( a[ i ] ), b_lowercase = tolower( b[ i ] );
      if( a_lowercase != b_lowercase )
        return a_lowercase - b_lowercase;
    }
    if( a_length > b_length )
      return 1;
    if( b_length > a_length )
      return -1;
    return 0;
  }
}
