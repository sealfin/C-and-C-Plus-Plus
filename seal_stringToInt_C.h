#ifndef seal_stringToInt_C_h

#define seal_stringToInt_C_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

typedef enum
{
  k_seal_STRING_TO_INT_ERROR_C__NONE = 0,
  k_seal_STRING_TO_INT_ERROR_C__P_IS_NULL,
  k_seal_STRING_TO_INT_ERROR_C__P_IS_ZERO_CHARACTERS_LONG,
  k_seal_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER,
  k_seal_STRING_TO_INT_ERROR_C__SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER,
  k_seal_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER
}
t_seal_STRING_TO_INT_ERROR_C;

int f_seal_StringToInt_C( const char * const p );
t_seal_STRING_TO_INT_ERROR_C f_seal_StringToInt_Error_C( void );
void p_seal_StringToInt_PrintErrorsTo_C( FILE *p );
/* Default is NULL. */

#ifdef __cplusplus
}
#endif

#endif
