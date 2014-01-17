#include "seal_tileBackground.h"
#include <stdio.h>

seal_TileBackground::seal_TileBackground( seal_Texture *p_texture, const size_t p_width, const size_t p_height )
{
  if( p_texture == NULL )
  {
    fprintf( stderr, "seal_TileBackground::<constructor> - p_texture == NULL.\n" );
    throw "seal_TileBackground::<constructor> - an error occurred; by default, a description of the error will have been printed to stderr.";
  }
  if( p_width == 0 )
  {
    fprintf( stderr, "seal_TileBackground::<constructor> - p_width == 0.\n" );
    throw "seal_TileBackground::<constructor> - an error occurred; by default, a description of the error will have been printed to stderr.";
  }
  if( p_height == 0 )
  {
    fprintf( stderr, "seal_TileBackground::<constructor> - p_height == 0.\n" );
    throw "seal_TileBackground::<constructor> - an error occurred; by default, a description of the error will have been printed to stderr.";
  }
  m_texture = p_texture;
  m_width = p_width;
  m_height = p_height;
  m_geometryCoordinates = ( GLfloat* )malloc( sizeof( GLfloat ) * m_width * m_height * 12 );
  size_t x, y = 0;
  GLfloat x_pixel, y_pixel = 0;
  seal_Quad_Triangles q;
  size_t i = 0, k;
  for( ; y < m_height; y ++, y_pixel += m_texture->f_SubTextureHeight())
    for( x = 0, x_pixel = 0; x < m_width; x ++, x_pixel += m_texture->f_SubTextureWidth())
    {
      q.p_Set( x_pixel, y_pixel, m_texture->f_SubTextureWidth(), m_texture->f_SubTextureHeight());
      for( k = 0; k < 12; i ++, k ++ )
        m_geometryCoordinates[ i ] = q.m_coordinates[ k ];
    }
  m_textureCoordinates = ( GLfloat* )malloc( sizeof( GLfloat ) * m_width * m_height * 12 );
  m_subTextures = ( size_t* )malloc( sizeof( size_t ) * m_width * m_height );
  p_SetAllSubTextures( 0 );
  m_bottomLeftX = 0;
  m_bottomLeftY = 0;
}

seal_TileBackground::~seal_TileBackground( void )
{
  free( m_geometryCoordinates );
  free( m_textureCoordinates );
  free( m_subTextures );
}

void seal_TileBackground::p_Render( void )
{
  glVertexPointer( 2, GL_FLOAT, 0, m_geometryCoordinates );
  glTexCoordPointer( 2, GL_FLOAT, 0, m_textureCoordinates );
  m_texture->p_Bind();
  glPushMatrix();
  glTranslatef(( GLfloat )( GLint )m_bottomLeftX, ( GLfloat )( GLint )m_bottomLeftY, 0 );
  glDrawArrays( GL_TRIANGLES, 0, m_width * m_height * 6 );
  glPopMatrix();
}

#define M_seal_TILE_BACKGROUND__THROW_EXCEPTION_IF_X_OR_Y_IS_OUT_OF_BOUNDS( p )                                                         \
  if( p_x >= m_width )                                                                                                                  \
  {                                                                                                                                     \
    fprintf( stderr, "seal_TileBackground::" # p " - p_x (%lu) >= f_Width() (%lu).\n", p_x, m_width );                                  \
    throw "seal_TileBackground::" # p " - an error occurred; by default, a description of the error will have been printed to stderr."; \
  }                                                                                                                                     \
  if( p_y >= m_height )                                                                                                                 \
  {                                                                                                                                     \
    fprintf( stderr, "seal_TileBackground::" # p " - p_y (%lu) >= f_Height() (%lu).\n", p_y, m_height );                                \
    throw "seal_TileBackground::" # p " - an error occurred; by default, a description of the error will have been printed to stderr."; \
  }

size_t seal_TileBackground::f_GetSubTexture( const size_t p_x, const size_t p_y )
{
  M_seal_TILE_BACKGROUND__THROW_EXCEPTION_IF_X_OR_Y_IS_OUT_OF_BOUNDS( f_GetSubTexture )
  return m_subTextures[ f_XAndYToIndex( p_x, p_y ) ];
}

void seal_TileBackground::p_SetSubTexture( const size_t p_x, const size_t p_y, const size_t p_subTexture )
{
  M_seal_TILE_BACKGROUND__THROW_EXCEPTION_IF_X_OR_Y_IS_OUT_OF_BOUNDS( p_SetSubTexture )
  size_t i = f_XAndYToIndex( p_x, p_y );
  m_subTextures[ i ] = p_subTexture;
  seal_Quad_Triangles q;
  m_texture->p_GetSubTextureQuad( p_subTexture, &q );
  size_t k = 0;
  for( i *= 12; k < 12; i ++, k ++ )
    m_textureCoordinates[ i ] = q.m_coordinates[ k ];
}

void seal_TileBackground::p_SetAllSubTextures( const size_t p )
{
  size_t i = 0;
  for( ; i < m_width * m_height; i ++ )
    m_subTextures[ i ] = p;
  seal_Quad_Triangles q;
  m_texture->p_GetSubTextureQuad( p, &q );
  size_t k = 0;
  for( i = 0; i < m_width * m_height * 12; i ++, k ++ )
  {
    if( k == 12 )
      k = 0;
    m_textureCoordinates[ i ] = q.m_coordinates[ k ];
  }
}

void seal_TileBackground::p_HFlipSubTexture( const size_t p_x, const size_t p_y )
{
  M_seal_TILE_BACKGROUND__THROW_EXCEPTION_IF_X_OR_Y_IS_OUT_OF_BOUNDS( p_HFlipSubTexture )
  size_t k = 0, i = f_XAndYToIndex( p_x, p_y ) * 12;
  seal_Quad_Triangles q;
  for( ; k < 12; i ++, k ++ )
    q.m_coordinates[ k ] = m_geometryCoordinates[ i ];
  q.p_HFlip();
  for( k = 0, i -= 12; k < 12; i ++, k ++ )
    m_geometryCoordinates[ i ] = q.m_coordinates[ k ];
}

void seal_TileBackground::p_VFlipSubTexture( const size_t p_x, const size_t p_y )
{
  M_seal_TILE_BACKGROUND__THROW_EXCEPTION_IF_X_OR_Y_IS_OUT_OF_BOUNDS( p_VFlipSubTexture )
  size_t k = 0, i = f_XAndYToIndex( p_x, p_y ) * 12;
  seal_Quad_Triangles q;
  for( ; k < 12; i ++, k ++ )
    q.m_coordinates[ k ] = m_geometryCoordinates[ i ];
  q.p_VFlip();
  for( k = 0, i -= 12; k < 12; i ++, k ++ )
    m_geometryCoordinates[ i ] = q.m_coordinates[ k ];
}

#undef M_seal_TILE_BACKGROUND__THROW_EXCEPTION_IF_X_OR_Y_IS_OUT_OF_BOUNDS
