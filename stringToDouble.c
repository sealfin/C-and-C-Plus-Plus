#include "seal_stringToDouble_C.h"
#include "seal_bool.h"
#include <string.h>
#include <math.h>

static t_seal_STRING_TO_DOUBLE_ERROR_C g_error = k_seal_STRING_TO_DOUBLE_ERROR_C__NONE;
static FILE *g_printErrorsTo = NULL;

static int f_private( const size_t p_begin, const size_t p_end, const char * const p_string, const char * const p_part, const t_seal_STRING_TO_DOUBLE_ERROR_C p_error )
{
  size_t i = p_begin;
  int multiplier = 1, result = 0;
  for( ; i > p_end; i --, multiplier *= 10 )
    if(( p_string[ i - 1 ] >= '0' ) && ( p_string[ i - 1 ] <= '9' ))
      result += (( p_string[ i - 1 ] - '0' ) * multiplier );
    else
    {
      if( g_printErrorsTo != NULL )
        fprintf( g_printErrorsTo, "f_seal_StringToDouble_C - p contains a non-numerical character in the %s part ('%c').\n", p_part, p_string[ i - 1 ] );
      g_error = p_error;
      return 0;
    }
  return result;
}

double f_seal_StringToDouble_C( const char * const p )
{
  bool has_sign, negative;
  size_t end_i = 0, i;
  bool has_point = false;
  size_t point_i;
  int i_part;
  double result = 0;
  g_error = k_seal_STRING_TO_DOUBLE_ERROR_C__NONE;
  if( p == NULL )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_StringToDouble_C - p == NULL.\n" );
    g_error = k_seal_STRING_TO_DOUBLE_ERROR_C__P_IS_NULL;
    return 0;
  }
  if( strlen( p ) == 0 )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_StringToDouble_C - strlen( p ) == 0.\n" );
    g_error = k_seal_STRING_TO_DOUBLE_ERROR_C__P_IS_ZERO_CHARACTERS_LONG;
    return 0;
  }
  has_sign = ( p[ 0 ] == '+' ) || ( p[ 0 ] == '-' );
  negative = p[ 0 ] == '-';
  if( has_sign && ( strlen( p ) == 1 ))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_StringToDouble_C - p contains only a sign character ('%c').\n", p[ 0 ] );
    g_error = k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER;
    return 0;
  }
  if( has_sign )
    end_i ++;
  for( i = end_i; i < strlen( p ); i ++ )
    if( p[ i ] == '.' )
    {
      has_point = true;
      point_i = i;
      break;
    }
  if( has_point && ( strlen( p ) == 1 ))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_StringToDouble_C - p contains only a decimal point.\n" );
    g_error = k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_ONLY_A_DECIMAL_POINT;
    return 0;
  }
  if( has_sign && has_point && ( strlen( p ) == 2 ))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_StringToDouble_C - p contains no non-sign, non-decimal point characters.\n" );
    g_error = k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_NO_NON_SIGN_NON_DECIMAL_POINT_CHARACTERS;
    return 0;
  }
  i_part = f_private((( !has_point )?strlen( p ):point_i ), end_i, p, "integer", k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART );
  if( g_error != k_seal_STRING_TO_DOUBLE_ERROR_C__NONE )
    return 0;
  if( has_point )
  {
    int f_part = f_private( strlen( p ), point_i + 1, p, "fractional", k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART );
    size_t l;
    if( g_error != k_seal_STRING_TO_DOUBLE_ERROR_C__NONE )
      return 0;
    l = strlen( p ) - point_i;
    l --;
    result += f_part;
    if( l != 0 )
      result /= pow( 10, l );
  }
  result += i_part;
  if( negative )
    result = -result;
  return result;
}

t_seal_STRING_TO_DOUBLE_ERROR_C f_seal_StringToDouble_Error_C( void )
{
  return g_error;
}

void p_seal_StringToDouble_PrintErrorsTo_C( FILE *p )
{
  g_printErrorsTo = p;
}
