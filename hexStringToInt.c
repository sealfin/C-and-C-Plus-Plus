#include "seal_hexStringToInt_C.h"
#include "seal_bool.h"
#include <string.h>
#include <ctype.h>

static t_seal_HEX_STRING_TO_INT_ERROR_C g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__NONE;
static FILE *g_printErrorsTo = NULL;

int f_seal_HexStringToInt_C( const char * const p )
{
  bool has_sign, negative;
  size_t end_i = 0;
  bool has_prefix;
  size_t i;
  int multiplier = 1, result = 0;
  g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__NONE;
  if( p == NULL )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_HexStringToInt_C - p == NULL.\n" );
    g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__P_IS_NULL;
    return 0;
  }
  if( strlen( p ) == 0 )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_HexStringToInt_C - strlen( p ) == 0.\n" );
    g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__P_IS_ZERO_CHARACTERS_LONG;
    return 0;
  }
  has_sign = ( p[ 0 ] == '+' ) || ( p[ 0 ] == '-' );
  negative = p[ 0 ] == '-';
  if( has_sign && ( strlen( p ) == 1 ))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_HexStringToInt_C - p contains only a sign character ('%c').\n", p[ 0 ] );
    g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER;
    return 0;
  }
  if( has_sign )
    end_i ++;
  has_prefix = ( strlen( p ) >= ( 2 + end_i )) && (( p[ 1 + end_i ] == 'x' ) || ( p[ 1 + end_i ] == 'X' ));
  if(( !has_sign ) && has_prefix && ( strlen( p ) == 2 ))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_HexStringToInt_C - p contains only a prefix (\"%s\").\n", p );
    g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_PREFIX;
    return 0;
  }
  if( has_prefix && ( p[ end_i ] != '0' ))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_HexStringToInt_C - p contains a non-'0' character as the first character in the prefix ('%c').\n", p[ end_i ] );
    g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX;
    return 0;
  }
  if( has_prefix )
    end_i += 2;
  if( strlen( p ) == end_i )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_HexStringToInt_C - p contains no non-sign, non-prefix characters.\n" );
    g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_NO_NON_SIGN_NON_PREFIX_CHARACTERS;
    return 0;
  }
  for( i = strlen( p ); i > end_i; i --, multiplier *= 16 )
    if(( p[ i - 1 ] >= '0' ) && ( p[ i - 1 ] <= '9' ))
      result += (( p[ i - 1 ] - '0' ) * multiplier );
    else
    {
      char c = tolower( p[ i - 1 ] );
      if(( c >= 'a' ) && ( c <= 'f' ))
        result += ((( c - 'a' ) + 10 ) * multiplier );
      else
      {
        if( g_printErrorsTo != NULL )
          fprintf( g_printErrorsTo, "f_seal_HexStringToInt_C - p contains a non-hexadecimal character ('%c').\n", c );
        g_error = k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER;
        return 0;
      }
    }
  if( negative )
    result = -result;
  return result;
}

t_seal_HEX_STRING_TO_INT_ERROR_C f_seal_HexStringToInt_Error_C( void )
{
  return g_error;
}

void p_seal_HexStringToInt_PrintErrorsTo_C( FILE *p )
{
  g_printErrorsTo = p;
}
