#ifndef seal_quadColours_triangles_h

#define seal_quadColours_triangles_h

#include <OpenGL/OpenGL.h>

class seal_QuadColours_Triangles
{
  public:
    GLfloat m_rgba[ 24 ];

  public:
    seal_QuadColours_Triangles( void ){}

    seal_QuadColours_Triangles( const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a )
    {
      p_Set( r, g, b, a );
    }

    seal_QuadColours_Triangles( seal_QuadColours_Triangles *p )
    {
      p_Set( p );
    }

    void p_Set( const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a )
    {
      size_t i = 0;
      for( ; i < 24; i += 4 )
      {
        m_rgba[ i ] = r;
        m_rgba[ i + 1 ] = g;
        m_rgba[ i + 2 ] = b;
        m_rgba[ i + 3 ] = a;
      }
    }

    void p_Set( seal_QuadColours_Triangles *p )
    {
      size_t i = 0;
      for( ; i < 24; i ++ )
        m_rgba[ i ] = p->m_rgba[ i ];
    }

    void p_SetTopLeftCorner( const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a )
    {
      m_rgba[ 20 ] = r;
      m_rgba[ 21 ] = g;
      m_rgba[ 22 ] = b;
      m_rgba[ 23 ] = a;
    }

    void p_SetTopRightCorner( const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a )
    {
      m_rgba[ 8 ] = m_rgba[ 16 ] = r;
      m_rgba[ 9 ] = m_rgba[ 17 ] = g;
      m_rgba[ 10 ] = m_rgba[ 18 ] = b;
      m_rgba[ 11 ] = m_rgba[ 19 ] = a;
    }

    void p_SetBottomRightCorner( const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a )
    {
      m_rgba[ 4 ] = r;
      m_rgba[ 5 ] = g;
      m_rgba[ 6 ] = b;
      m_rgba[ 7 ] = a;
    }

    void p_SetBottomLeftCorner( const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a )
    {
      m_rgba[ 0 ] = m_rgba[ 12 ] = r;
      m_rgba[ 1 ] = m_rgba[ 13 ] = g;
      m_rgba[ 2 ] = m_rgba[ 14 ] = b;
      m_rgba[ 3 ] = m_rgba[ 15 ] = a;
    }
};

#endif
