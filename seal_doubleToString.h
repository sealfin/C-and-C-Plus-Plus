#ifndef seal_doubleToString_h

#define seal_doubleToString_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "seal_bool.h"
#include <stdlib.h>

char *f_seal_DoubleToString( double p_double, const size_t p_numberOfFractionalPartDigits, const bool p_explicitSign );

#ifdef __cplusplus
}
#endif

#endif
