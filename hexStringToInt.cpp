#include "seal_hexStringToInt.h"
#include "seal_hexStringToInt_C.h"

int f_seal_HexStringToInt( const char * const p )
{
  const int result = f_seal_HexStringToInt_C( p );
  const t_seal_HEX_STRING_TO_INT_ERROR_C error = f_seal_HexStringToInt_Error_C();
  switch( error )
  {
    case k_seal_HEX_STRING_TO_INT_ERROR_C__P_IS_NULL:
      throw "f_seal_HexStringToInt - p == NULL.";
    case k_seal_HEX_STRING_TO_INT_ERROR_C__P_IS_ZERO_CHARACTERS_LONG:
      throw "f_seal_HexStringToInt - strlen( p ) == 0.";
    case k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER:
      throw "f_seal_HexStringToInt - p contains only a sign character.";
    case k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_PREFIX:
      throw "f_seal_HexStringToInt - p contains only a prefix.";
    case k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX:
      throw "f_seal_HexStringToInt - p contains a non-'0' character as the first character in the prefix.";
    case k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_NO_NON_SIGN_NON_PREFIX_CHARACTERS:
      throw "f_seal_HexStringToInt - p contains no non-sign, non-prefix characters.";
    case k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER:
      throw "f_seal_HexStringToInt - p contains a non-hexadecimal character.";
  }
  return result;
}
