#include "seal_stringToInt_C.h"
#include <stdio.h>
#include <string.h>

static t_seal_STRING_TO_INT_ERROR_C g_error = k_seal_STRING_TO_INT_ERROR_C__NONE;

int f_seal_StringToInt_C( const char * const p )
{
  size_t i;
  int multiplier = 1, result = 0;
  g_error = k_seal_STRING_TO_INT_ERROR_C__NONE;
  if( p == NULL )
  {
    fprintf( stderr, "f_seal_StringToInt_C - p == NULL.\n" );
    g_error = k_seal_STRING_TO_INT_ERROR_C__P_IS_NULL;
    return 0;
  }
  if( strlen( p ) == 0 )
  {
    fprintf( stderr, "f_seal_StringToInt_C - strlen( p ) == 0.\n" );
    g_error = k_seal_STRING_TO_INT_ERROR_C__P_IS_ZERO_CHARACTERS_LONG;
    return 0;
  }
  if(( strlen( p ) == 1 ) && (( p[ 0 ] == '+' ) || ( p[ 0 ] == '-' )))
  {
    fprintf( stderr, "f_seal_StringToInt_C - p contains only a sign character ('%c').\n", p[ 0 ] );
    g_error = k_seal_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER;
    return 0;
  }
  for( i = strlen( p ); i > 0; i --, multiplier *= 10 )
    if(( p[ i - 1 ] >= '0' ) && ( p[ i - 1 ] <= '9' ))
      result += (( p[ i - 1 ] - '0' ) * multiplier );
    else
      if( p[ i - 1 ] == '+' )
      {
        if( i - 1 == 0 )
          ;
        else
        {
          fprintf( stderr, "f_seal_StringToInt_C - the sign character ('+') is not the first character.\n" );
          g_error = k_seal_STRING_TO_INT_ERROR_C__SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER;
          return 0;
        }
      }
      else
        if( p[ i - 1 ] == '-' )
        {
          if( i - 1 == 0 )
            result = -result;
          else
          {
            fprintf( stderr, "f_seal_StringToInt_C - the sign character ('-') is not the first character.\n" );
            g_error = k_seal_STRING_TO_INT_ERROR_C__SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER;
            return 0;
          }
        }
        else
        {
          fprintf( stderr, "f_seal_StringToInt_C - p contains a non-numerical character ('%c').\n", p[ i - 1 ] );
          g_error = k_seal_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER;
          return 0;
        }
  return result;
}

t_seal_STRING_TO_INT_ERROR_C f_seal_StringToInt_Error_C( void )
{
  return g_error;
}
