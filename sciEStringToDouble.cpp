#include "seal_sciEStringToDouble.h"
#include "seal_sciEStringToDouble_C.h"

double f_seal_SciEStringToDouble( const char * const p )
{
  const double d = f_seal_SciEStringToDouble_C( p );
  if( f_seal_SciEStringToDouble_Error_C())
    throw "f_seal_SciEStringToDouble - an error occurred; by default, a description of the error will have been printed to stderr.";
  return d;
}
