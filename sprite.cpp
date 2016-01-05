#include "seal_sprite.h"
#include "seal_quadColours_triangles.h"
#include <stdio.h>
#include <stdarg.h>

seal_SpriteArchetypeTree *seal_Sprite::mg_archetypeTree = NULL;

#define M_seal_SPRITE__THROW_EXCEPTION( p ) \
  throw "seal_Sprite::" p " - an error occurred; by default, a description of the error will have been printed to stderr.";

void seal_Sprite::p_NewArchetype( char *p_label, seal_Texture *p_texture, const bool p_deleteTexture, const t_seal_SPRITE_ANIMATION_BEHAVIOUR p_animationBehaviour, const size_t p_animationBehaviour_repeatFromFrame, const size_t p_numberOfFrames, ... /* A frame (sub-texture index) followed by the ticks for which the frame is shown. */ )
{
  if( p_label == NULL )
  {
    fprintf( stderr, "seal_Sprite::p_NewArchetype - p_label == NULL.\n" );
    M_seal_SPRITE__THROW_EXCEPTION( "p_NewArchetype" )
  }
  if(( mg_archetypeTree != NULL ) && ( mg_archetypeTree->f_IsInTree( p_label )))
  {
    fprintf( stderr, "seal_Sprite::p_NewArchetype - mg_archetypeTree->f_IsInTree( \"%s\" ) == true.\n", p_label );
    M_seal_SPRITE__THROW_EXCEPTION( "p_NewArchetype" )
  }
  if( p_texture == NULL )
  {
    fprintf( stderr, "seal_Sprite::p_NewArchetype( \"%s\", ... ) - p_texture == NULL.\n", p_label );
    M_seal_SPRITE__THROW_EXCEPTION( "p_NewArchetype" )
  }
  if( p_numberOfFrames == 0 )
  {
    fprintf( stderr, "seal_Sprite::p_NewArchetype( \"%s\", ... ) - p_numberOfFrames == 0.\n", p_label );
    M_seal_SPRITE__THROW_EXCEPTION( "p_NewArchetype" )
  }
  if(( p_animationBehaviour == k_seal_SPRITE_ANIMATION_BEHAVIOUR__REPEATS ) && ( p_animationBehaviour_repeatFromFrame >= p_numberOfFrames ))
  {
    fprintf( stderr, "seal_Sprite::p_NewArchetype( \"%s\", ... ) - p_animationBehaviour == k_seal_SPRITE_ANIMATION_BEHAVIOUR__REPEATS && p_animationBehaviour_repeatFromFrame (%lu) ≥ p_numberOfFrames (%lu).\n", p_label, p_animationBehaviour_repeatFromFrame, p_numberOfFrames );
    M_seal_SPRITE__THROW_EXCEPTION( "p_NewArchetype" )
  }
  struct t_seal_SpriteArchetype *a = ( struct t_seal_SpriteArchetype* )malloc( sizeof( struct t_seal_SpriteArchetype ));
  a->m_label = p_label;
  a->m_texture = p_texture;
  a->m_deleteTexture = p_deleteTexture;
  a->m_animationBehaviour = p_animationBehaviour;
  a->m_animationBehaviour_repeatFromFrame = p_animationBehaviour_repeatFromFrame;
  a->m_numberOfFrames = p_numberOfFrames;
  a->m_frames = ( size_t* )malloc( sizeof( size_t ) * a->m_numberOfFrames );
  a->m_ticksFrameShownFor = ( size_t* )malloc( sizeof( size_t ) * a->m_numberOfFrames );
  va_list parameter;
  size_t i = 0;
  int k;
  va_start( parameter, p_numberOfFrames );
  for( ; i < a->m_numberOfFrames; i ++ )
  {
    k = va_arg( parameter, int );
    if(( k < 0 ) || ( k >= a->m_texture->f_NumberOfSubTextures()))
    {
      fprintf( stderr, "seal_Sprite::p_NewArchetype( \"%s\", ... ) - m_frames[ %lu ] (%d) < 0 || m_frames[ %lu ] ≥ m_texture->f_NumberOfSubTextures() (%lu).\n", p_label, i, k, i, a->m_texture->f_NumberOfSubTextures());
      free( a->m_frames );
      free( a->m_ticksFrameShownFor );
      free( a );
      M_seal_SPRITE__THROW_EXCEPTION( "p_NewArchetype" )
    }
    a->m_frames[ i ] = k;

    k = va_arg( parameter, int );
    if( k <= 0 )
    {
      fprintf( stderr, "seal_Sprite::p_NewArchetype( \"%s\", ... ) - m_ticksFrameShownFor[ %lu ] (%d) ≤ 0.\n", p_label, i, k );
      free( a->m_frames );
      free( a->m_ticksFrameShownFor );
      free( a );
      M_seal_SPRITE__THROW_EXCEPTION( "p_NewArchetype" )
    }
    a->m_ticksFrameShownFor[ i ] = k;
  }
  va_end( parameter );
  a->m_numberOfInstances = 0;
  if( mg_archetypeTree == NULL )
    mg_archetypeTree = new seal_SpriteArchetypeTree();
  mg_archetypeTree->p_Set( a );
}

