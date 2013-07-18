#include "seal_stringToDouble.h"
#include "seal_stringToDouble_C.h"

double f_seal_StringToDouble( const char * const p )
{
  const double result = f_seal_StringToDouble_C( p );
  const t_seal_STRING_TO_DOUBLE_ERROR_C error = f_seal_StringToDouble_Error_C();
  switch( error )
  {
    case k_seal_STRING_TO_DOUBLE_ERROR_C__P_IS_NULL:
      throw "f_seal_StringToDouble - p == NULL.";
    case k_seal_STRING_TO_DOUBLE_ERROR_C__P_IS_ZERO_CHARACTERS_LONG:
      throw "f_seal_StringToDouble - strlen( p ) == 0.";
    case k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER:
      throw "f_seal_StringToDouble - p contains only a sign character.";
    case k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_ONLY_A_DECIMAL_POINT:
      throw "f_seal_StringToDouble - p contains only a decimal point.";
    case k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_NO_NON_SIGN_NON_DECIMAL_POINT_CHARACTERS:
      throw "f_seal_StringToDouble - p contains no non-sign, non-decimal point characters.";
    case k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART:
      throw "f_seal_StringToDouble - p contains a non-numerical character in the integer part.";
    case k_seal_STRING_TO_DOUBLE_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART:
      throw "f_seal_StringToDouble - p contains a non-numerical character in the fractional part.";
  }
  return result;
}
