#include "seal_texture.h"
#include <stdio.h>
#include <SDL2_image/SDL_image.h>

seal_Texture *seal_Texture::mg_bound = NULL;

seal_Texture::seal_Texture( const char * const p_imagePath, const size_t p_subTextureWidth, const size_t p_subTextureHeight )
{
  size_t textureWidth, textureHeight;
  GLubyte *p = f_Pixels( p_imagePath, &textureWidth, &textureHeight );
  size_t i = 0;
  for( ; i < 16; i ++ )
    m_textureMatrix[ i ] = 0;
  m_textureMatrix[ 0 ] = 1.0 / textureWidth;
  m_textureMatrix[ 5 ] = 1.0 / textureHeight;
  m_textureMatrix[ 10 ] = 1;
  m_textureMatrix[ 15 ] = 1;
  glGenTextures( 1, &m_texture );
  glBindTexture( GL_TEXTURE_2D, m_texture );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
  free( p );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  m_subTextureWidth = p_subTextureWidth;
  m_subTextureHeight = p_subTextureHeight;
  const size_t subTexturesWide = textureWidth / m_subTextureWidth, subTexturesHigh = textureHeight / m_subTextureHeight;
  m_numberOfSubTextures = subTexturesWide * subTexturesHigh;
  m_subTextureQuads = ( seal_Quad_Triangles** )malloc( sizeof( seal_Quad_Triangles* ) * m_numberOfSubTextures );
  size_t x, y = 0;
  GLfloat p_x, p_y = 0;
  i = 0;
  for( ; y < subTexturesHigh; y ++, p_y += m_subTextureHeight )
    for( x = 0, p_x = 0; x < subTexturesWide; x ++, p_x += m_subTextureWidth )
      m_subTextureQuads[ i ++ ] = new seal_Quad_Triangles( p_x, p_y, m_subTextureWidth, m_subTextureHeight );
}

seal_Texture::~seal_Texture( void )
{
  size_t i = 0;
  for( ; i < m_numberOfSubTextures; i ++ )
    delete m_subTextureQuads[ i ];
  free( m_subTextureQuads );
  glDeleteTextures( 1, &m_texture );
}

void seal_Texture::p_Bind( void )
{
  if( mg_bound != this )
  {
    mg_bound = this;
    glBindTexture( GL_TEXTURE_2D, m_texture );
    GLint matrixMode;
    glGetIntegerv( GL_MATRIX_MODE, &matrixMode );
    glMatrixMode( GL_TEXTURE );
    glLoadMatrixf( m_textureMatrix );
    glMatrixMode( matrixMode );
  }
}

void seal_Texture::p_GetSubTextureQuad( const size_t p_subTexture, seal_Quad_Triangles *p_subTextureQuad )
{
  if( p_subTexture >= m_numberOfSubTextures )
  {
    fprintf( stderr, "seal_Texture::p_GetSubTextureQuad - p_subTexture (%lu) >= f_NumberOfSubTextures() (%lu).\n", p_subTexture, m_numberOfSubTextures );
    throw "seal_Texture::p_GetSubTextureQuad - an error occurred; by default, a description of the error will have been printed to stderr.";
  }
  p_subTextureQuad->p_Set( m_subTextureQuads[ p_subTexture ] );
}

GLubyte *seal_Texture::f_Pixels( const char * const p_imagePath, size_t *p_imageWidth, size_t *p_imageHeight )
{
  SDL_Surface *s = IMG_Load( p_imagePath );
  if( s == NULL )
  {
    fprintf( stderr, "seal_Texture::<constructor> - unable to open the image \"%s\".\n", p_imagePath );
    throw "seal_Texture::<constructor> - an error occurred; by default, a description of the error will have been printed to stderr.";
  }
  if( s->format->BytesPerPixel != 4 )
  {
    fprintf( stderr, "seal_Texture::<constructor> - the image \"%s\" does not use 32bits per pixel, and support for %dbits per pixel has not yet been implemented.\n", p_imagePath, s->format->BytesPerPixel * 8 );
    SDL_FreeSurface( s );
    throw "seal_Texture::<constructor> - an error occurred; by default, a description of the error will have been printed to stderr.";
  }
  *p_imageWidth = s->w;
  if( !f_IsPowerOfTwo( *p_imageWidth ))
  {
    fprintf( stderr, "seal_Texture::<constructor> - the width of the image \"%s\" is not a power of two (%lu).\n", p_imagePath, *p_imageWidth );
    SDL_FreeSurface( s );
    throw "seal_Texture::<constructor> - an error occurred; by default, a description of the error will have been printed to stderr.";
  }
  *p_imageHeight = s->h;
  if( !f_IsPowerOfTwo( *p_imageHeight ))
  {
    fprintf( stderr, "seal_Texture::<constructor> - the height of the image \"%s\" is not a power of two (%lu).\n", p_imagePath, *p_imageHeight );
    SDL_FreeSurface( s );
    throw "seal_Texture::<constructor> - an error occurred; by default, a description of the error will have been printed to stderr.";
  }
  GLubyte *p = ( GLubyte* )malloc( sizeof( GLubyte ) * *p_imageWidth * *p_imageHeight * 4 );
  if( SDL_MUSTLOCK( s ))
    SDL_LockSurface( s );
  size_t i = 0;
  Uint8 r, g, b, a;
  size_t k = *p_imageWidth * *p_imageHeight * 4, m = 0;
  k -= ( *p_imageWidth * 4 );
  for( ; i < *p_imageWidth * *p_imageHeight; i ++ )
  {
    const Uint32 pixel = (( Uint32* )s->pixels )[ i ];
    SDL_GetRGBA( pixel, s->format, &r, &g, &b, &a );
    p[ k ++ ] = r;
    p[ k ++ ] = g;
    p[ k ++ ] = b;
    p[ k ++ ] = a;
    if( ++ m == *p_imageWidth )
    {
      k -= ( *p_imageWidth * 2 * 4 );
      m = 0;
    }
  }
  if( SDL_MUSTLOCK( s ))
    SDL_UnlockSurface( s );
  SDL_FreeSurface( s );
  return p;
}

bool seal_Texture::f_IsPowerOfTwo( const size_t p )
{
  size_t i = 1;
  while( i < p )
    i <<= 1;
  return i == p;
}
