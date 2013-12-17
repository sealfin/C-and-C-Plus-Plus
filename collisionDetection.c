#include "seal_collisionDetection.h"

static bool f_private( const double p_coordinateA, const double p_halfDimensionA, const double p_coordinateB, const double p_halfDimensionB )
{
  double d = p_coordinateA - p_coordinateB;
  if( d < 0 )
    d = -d;
  d -= ( p_halfDimensionA + p_halfDimensionB );
  return d < 0;
}

bool f_seal_AABBCollision( const t_seal_CollisionDetectionAABB * const a, const t_seal_CollisionDetectionAABB * const b )
{
  return f_private( a->m_originX, a->m_halfWidth, b->m_originX, b->m_halfWidth ) && f_private( a->m_originY, a->m_halfHeight, b->m_originY, b->m_halfHeight );
}
