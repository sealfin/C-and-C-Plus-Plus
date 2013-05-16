#include "seal_stringConcatenation_C.h"
#include "stringConcatenation.h"

static t_seal_STRING_CONCATENATION_ERROR_C g_error = k_seal_STRING_CONCATENATION_ERROR_C__NONE;

M_seal_CONCATENATE_STRINGS( f_seal_ConcatenateStrings_C, g_error = k_seal_STRING_CONCATENATION_ERROR_C__NONE;, g_error = k_seal_STRING_CONCATENATION_ERROR_C__P_IS_NULL;, g_error = k_seal_STRING_CONCATENATION_ERROR_C__CONCATENATED_STRING_TOO_LONG; )

t_seal_STRING_CONCATENATION_ERROR_C f_seal_StringConcatenation_Error_C( void )
{
  return g_error;
}
