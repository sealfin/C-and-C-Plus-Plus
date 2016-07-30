#include "seal_lineCollisionDetection.h"
#include "seal_bool.h"
#include <math.h>

t_seal_CollisionDetectionLine f_seal_NewCollisionDetectionLine( const double p_x1, const double p_y1, const double p_x2, const double p_y2 )
{
  t_seal_CollisionDetectionLine line;
  line.m_begin.m_x = p_x1;
  line.m_begin.m_y = p_y1;
  line.m_end.m_x = p_x2;
  line.m_end.m_y = p_y2;
  line.m_width = fabs( p_x2 - p_x1 );
  line.m_height = fabs( p_y2 - p_y1 );
  line.m_horizontalMidpoint = ( p_x1 + p_x2 ) / 2;
  line.m_verticalMidpoint = ( p_y1 + p_y2 ) / 2;
  {
    const double delta_x = p_x2 - p_x1;
    if( delta_x == 0 )
      line.m_type = k_seal_COLLISION_DETECTION_LINE_TYPE__VERTICAL;
    else
    {
      const double delta_y = p_y2 - p_y1;
      if( delta_y == 0 )
      {
        line.m_slope = 0;
        line.m_yIntercept = p_y1;
        line.m_type = k_seal_COLLISION_DETECTION_LINE_TYPE__HORIZONTAL;
      }
      else
      {
        line.m_slope = delta_y / delta_x;
        line.m_yIntercept = -1 * line.m_slope * p_x1 + p_y1;
        line.m_type = k_seal_COLLISION_DETECTION_LINE_TYPE__NON_HORIZONTAL_AND_NON_VERTICAL;
      }
    }
  }
  return line;
}

/* The following function assumes that `p_collision->m_detected == k_seal_LINE_COLLISION_DETECTED__NO`. */
static
#ifndef LEONARDO
/* It would be helpful if Leonardo IDE treated the `inline` qualifier as a no-op if it doesn't support that qualifier… */
inline
#endif
bool f_seal_LineCollision_Algorithm3( const t_seal_CollisionDetectionLine * const p_a, const t_seal_CollisionDetectionLine * const p_b, t_seal_LineCollision *p_collision )
{
  if(( p_a->m_type != k_seal_COLLISION_DETECTION_LINE_TYPE__VERTICAL )
    && ( p_b->m_type == k_seal_COLLISION_DETECTION_LINE_TYPE__VERTICAL ))
  {
    p_collision->m_at.m_x = p_b->m_begin.m_x;
    p_collision->m_at.m_y = p_a->m_slope * p_b->m_begin.m_x + p_a->m_yIntercept;

    // i.
    if( !( fabs( p_collision->m_at.m_x - p_a->m_horizontalMidpoint ) < p_a->m_width / 2 ))
      goto l_END_OF_FUNCTION;

    // ii.
    {
      const double d = fabs( p_collision->m_at.m_y - p_a->m_verticalMidpoint );
      if( !(( /* d == 0 */ p_a->m_type == k_seal_COLLISION_DETECTION_LINE_TYPE__HORIZONTAL ) || ( d < p_a->m_height / 2 )))
        goto l_END_OF_FUNCTION;
    }

    // iii.
    if( !( fabs( p_collision->m_at.m_y - p_b->m_verticalMidpoint ) < p_b->m_height / 2 ))
      goto l_END_OF_FUNCTION;

    p_collision->m_detected = k_seal_LINE_COLLISION_DETECTED__YES;
    l_END_OF_FUNCTION:return true;
  }
  return false;
}

