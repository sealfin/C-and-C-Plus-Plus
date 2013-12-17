#ifndef seal_collisionDetection_h

#define seal_collisionDetection_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "seal_bool.h"

typedef struct t_seal_CollisionDetectionAABB_struct
{
  double m_originX, m_originY, m_halfWidth, m_halfHeight;
}
t_seal_CollisionDetectionAABB;

bool f_seal_AABBCollision( const t_seal_CollisionDetectionAABB * const a, const t_seal_CollisionDetectionAABB * const b );

#ifdef __cplusplus
}
#endif

#endif
