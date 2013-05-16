#ifndef seal_stringConcatenation_C_h

#define seal_stringConcatenation_C_h

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
  k_seal_STRING_CONCATENATION_ERROR_C__NONE = 0,
  k_seal_STRING_CONCATENATION_ERROR_C__P_IS_NULL,
  k_seal_STRING_CONCATENATION_ERROR_C__CONCATENATED_STRING_TOO_LONG
}
t_seal_STRING_CONCATENATION_ERROR_C;

char *f_seal_ConcatenateStrings_C( char *p, ... );
t_seal_STRING_CONCATENATION_ERROR_C f_seal_StringConcatenation_Error_C( void );

#ifdef __cplusplus
}
#endif

#endif