/* The following function assumes that `p_b->m_type != k_seal_COLLISION_DETECTION_LINE_TYPE__VERTICAL`, that the two lines are neither coincident nor parallel, and that `p_collision->m_detected == k_seal_LINE_COLLISION_DETECTED__NO`. */
static
#ifndef LEONARDO
/* Again, it would be helpful if Leonardo IDE treated the `inline` qualifier as a no-op if it doesn't support that qualifier… */
inline
#endif
bool f_seal_LineCollision_Algorithm4( const t_seal_CollisionDetectionLine * const p_a, const t_seal_CollisionDetectionLine * const p_b, t_seal_LineCollision *p_collision )
{
  if( p_a->m_type == k_seal_COLLISION_DETECTION_LINE_TYPE__NON_HORIZONTAL_AND_NON_VERTICAL )
  {
    p_collision->m_at.m_x = ( p_b->m_yIntercept - p_a->m_yIntercept ) / ( p_a->m_slope - p_b->m_slope );
    p_collision->m_at.m_y = ( -1 * p_b->m_slope * p_a->m_yIntercept + p_a->m_slope * p_b->m_yIntercept ) / ( p_a->m_slope - p_b->m_slope );

    // i.
    if( !( fabs( p_collision->m_at.m_x - p_a->m_horizontalMidpoint ) < p_a->m_width / 2 ))
      goto l_END_OF_FUNCTION;

    // ii.
    if( !( fabs( p_collision->m_at.m_y - p_a->m_verticalMidpoint ) < p_a->m_height / 2 ))
      goto l_END_OF_FUNCTION;

    // iii.
    if( !( fabs( p_collision->m_at.m_x - p_b->m_horizontalMidpoint ) < p_b->m_width / 2 ))
      goto l_END_OF_FUNCTION;

    // iv.
    {
      const double d = fabs( p_collision->m_at.m_y - p_b->m_verticalMidpoint );
      if( !(( /* d == 0 */ p_b->m_type == k_seal_COLLISION_DETECTION_LINE_TYPE__HORIZONTAL ) || ( d < p_b->m_height / 2 )))
        goto l_END_OF_FUNCTION;
    }

    p_collision->m_detected = k_seal_LINE_COLLISION_DETECTED__YES;
    l_END_OF_FUNCTION:return true;
  }
  return false;
}

t_seal_LineCollision f_seal_LineCollision( const t_seal_CollisionDetectionLine * const p_a, const t_seal_CollisionDetectionLine * const p_b )
{
  t_seal_LineCollision collision;
  collision.m_detected = k_seal_LINE_COLLISION_DETECTED__NO;

  // Algorithm 1.
  if(( p_a->m_type == k_seal_COLLISION_DETECTION_LINE_TYPE__HORIZONTAL )
    && ( p_b->m_type == k_seal_COLLISION_DETECTION_LINE_TYPE__HORIZONTAL ))
  {
    if( p_a->m_begin.m_y == p_b->m_begin.m_y )
      if( fabs( p_a->m_horizontalMidpoint - p_b->m_horizontalMidpoint ) < ( p_a->m_width + p_b->m_width ) / 2 )
        collision.m_detected = k_seal_LINE_COLLISION_DETECTED__YES__COINCIDENT;
    return collision;
  }

  // Algorithm 2.
  if(( p_a->m_type == k_seal_COLLISION_DETECTION_LINE_TYPE__VERTICAL )
    && ( p_b->m_type == k_seal_COLLISION_DETECTION_LINE_TYPE__VERTICAL ))
  {
    if( p_a->m_begin.m_x == p_b->m_begin.m_x )
      if( fabs( p_a->m_verticalMidpoint - p_b->m_verticalMidpoint ) < ( p_a->m_height + p_b->m_height ) / 2 )
        collision.m_detected = k_seal_LINE_COLLISION_DETECTED__YES__COINCIDENT;
    return collision;
  }

  if( f_seal_LineCollision_Algorithm3( p_a, p_b, &collision ))
    return collision;
  if( f_seal_LineCollision_Algorithm3( p_b, p_a, &collision ))
    return collision;

  // Algorithm 5.
  if( p_a->m_slope == p_b->m_slope )
  {
    if( p_a->m_yIntercept == p_b->m_yIntercept )
      if( fabs( p_a->m_horizontalMidpoint - p_b->m_horizontalMidpoint ) < ( p_a->m_width + p_b->m_width ) / 2 )
        collision.m_detected = k_seal_LINE_COLLISION_DETECTED__YES__COINCIDENT;
    return collision;
  }

  if( f_seal_LineCollision_Algorithm4( p_a, p_b, &collision ))
    return collision;
  f_seal_LineCollision_Algorithm4( p_b, p_a, &collision );
  return collision;
}
