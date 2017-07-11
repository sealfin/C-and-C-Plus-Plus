#include "seal_math.h"
#include <math.h>

const double k_seal_PI = 3.141592654;

double f_seal_DegreesToRadians( const double p )
{
  return p * k_seal_PI / 180;
}

double f_seal_RadiansToDegrees( const double p )
{
  return p * 180 / k_seal_PI;
}

double f_seal_XComponentOfVector( const double p_direction, const double p_magnitude )
{
  return sin( f_seal_DegreesToRadians( p_direction )) * p_magnitude;
}

double f_seal_YComponentOfVector( const double p_direction, const double p_magnitude )
{
  return cos( f_seal_DegreesToRadians( p_direction )) * p_magnitude;
}

double f_seal_DirectionOfVector( const double p_xComponent, const double p_yComponent )
{
  if(( p_xComponent == 0 ) || ( p_yComponent == 0 ))
  {
    if( p_xComponent > 0 )
      return 90;
    if( p_xComponent < 0 )
      return 270;
    if( p_yComponent > 0 )
      return 0;
    if( p_yComponent < 0 )
      return 180;
    /* p_xComponent == 0 && p_yComponent == 0 */
    return 0;
  }
  {
    /* p_xComponent != 0 && p_yComponent != 0 */
    const double d = f_seal_RadiansToDegrees( atan( p_yComponent / p_xComponent ));
    if(( p_xComponent > 0 ) && ( p_yComponent > 0 ))
      return 90 - d;
    if(( p_xComponent > 0 ) && ( p_yComponent < 0 ))
      return fabs( d ) + 90;
    if(( p_xComponent < 0 ) && ( p_yComponent < 0 ))
      return 270 - d;
    /* p_xComponent < 0 && p_yComponent > 0 */
    return fabs( d ) + 270;
  }
}

double f_seal_MagnitudeOfVector( const double p_xComponent, const double p_yComponent )
{
  return sqrt( pow( fabs( p_xComponent ), 2 ) + pow( fabs( p_yComponent ), 2 ));
}

static double f_seal_ClampDegrees( double p )
{
  while( p < 0 )
    p += 360;
  while( p >= 360 )
    p -= 360;
  return p;
}

double f_seal_AddDegrees( const double a, const double b )
{
  return f_seal_ClampDegrees( a + b );
}

double f_seal_SubtractDegrees( const double a, const double b )
{
  return f_seal_ClampDegrees( a - b );
}

bool f_seal_Left( const double a, double b )
{
  double u1, d1 = f_seal_ClampDegrees( a ) - 180, u2, d2;
  if( d1 < 0 )
  {
    u1 = 360;
    d1 = f_seal_ClampDegrees( d1 );
    d2 = 0;
    u2 = f_seal_ClampDegrees( a );
  }
  else
  {
    d2 = d1 = f_seal_ClampDegrees( d1 );
    u2 = u1 = f_seal_ClampDegrees( a );
  }
  b = f_seal_ClampDegrees( b );
  return ((( b > d1 ) && ( b < u1 ))
    || (( b > d2 ) && ( b < u2 )));
}

bool f_seal_Right( const double a, double b )
{
  double u1 = f_seal_ClampDegrees( a ) + 180, d1, u2, d2;
  if( u1 >= 360 )
  {
    d1 = 0;
    u1 = f_seal_ClampDegrees( u1 );
    d2 = f_seal_ClampDegrees( a );
    u2 = 360;
  }
  else
  {
    d2 = d1 = f_seal_ClampDegrees( a );
    u2 = u1 = f_seal_ClampDegrees( u1 );
  }
  b = f_seal_ClampDegrees( b );
  return ((( b > d1 ) && ( b < u1 ))
    || (( b > d2 ) && ( b < u2 )));
}

bool f_seal_In( const double p_leftBoundary, const double p_rightBoundary, const double p_angle )
{
  double d1 = f_seal_ClampDegrees( p_leftBoundary ), u1 = f_seal_ClampDegrees( p_rightBoundary ), range = u1 - d1, d2, u2;
  if( range < 0 )
    range += 360;
  if( d1 + range < 360 )
  {
    d2 = d1;
    u2 = u1;
  }
  else
  {
    u1 = 360;
    d2 = 0;
    u2 = f_seal_AddDegrees( d1, range );
  }
  return ((( p_angle >= d1 ) && ( p_angle <= u1 ))
    || (( p_angle >= d2 ) && ( p_angle <= u2 )));
}
