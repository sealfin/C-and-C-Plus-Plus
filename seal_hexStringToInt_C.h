#ifndef seal_hexStringToInt_C_h

#define seal_hexStringToInt_C_h

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
  k_seal_HEX_STRING_TO_INT_ERROR_C__NONE = 0,
  k_seal_HEX_STRING_TO_INT_ERROR_C__P_IS_NULL,
  k_seal_HEX_STRING_TO_INT_ERROR_C__P_IS_ZERO_CHARACTERS_LONG,
  k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_SIGN_CHARACTER,
  k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_ONLY_A_PREFIX,
  k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX,
  k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_NO_NON_SIGN_NON_PREFIX_CHARACTERS,
  k_seal_HEX_STRING_TO_INT_ERROR_C__P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER
}
t_seal_HEX_STRING_TO_INT_ERROR_C;

int f_seal_HexStringToInt_C( const char * const p );
t_seal_HEX_STRING_TO_INT_ERROR_C f_seal_HexStringToInt_Error_C( void );

#ifdef __cplusplus
}
#endif

#endif
