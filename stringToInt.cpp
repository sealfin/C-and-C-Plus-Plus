#include "seal_stringToInt.h"
#include "seal_stringToInt_C.h"

int f_seal_StringToInt( const char * const p )
{
  const int result = f_seal_StringToInt_C( p );
  const t_seal_STRING_TO_INT_ERROR_C error = f_seal_StringToInt_Error_C();
  switch( error )
  {
    case k_seal_STRING_TO_INT_ERROR_C__P_IS_NULL:
      throw "f_seal_StringToInt - p == NULL.";
    case k_seal_STRING_TO_INT_ERROR_C__P_IS_ZERO_CHARACTERS_LONG:
      throw "f_seal_StringToInt - strlen( p ) == 0.";
    case k_seal_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER:
      throw "f_seal_StringToInt - p contains only a sign character.";
    case k_seal_STRING_TO_INT_ERROR_C__SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER:
      throw "f_seal_StringToInt - the sign character is not the first character.";
    case k_seal_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_NUMERICAL_CHARACTER:
      throw "f_seal_StringToInt - p contains a non-numerical character.";
  }
  return result;
}
