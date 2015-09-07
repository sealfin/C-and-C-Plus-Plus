#ifndef seal_tileBackground_h

#define seal_tileBackground_h

#include "seal_texture.h"

class seal_TileBackground
{
  private:
    seal_Texture *m_texture;
    size_t m_width, m_height;
    GLfloat *m_geometryCoordinates, *m_textureCoordinates;
    size_t *m_subTextures;
    double m_bottomLeftX, m_bottomLeftY;

  public:
    seal_TileBackground( seal_Texture *p_texture, const size_t p_width, const size_t p_height );
    ~seal_TileBackground( void );
    void p_Render( void );
    size_t f_NumberOfSubTextures( void )
    {
      return m_texture->f_NumberOfSubTextures();
    }
    size_t f_SubTextureWidth( void )
    {
      return m_texture->f_SubTextureWidth();
    }
    size_t f_SubTextureHeight( void )
    {
      return m_texture->f_SubTextureHeight();
    }
    size_t f_Width( void )
    {
      return m_width;
    }
    size_t f_Height( void )
    {
      return m_height;
    }
    double f_Bottom( void )
    {
      return m_bottomLeftY;
    }
    double f_Top( void )
    {
      return m_bottomLeftY + m_height * m_texture->f_SubTextureHeight();
    }
    double f_Left( void )
    {
      return m_bottomLeftX;
    }
    double f_Right( void )
    {
      return m_bottomLeftX + m_width * m_texture->f_SubTextureWidth();
    }
    size_t f_GetSubTexture( const size_t p_x, const size_t p_y );
    void p_SetSubTexture( const size_t p_x, const size_t p_y, const size_t p_subTexture );
    void p_SetAllSubTextures( const size_t p );
    void p_HFlipSubTexture( const size_t p_x, const size_t p_y );
    void p_VFlipSubTexture( const size_t p_x, const size_t p_y );
    double f_GetBottomLeftX( void )
    {
      return m_bottomLeftX;
    }
    double f_GetBottomLeftY( void )
    {
      return m_bottomLeftY;
    }
    void p_SetBottomLeftX( double p )
    {
      m_bottomLeftX = p;
    }
    void p_SetBottomLeftY( double p )
    {
      m_bottomLeftY = p;
    }

  private:
    size_t f_XAndYToIndex( const size_t p_x, const size_t p_y )
    {
      return p_x + p_y * m_width;
    }
};

#endif
