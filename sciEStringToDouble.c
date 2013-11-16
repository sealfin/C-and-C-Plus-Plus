#include "seal_sciEStringToDouble_C.h"
#include <string.h>
#include <math.h>

static bool g_error = false, g_printErrorsToSet = false;
static FILE *g_printErrorsTo = NULL;

static int f_int( const char * const p_string, const size_t p_begin, const size_t p_end, const char * const p_part )
{
  size_t i = p_end;
  int multiplier = 1, result = 0;
  for( ; i > p_begin; i --, multiplier *= 10 )
    if(( p_string[ i - 1 ] >= '0' ) && ( p_string[ i - 1 ] <= '9' ))
      result += (( p_string[ i - 1 ] - '0' ) * multiplier );
    else
    {
      if( g_printErrorsTo != NULL )
        fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - %s contains a non-numerical character ('%c').\n", p_part, p_string[ i - 1 ] );
      g_error = true;
      return 0;
    }
  return result;
}

static double f_double( const char * const p_string, size_t p_begin, const size_t p_end, const char * const p_part )
{
  const bool has_sign = ( p_string[ p_begin ] == '+' ) || ( p_string[ p_begin ] == '-' );
  size_t i;
  bool has_point = false;
  size_t point_i = p_end;
  int i_part;
  double result = 0;
  const bool negative = p_string[ p_begin ] == '-';
  if( has_sign )
  {
    p_begin ++;
    if( p_begin == p_end )
    {
      if( g_printErrorsTo != NULL )
        fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - %s contains only a sign character ('%c').\n", p_part, p_string[ p_begin - 1 ] );
      g_error = true;
      return 0;
    }
  }
  for( i = p_begin; i < p_end; i ++ )
    if( p_string[ i ] == '.' )
    {
      has_point = true;
      point_i = i;
      break;
    }
  if( has_sign && has_point && ( p_end - p_begin == 1 ))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - %s contains no non-sign, non-decimal point characters.\n", p_part );
    g_error = true;
    return 0;
  }
  if( has_point && ( p_end - p_begin == 1 ))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - %s contains only a decimal point.\n", p_part );
    g_error = true;
    return 0;
  }
  i_part = f_int( p_string, p_begin, point_i, p_part );
  if( g_error )
    return 0;
  if( has_point )
  {
    int f_part = f_int( p_string, point_i + 1, p_end, p_part );
    size_t l;
    if( g_error )
      return 0;
    l = p_end - point_i;
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

double f_seal_SciEStringToDouble_C( const char * const p )
{
  size_t e_i = 0;
  bool has_e = false, exponent_has_sign, negative_exponent;
  int exponent;
  double coefficient;
  g_error = false;
  if( !g_printErrorsToSet )
  {
    g_printErrorsToSet = true;
    g_printErrorsTo = stderr;
  }
  if( p == NULL )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - p == NULL.\n" );
    g_error = true;
    return 0;
  }
  if( strlen( p ) == 0 )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - strlen( p ) == 0.\n" );
    g_error = true;
    return 0;
  }
  if(( strlen( p ) == 1 ) && (( p[ 0 ] == 'e' ) || ( p[ 0 ] == 'E' )))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - p contains only the '%c' character.\n", p[ 0 ] );
    g_error = true;
    return 0;
  }
  for( ; e_i < strlen( p ); e_i ++ )
    if(( p[ e_i ] == 'e' ) || ( p[ e_i ] == 'E' ))
    {
      has_e = true;
      break;
    }
  if( !has_e )
    return f_double( p, 0, strlen( p ), "p" );
  if( e_i == 0 )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - p contains an exponent but no coefficient.\n" );
    g_error = true;
    return 0;
  }
  if( e_i == strlen( p ) - 1 )
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - p contains a coefficient but no exponent.\n" );
    g_error = true;
    return 0;
  }
  exponent_has_sign = ( p[ e_i + 1 ] == '+' ) || ( p[ e_i + 1 ] == '-' );
  negative_exponent = p[ e_i + 1 ] == '-';
  if( exponent_has_sign && ( e_i + 2 == strlen( p )))
  {
    if( g_printErrorsTo != NULL )
      fprintf( g_printErrorsTo, "f_seal_SciEStringToDouble_C - the exponent contains only a sign character ('%c').\n", p[ e_i + 1 ] );
    g_error = true;
    return 0;
  }
  exponent = f_int( p, e_i + 1 + (( exponent_has_sign )?1:0 ), strlen( p ), "the exponent" );
  if( g_error )
    return 0;
  if( negative_exponent )
    exponent = -exponent;
  coefficient = f_double( p, 0, e_i, "the coefficient" );
  if( g_error )
    return 0;
  return coefficient * pow( 10, exponent );
}

bool f_seal_SciEStringToDouble_Error_C( void )
{
  return g_error;
}

void p_seal_SciEStringToDouble_PrintErrorsTo_C( FILE *p )
{
  g_printErrorsToSet = true;
  g_printErrorsTo = p;
}
