#ifndef seal_stringComparison_h

#define seal_stringComparison_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "seal_bool.h"

bool f_seal_CompareStrings_IgnoreCase( const char * const a, const char * const b );
/*
Returns true if a == NULL && b == NULL.
Returns false if ( a == NULL || b == NULL ) && a != b.
*/
int f_seal_CompareStringsLexicographically_IgnoreCase( const char * const a, const char * const b );
/*
Returns 0 if a == NULL && b == NULL.
Returns 1 if a != NULL && b == NULL.
Returns -1 if a == NULL && b != NULL.
*/

#ifdef __cplusplus
}
#endif

#endif
