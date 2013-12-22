#ifndef seal_math_h

#define seal_math_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "seal_bool.h"

double f_seal_DegreesToRadians( const double p );
double f_seal_RadiansToDegrees( const double p );
double f_seal_XComponentOfVector( const double p_direction, const double p_magnitude );
double f_seal_YComponentOfVector( const double p_direction, const double p_magnitude );
double f_seal_DirectionOfVector( const double p_xComponent, const double p_yComponent );
double f_seal_MagnitudeOfVector( const double p_xComponent, const double p_yComponent );
double f_seal_AddDegrees( const double a, const double b );
double f_seal_SubtractDegrees( const double a, const double b );
/* Returns a - b. */
bool f_seal_Left( const double a, double b );
/* Returns true if b is to the left - within 180 degrees - of a. */
bool f_seal_Right( const double a, double b );
/* Returns true of b is to the right - within 180 degrees - of a. */
bool f_seal_In( const double p_leftBoundary, const double p_rightBoundary, const double p_angle );

#ifdef __cplusplus
}
#endif

#endif
