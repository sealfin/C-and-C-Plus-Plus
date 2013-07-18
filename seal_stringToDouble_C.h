#ifndef seal_stringToDouble_C_h

#define seal_stringToDouble_C_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

typedef enum
{
  k_seal_STRING_TO_DOUBLE_ERROR_C__NONE = 0,
  k_seal_STRING_TO_DOUBLE_ERROR_C__P_IS_NULL,
  k_seal_STRING_TO_DOUBLE_ERROR_C__P_IS_ZERO_CHARACTERS_LONG,
  k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER,
  k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_ONLY_A_DECIMAL_POINT,
  k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_NO_NON_SIGN_NON_DECIMAL_POINT_CHARACTERS,
  k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART,
  k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART
}
t_seal_STRING_TO_DOUBLE_ERROR_C;

double f_seal_StringToDouble_C( const char * const p );
t_seal_STRING_TO_DOUBLE_ERROR_C f_seal_StringToDouble_Error_C( void );
void p_seal_StringToDouble_PrintErrorsTo_C( FILE *p );
/* Default is NULL. */

#ifdef __cplusplus
}
#endif

#endif
