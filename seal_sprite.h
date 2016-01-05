#ifndef seal_sprite_h

#define seal_sprite_h

#include "seal_texture.h"
#include "seal_tree.h"
#include <string.h>

typedef enum
{
  k_seal_SPRITE_ANIMATION_BEHAVIOUR__REPEATS,
  k_seal_SPRITE_ANIMATION_BEHAVIOUR__REVERSES,
  k_seal_SPRITE_ANIMATION_BEHAVIOUR__HALTS
}
t_seal_SPRITE_ANIMATION_BEHAVIOUR;

struct t_seal_SpriteArchetype
{
  char *m_label;
  seal_Texture *m_texture;
  bool m_deleteTexture;
  t_seal_SPRITE_ANIMATION_BEHAVIOUR m_animationBehaviour;
  size_t m_animationBehaviour_repeatFromFrame, m_numberOfFrames, *m_frames /* An array of sub-texture indices. */ , *m_ticksFrameShownFor, m_numberOfInstances;
};

class seal_SpriteArchetypeTree : public seal_Tree<struct t_seal_SpriteArchetype*, char*>
{
  private:
    t_seal_TREE_BRANCH_DIRECTION f_Compare_TT( struct t_seal_SpriteArchetype *p_old, struct t_seal_SpriteArchetype *p_new )
    {
      const int i = strcmp( p_old->m_label, p_new->m_label );
      if( i < 0 )
        return k_seal_TREE_BRANCH_DIRECTION__LEFT;
      if( i == 0 )
        return k_seal_TREE_BRANCH_DIRECTION__STRAIGHT;
      return k_seal_TREE_BRANCH_DIRECTION__RIGHT;
    }

    t_seal_TREE_BRANCH_DIRECTION f_Compare_TU( struct t_seal_SpriteArchetype *p_content, char *p_identifier )
    {
      const int i = strcmp( p_content->m_label, p_identifier );
      if( i < 0 )
        return k_seal_TREE_BRANCH_DIRECTION__LEFT;
      if( i == 0 )
        return k_seal_TREE_BRANCH_DIRECTION__STRAIGHT;
      return k_seal_TREE_BRANCH_DIRECTION__RIGHT;
    }

    struct t_seal_SpriteArchetype *f_IsNotInTree( char *p )
    {
    }

    void p_Delete( struct t_seal_SpriteArchetype *p )
    {
      if( p->m_deleteTexture )
        delete p->m_texture;
      free( p->m_frames );
      free( p->m_ticksFrameShownFor );
      free( p );
    }
};

typedef enum
{
  k_seal_SPRITE_ANIMATION_DIRECTION__FORWARDS = 1,
  k_seal_SPRITE_ANIMATION_DIRECTION__BACKWARDS = -1,
  k_seal_SPRITE_ANIMATION_DIRECTION__HALTED = 0
}
t_seal_SPRITE_ANIMATION_DIRECTION;

class seal_Sprite
{
  private:
    static seal_SpriteArchetypeTree *mg_archetypeTree;

    struct t_seal_SpriteArchetype *m_archetype;
    size_t m_frame;
    t_seal_SPRITE_ANIMATION_DIRECTION m_animationDirection;
    int m_ticksFrameShownFor;
    double m_bottomLeftX, m_bottomLeftY;
    seal_Quad_Triangles m_geometryCoordinates, m_textureCoordinates;
    bool m_opacityEnabled;
    GLfloat m_opacity;

  public:
    static void p_NewArchetype( char *p_label, seal_Texture *p_texture, const bool p_deleteTexture, const t_seal_SPRITE_ANIMATION_BEHAVIOUR p_animationBehaviour, const size_t p_animationBehaviour_repeatFromFrame, const size_t p_numberOfFrames, ... /* A frame (sub-texture index) followed by the ticks for which the frame is shown. */ );
    static void p_DeleteArchetype( char *p );

    seal_Sprite( char *p );
    ~seal_Sprite( void )
    {
      m_archetype->m_numberOfInstances --;
    }
    void p_Update( const size_t p );
    void p_Render( void );
    double f_GetBottomLeftX( void )
    {
      return m_bottomLeftX;
    }
    double f_GetBottomLeftY( void )
    {
      return m_bottomLeftY;
    }
    void p_SetBottomLeftX( const double p )
    {
      m_bottomLeftX = p;
    }
    void p_SetBottomLeftY( const double p )
    {
      m_bottomLeftY = p;
    }
    void p_SetFrame( const size_t p );
    bool f_Halted( void )
    {
      return m_animationDirection == k_seal_SPRITE_ANIMATION_DIRECTION__HALTED;
    }
    void p_HFlip( void )
    {
      m_geometryCoordinates.p_HFlip();
    }
    void p_VFlip( void )
    {
      m_geometryCoordinates.p_VFlip();
    }
    void p_SetOpacityEnabled( const bool p )
    {
      m_opacityEnabled = p;
    }
    void p_SetOpacity( const GLfloat p )
    {
      m_opacity = p;
    }
};

#endif