void seal_Sprite::p_DeleteArchetype( char *p )
{
  if( p == NULL )
  {
    fprintf( stderr, "seal_Sprite::p_DeleteArchetype - p == NULL.\n" );
    M_seal_SPRITE__THROW_EXCEPTION( "p_DeleteArchetype" )
  }
  if( mg_archetypeTree == NULL )
  {
    fprintf( stderr, "seal_Sprite::p_DeleteArchetype( \"%s\" ) - mg_archetypeTree == NULL.\n", p );
    M_seal_SPRITE__THROW_EXCEPTION( "p_DeleteArchetype" )
  }
  if( !mg_archetypeTree->f_IsInTree( p ))
  {
    fprintf( stderr, "seal_Sprite::p_DeleteArchetype - mg_archetypeTree->f_IsInTree( \"%s\" ) == false.\n", p );
    M_seal_SPRITE__THROW_EXCEPTION( "p_DeleteArchetype" )
  }
  struct t_seal_SpriteArchetype *a = mg_archetypeTree->f_Get( p );
  if( a->m_numberOfInstances > 0 )
  {
    fprintf( stderr, "seal_Sprite::p_DeleteArchetype( \"%s\" ) - m_numberOfInstances (%lu) > 0.\n", p, a->m_numberOfInstances );
    M_seal_SPRITE__THROW_EXCEPTION( "p_DeleteArchetype" )
  }
  mg_archetypeTree->p_Remove( p );
}

seal_Sprite::seal_Sprite( char *p )
{
  if( p == NULL )
  {
    fprintf( stderr, "seal_Sprite::<constructor> - p == NULL.\n" );
    M_seal_SPRITE__THROW_EXCEPTION( "<constructor>" )
  }
  if( mg_archetypeTree == NULL )
  {
    fprintf( stderr, "seal_Sprite::<constructor>( \"%s\" ) - mg_archetypeTree == NULL.\n", p );
    M_seal_SPRITE__THROW_EXCEPTION( "<constructor>" )
  }
  if( !mg_archetypeTree->f_IsInTree( p ))
  {
    fprintf( stderr, "seal_Sprite::<constructor> - mg_archetypeTree->f_IsInTree( \"%s\" ) == false.\n", p );
    M_seal_SPRITE__THROW_EXCEPTION( "<constructor>" )
  }
  m_archetype = mg_archetypeTree->f_Get( p );
  m_archetype->m_numberOfInstances ++;
  m_frame = 0;
  m_animationDirection = k_seal_SPRITE_ANIMATION_DIRECTION__FORWARDS;
  m_ticksFrameShownFor = m_archetype->m_ticksFrameShownFor[ m_frame ];
  m_bottomLeftX = 0;
  m_bottomLeftY = 0;
  m_geometryCoordinates.p_Set( m_bottomLeftX, m_bottomLeftY, m_archetype->m_texture->f_SubTextureWidth(), m_archetype->m_texture->f_SubTextureHeight());
  m_archetype->m_texture->p_GetSubTextureQuad( m_archetype->m_frames[ m_frame ], &m_textureCoordinates );
  m_opacityEnabled = false;
  m_opacity = 1;
}

