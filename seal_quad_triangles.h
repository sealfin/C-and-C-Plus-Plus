#ifndef seal_quad_triangles_h

#define seal_quad_triangles_h

#include <OpenGL/OpenGL.h>

class seal_Quad_Triangles
{
  public:
    GLfloat m_coordinates[ 12 ];

  public:
    seal_Quad_Triangles( void ){}

    seal_Quad_Triangles( const GLfloat p_bottomLeftX, const GLfloat p_bottomLeftY, const GLfloat p_width, const GLfloat p_height )
    {
      p_Set( p_bottomLeftX, p_bottomLeftY, p_width, p_height );
    }

    seal_Quad_Triangles( seal_Quad_Triangles *p )
    {
      p_Set( p );
    }

    void p_Set( const GLfloat p_bottomLeftX, const GLfloat p_bottomLeftY, const GLfloat p_width, const GLfloat p_height )
    {
      p_SetTopLeftCorner( p_bottomLeftX, p_bottomLeftY + p_height );
      p_SetTopRightCorner( p_bottomLeftX + p_width, p_bottomLeftY + p_height );
      p_SetBottomRightCorner( p_bottomLeftX + p_width, p_bottomLeftY );
      p_SetBottomLeftCorner( p_bottomLeftX, p_bottomLeftY );
    }

    void p_Set( seal_Quad_Triangles *p )
    {
      GLfloat x, y;
      p->p_GetTopLeftCorner( &x, &y );
      p_SetTopLeftCorner( x, y );
      p->p_GetTopRightCorner( &x, &y );
      p_SetTopRightCorner( x, y );
      p->p_GetBottomRightCorner( &x, &y );
      p_SetBottomRightCorner( x, y );
      p->p_GetBottomLeftCorner( &x, &y );
      p_SetBottomLeftCorner( x, y );
    }

    void p_SetTopLeftCorner( const GLfloat x, const GLfloat y )
    {
      m_coordinates[ 10 ] = x;
      m_coordinates[ 11 ] = y;
    }

    void p_SetTopRightCorner( const GLfloat x, const GLfloat y )
    {
      m_coordinates[ 4 ] = x;
      m_coordinates[ 5 ] = y;
      m_coordinates[ 8 ] = x;
      m_coordinates[ 9 ] = y;
    }

    void p_SetBottomRightCorner( const GLfloat x, const GLfloat y )
    {
      m_coordinates[ 2 ] = x;
      m_coordinates[ 3 ] = y;
    }

    void p_SetBottomLeftCorner( const GLfloat x, const GLfloat y )
    {
      m_coordinates[ 0 ] = x;
      m_coordinates[ 1 ] = y;
      m_coordinates[ 6 ] = x;
      m_coordinates[ 7 ] = y;
    }

    void p_GetTopLeftCorner( GLfloat *x, GLfloat *y )
    {
      *x = m_coordinates[ 10 ];
      *y = m_coordinates[ 11 ];
    }

    void p_GetTopRightCorner( GLfloat *x, GLfloat *y )
    {
      *x = m_coordinates[ 4 ];
      *y = m_coordinates[ 5 ];
    }

    void p_GetBottomRightCorner( GLfloat *x, GLfloat *y )
    {
      *x = m_coordinates[ 2 ];
      *y = m_coordinates[ 3 ];
    }

    void p_GetBottomLeftCorner( GLfloat *x, GLfloat *y )
    {
      *x = m_coordinates[ 0 ];
      *y = m_coordinates[ 1 ];
    }
};

#endif
