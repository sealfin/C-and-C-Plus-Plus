#ifndef seal_intToHexString_h

#define seal_intToHexString_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "seal_bool.h"

char *f_seal_IntToHexString( int p_int, const bool p_uppercase, const bool p_prefix, const bool p_uppercasePrefix, const bool p_explicitSign );

#ifdef __cplusplus
}
#endif

#endif