void seal_Sprite::p_Update( const size_t p )
{
  if( m_animationDirection != k_seal_SPRITE_ANIMATION_DIRECTION__HALTED )
  {
    m_ticksFrameShownFor -= p;
    if( m_ticksFrameShownFor <= 0 )
    {
      switch( m_archetype->m_animationBehaviour )
      {
        case k_seal_SPRITE_ANIMATION_BEHAVIOUR__REPEATS:
          if( ++ m_frame == m_archetype->m_numberOfFrames )
            m_frame = m_archetype->m_animationBehaviour_repeatFromFrame;
          break;
        case k_seal_SPRITE_ANIMATION_BEHAVIOUR__REVERSES:
          if( m_animationDirection == k_seal_SPRITE_ANIMATION_DIRECTION__FORWARDS )
          {
            if( ++ m_frame == m_archetype->m_numberOfFrames )
              if( m_archetype->m_numberOfFrames >= 2 )
              {
                m_frame = m_archetype->m_numberOfFrames - 2;
                m_animationDirection = k_seal_SPRITE_ANIMATION_DIRECTION__BACKWARDS;
              }
              else
                m_frame = 0;
          }
          else
            if( m_frame == 0 )
              if( m_archetype->m_numberOfFrames >= 2 )
              {
                m_frame = 1;
                m_animationDirection = k_seal_SPRITE_ANIMATION_DIRECTION__FORWARDS;
              }
              else
                m_frame = 0;
            else
              m_frame --;
          break;
        case k_seal_SPRITE_ANIMATION_BEHAVIOUR__HALTS:
          if( ++ m_frame == m_archetype->m_numberOfFrames )
          {
            m_frame = m_archetype->m_numberOfFrames - 1;
            m_animationDirection = k_seal_SPRITE_ANIMATION_DIRECTION__HALTED;
          }
      }
      m_ticksFrameShownFor += m_archetype->m_ticksFrameShownFor[ m_frame ];
      m_archetype->m_texture->p_GetSubTextureQuad( m_archetype->m_frames[ m_frame ], &m_textureCoordinates );
    }
  }
}

void seal_Sprite::p_Render( void )
{
  glVertexPointer( 2, GL_FLOAT, 0, m_geometryCoordinates.m_coordinates );
  seal_QuadColours_Triangles coordinateColours( 1, 1, 1, m_opacity );
  if( m_opacityEnabled )
  {
    glEnableClientState( GL_COLOR_ARRAY );
    glColorPointer( 4, GL_FLOAT, 0, coordinateColours.m_rgba );
  }
  glTexCoordPointer( 2, GL_FLOAT, 0, m_textureCoordinates.m_coordinates );
  m_archetype->m_texture->p_Bind();
  glPushMatrix();
  glTranslatef(( GLfloat )( GLint )m_bottomLeftX, ( GLfloat )( GLint )m_bottomLeftY, 0 );
  glDrawArrays( GL_TRIANGLES, 0, 6 );
  glPopMatrix();
  if( m_opacityEnabled )
    glDisableClientState( GL_COLOR_ARRAY );
}

void seal_Sprite::p_SetFrame( const size_t p )
{
  if( p >= m_archetype->m_numberOfFrames )
  {
    fprintf( stderr, "seal_Sprite::p_SetFrame - p (%lu) ≥ m_archetype->m_numberOfFrames (%lu).\n", p, m_archetype->m_numberOfFrames );
    M_seal_SPRITE__THROW_EXCEPTION( "p_SetFrame" )
  }
  m_frame = p;
  m_archetype->m_texture->p_GetSubTextureQuad( m_archetype->m_frames[ m_frame ], &m_textureCoordinates );
  m_ticksFrameShownFor = m_archetype->m_ticksFrameShownFor[ m_frame ];
}

#undef M_seal_SPRITE__THROW_EXCEPTION
