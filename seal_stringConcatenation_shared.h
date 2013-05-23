#ifndef seal_stringConcatenation_shared_h

#define seal_stringConcatenation_shared_h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_seal_CONCATENATE_STRINGS( p_functionName, p_error_none, p_error_pIsNULL, p_error_concatenatedStringTooLong )                \
  char *p_functionName( char *p, ... )                                                                                                \
  {                                                                                                                                   \
    char *s;                                                                                                                          \
    va_list parameter;                                                                                                                \
    char *sParameter;                                                                                                                 \
    size_t sLength = 0;                                                                                                               \
    if( p == NULL )                                                                                                                   \
    {                                                                                                                                 \
      fprintf( stderr, #p_functionName " - p == NULL.\n" );                                                                           \
      p_error_pIsNULL                                                                                                                 \
      s = ( char* )malloc( sizeof( char ));                                                                                           \
      s[ 0 ] = '\0';                                                                                                                  \
      return s;                                                                                                                       \
    }                                                                                                                                 \
    va_start( parameter, p );                                                                                                         \
    sParameter = p;                                                                                                                   \
    do                                                                                                                                \
    {                                                                                                                                 \
      const size_t old_sLength = sLength;                                                                                             \
      sLength += strlen( sParameter );                                                                                                \
      if(( sLength == ( size_t )-1 ) || ( sLength < old_sLength ))                                                                    \
      {                                                                                                                               \
        fprintf( stderr, #p_functionName " - the length of the concatenated string exceeds 2^(sizeof( size_t )*8)-2 characters.\n" ); \
        p_error_concatenatedStringTooLong                                                                                             \
        s = ( char* )malloc( sizeof( char ));                                                                                         \
        s[ 0 ] = '\0';                                                                                                                \
        return s;                                                                                                                     \
      }                                                                                                                               \
    }                                                                                                                                 \
    while(( sParameter = va_arg( parameter, char* )) != NULL );                                                                       \
    va_end( parameter );                                                                                                              \
    s = ( char* )malloc( sizeof( char ) * ( sLength + 1 ));                                                                           \
    s[ 0 ] = '\0';                                                                                                                    \
    va_start( parameter, p );                                                                                                         \
    sParameter = p;                                                                                                                   \
    do                                                                                                                                \
    {                                                                                                                                 \
      strcat( s, sParameter );                                                                                                        \
    }                                                                                                                                 \
    while(( sParameter = va_arg( parameter, char* )) != NULL );                                                                       \
    va_end( parameter );                                                                                                              \
    p_error_none                                                                                                                      \
    return s;                                                                                                                         \
  }

#endif
