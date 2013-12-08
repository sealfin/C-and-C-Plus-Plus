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
