#ifndef seal_texture_h

#define seal_texture_h

#include "seal_quad_triangles.h"
#include <stdlib.h>

class seal_Texture
{
  private:
    static seal_Texture *mg_bound;
    GLfloat m_textureMatrix[ 16 ];
    GLuint m_texture;
    size_t m_subTextureWidth, m_subTextureHeight, m_numberOfSubTextures;
    seal_Quad_Triangles **m_subTextureQuads;

  public:
    seal_Texture( const char * const p_imagePath, const size_t p_subTextureWidth, const size_t p_subTextureHeight );
    ~seal_Texture( void );
    void p_Bind( void );
    size_t f_NumberOfSubTextures( void )
    {
      return m_numberOfSubTextures;
    }
    size_t f_SubTextureWidth( void )
    {
      return m_subTextureWidth;
    }
    size_t f_SubTextureHeight( void )
    {
      return m_subTextureHeight;
    }
    void p_GetSubTextureQuad( const size_t p_subTexture, seal_Quad_Triangles *p_subTextureQuad );

  private:
    GLubyte *f_Pixels( const char * const p_imagePath, size_t *p_imageWidth, size_t *p_imageHeight );
    bool f_IsPowerOfTwo( const size_t p );
};

#endif
