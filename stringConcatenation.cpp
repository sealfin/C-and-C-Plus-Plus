#include "seal_stringConcatenation.h"
#include "seal_stringConcatenation_C.h"
#include "seal_stringConcatenation_shared.h"

M_seal_CONCATENATE_STRINGS( f_seal_ConcatenateStrings, , throw "f_seal_ConcatenateStrings - p == NULL.";, throw "f_seal_ConcatenateStrings - the length of the concatenated string exceeds 2^(sizeof( size_t )*8)-2 characters.";, f_seal_StringConcatenation_PrintErrorsTo_C())
