#ifndef seal_tree_h

#define seal_tree_h

#include <stdlib.h>

template <class T>
struct t_seal_TreeNode
{
  struct t_seal_TreeNode<T> *m_l, *m_r;
  T m_content;
};

typedef enum
{
  k_seal_TREE_BRANCH_DIRECTION__LEFT = -1,
  k_seal_TREE_BRANCH_DIRECTION__STRAIGHT = 0,
  k_seal_TREE_BRANCH_DIRECTION__RIGHT = 1
}
t_seal_TREE_BRANCH_DIRECTION;

template <class T, class U>
class seal_Tree
{
  protected:
    struct t_seal_TreeNode<T> *m_root;

  public:
    seal_Tree( void )
    {
      m_root = NULL;
    }

    ~seal_Tree( void )
    {
      p_Delete( m_root );
    }

  private:
    void p_Delete( struct t_seal_TreeNode<T> *p )
    {
      if( p != NULL )
      {
        p_Delete( p->m_l );
        p_Delete( p->m_r );
        p_Delete( p->m_content );
        free( p );
      }
    }

  public:
    void p_Set( T p )
    {
      if( m_root == NULL )
        m_root = f_NewTreeNode( p );
      else
        p_Set( m_root, p );
    }

  private:
    struct t_seal_TreeNode<T> *f_NewTreeNode( T p )
    {
      struct t_seal_TreeNode<T> *n = ( struct t_seal_TreeNode<T>* )malloc( sizeof( struct t_seal_TreeNode<T> ));
      n->m_l = NULL;
      n->m_r = NULL;
      n->m_content = p;
      return n;
    }

    void p_Set( struct t_seal_TreeNode<T> *p_n, T p_content )
    {
      const t_seal_TREE_BRANCH_DIRECTION bD = f_Compare_TT( p_n->m_content, p_content );
      if( bD == k_seal_TREE_BRANCH_DIRECTION__LEFT )
        if( p_n->m_l == NULL )
          p_n->m_l = f_NewTreeNode( p_content );
        else
          p_Set( p_n->m_l, p_content );
      else
        if( bD == k_seal_TREE_BRANCH_DIRECTION__RIGHT )
          if( p_n->m_r == NULL )
            p_n->m_r = f_NewTreeNode( p_content );
          else
            p_Set( p_n->m_r, p_content );
        else
          p_IsAlreadyInTree( p_n->m_content, p_content );
    }

  public:
    bool f_IsInTree( U p )
    {
      if( m_root == NULL )
        return false;
      return f_IsInTree( m_root, p );
    }

  private:
    bool f_IsInTree( struct t_seal_TreeNode<T> *p_n, U p_identifier )
    {
      const t_seal_TREE_BRANCH_DIRECTION bD = f_Compare_TU( p_n->m_content, p_identifier );
      if( bD == k_seal_TREE_BRANCH_DIRECTION__LEFT )
        if( p_n->m_l == NULL )
          return false;
        else
          return f_IsInTree( p_n->m_l, p_identifier );
      else
        if( bD == k_seal_TREE_BRANCH_DIRECTION__RIGHT )
          if( p_n->m_r == NULL )
            return false;
          else
            return f_IsInTree( p_n->m_r, p_identifier );
        else
          return true;
    }

  public:
    T f_Get( U p )
    {
      if( m_root == NULL )
        return f_IsNotInTree( p );
      return f_Get( m_root, p );
    }

  private:
    T f_Get( struct t_seal_TreeNode<T> *p_n, U p_identifier )
    {
      const t_seal_TREE_BRANCH_DIRECTION bD = f_Compare_TU( p_n->m_content, p_identifier );
      if( bD == k_seal_TREE_BRANCH_DIRECTION__LEFT )
        if( p_n->m_l == NULL )
          return f_IsNotInTree( p_identifier );
        else
          return f_Get( p_n->m_l, p_identifier );
      else
        if( bD == k_seal_TREE_BRANCH_DIRECTION__RIGHT )
          if( p_n->m_r == NULL )
            return f_IsNotInTree( p_identifier );
          else
            return f_Get( p_n->m_r, p_identifier );
        else
          return p_n->m_content;
    }

  protected:
    virtual t_seal_TREE_BRANCH_DIRECTION f_Compare_TT( T p_old, T p_new ) = 0;

    virtual t_seal_TREE_BRANCH_DIRECTION f_Compare_TU( T p_content, U p_identifier ) = 0;

    virtual void p_IsAlreadyInTree( T p_old, T p_new )
    {
    }

    virtual T f_IsNotInTree( U p ) = 0;

    virtual void p_Delete( T p )
    {
    }
};

#endif
