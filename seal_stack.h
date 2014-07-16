#ifndef seal_stack_h

#define seal_stack_h

#include <stdlib.h>

template <class T>
struct t_seal_StackNode
{
  struct t_seal_StackNode<T> *m_d;
  T m_content;
};

template <class T>
class seal_Stack
{
  protected:
    struct t_seal_StackNode<T> *m_top;

  public:
    seal_Stack( void )
    {
      m_top = NULL;
    }

    ~seal_Stack( void )
    {
      p_Delete( m_top );
    }

  private:
    void p_Delete( struct t_seal_StackNode<T> *p )
    {
      if( p != NULL )
      {
        p_Delete( p->m_d );
        p_Delete( p->m_content );
        free( p );
      }
    }

  public:
    void p_Empty( void )
    {
      p_Delete( m_top );
      m_top = NULL;
    }

    void p_Push( T p )
    {
      struct t_seal_StackNode<T> *n = ( struct t_seal_StackNode<T>* )malloc( sizeof( struct t_seal_StackNode<T> ));
      n->m_d = m_top;
      n->m_content = f_Assign( p );
      m_top = n;
    }

    bool f_IsEmpty( void )
    {
      return ( m_top == NULL );
    }

    T f_Pop( void )
    {
      if( f_IsEmpty())
        throw "seal_Stack::f_Pop - f_IsEmpty() == true.";
      T content = m_top->m_content;
      struct t_seal_StackNode<T> *n = m_top;
      m_top = m_top->m_d;
      free( n );
      return content;
    }

  protected:
    virtual T f_Assign( T p )
    {
      return p;
    }

    virtual void p_Delete( T p )
    {
    }
};

#endif
