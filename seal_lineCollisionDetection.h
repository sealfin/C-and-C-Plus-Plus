#ifndef seal_lineCollisionDetection_h

#define seal_lineCollisionDetection_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct t_seal_CollisionDetectionLineCoordinates_struct
{
  double m_x, m_y;
}
t_seal_CollisionDetectionLineCoordinates;

typedef enum
{
  k_seal_COLLISION_DETECTION_LINE_TYPE__HORIZONTAL,
  k_seal_COLLISION_DETECTION_LINE_TYPE__VERTICAL,
  k_seal_COLLISION_DETECTION_LINE_TYPE__NON_HORIZONTAL_AND_NON_VERTICAL
}
t_seal_CollisionDetectionLineType;

typedef struct t_seal_CollisionDetectionLine_struct
{
  t_seal_CollisionDetectionLineCoordinates m_begin, m_end;
  double m_width /* w. */, m_height /* h. */, m_horizontalMidpoint /* s. */, m_verticalMidpoint /* t. */, m_slope /* m. */, m_yIntercept /* b. */;
  t_seal_CollisionDetectionLineType m_type;
}
t_seal_CollisionDetectionLine;

t_seal_CollisionDetectionLine f_seal_NewCollisionDetectionLine( const double p_x1, const double p_y1, const double p_x2, const double p_y2 );

typedef enum
{
  k_seal_LINE_COLLISION_DETECTED__NO = 0,
  k_seal_LINE_COLLISION_DETECTED__YES,
  k_seal_LINE_COLLISION_DETECTED__YES__COINCIDENT
}
t_seal_LineCollisionDetected;

typedef struct t_seal_LineCollision_struct
{
  t_seal_LineCollisionDetected m_detected;
  t_seal_CollisionDetectionLineCoordinates m_at;
}
t_seal_LineCollision;

t_seal_LineCollision f_seal_LineCollision( const t_seal_CollisionDetectionLine * const p_a, const t_seal_CollisionDetectionLine * const p_b );

#ifdef __cplusplus
}
#endif

#endif
