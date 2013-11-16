#ifndef seal_sciEStringToDouble_C_h

#define seal_sciEStringToDouble_C_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "seal_bool.h"
#include <stdio.h>

double f_seal_SciEStringToDouble_C( const char * const p );
/* Converts a string representation of a number in scientific e notation - eg. 0.0e0, equivalent to 0.0x10^0 - to a double. */
bool f_seal_SciEStringToDouble_Error_C( void );
/* Returns false - viz. "no error" - if the function f_seal_SciEStringToDouble_C converted the string passed to it to a double without error. */
void p_seal_SciEStringToDouble_PrintErrorsTo_C( FILE *p );
/* Default is stderr. */

#ifdef __cplusplus
}
#endif

#endif
