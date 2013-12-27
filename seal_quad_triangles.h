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

    void p_Set( const GLfloat p_bottomLeftX, const GLfloat p_bottomLeftY, const GLfloat p_width, const GLfloat p_height )
    {
      p_TopLeftCorner( p_bottomLeftX, p_bottomLeftY + p_height );
      p_TopRightCorner( p_bottomLeftX + p_width, p_bottomLeftY + p_height );
      p_BottomRightCorner( p_bottomLeftX + p_width, p_bottomLeftY );
      p_BottomLeftCorner( p_bottomLeftX, p_bottomLeftY );
    }

    void p_TopLeftCorner( const GLfloat x, const GLfloat y )
    {
      m_coordinates[ 10 ] = x;
      m_coordinates[ 11 ] = y;
    }

    void p_TopRightCorner( const GLfloat x, const GLfloat y )
    {
      m_coordinates[ 4 ] = x;
      m_coordinates[ 5 ] = y;
      m_coordinates[ 8 ] = x;
      m_coordinates[ 9 ] = y;
    }

    void p_BottomRightCorner( const GLfloat x, const GLfloat y )
    {
      m_coordinates[ 2 ] = x;
      m_coordinates[ 3 ] = y;
    }

    void p_BottomLeftCorner( const GLfloat x, const GLfloat y )
    {
      m_coordinates[ 0 ] = x;
      m_coordinates[ 1 ] = y;
      m_coordinates[ 6 ] = x;
      m_coordinates[ 7 ] = y;
    }
};

#endif
