#ifndef seal_queue_h

#define seal_queue_h

#include <stdlib.h>

template <class T>
struct seal_QueueNode
{
  struct seal_QueueNode<T> *m_n;
  T m_content;
};

template <class T>
class seal_Queue
{
  protected:
    struct seal_QueueNode<T> *m_first, *m_last;

  private:
    struct seal_QueueNode<T> *m_current;

  public:
    seal_Queue( void )
    {
      m_first = NULL;
      m_current = NULL;
    }

    ~seal_Queue( void )
    {
      p_Delete( m_first );
    }

  private:
    void p_Delete( struct seal_QueueNode<T> *p )
    {
      if( p != NULL )
      {
        p_Delete( p->m_n );
        p_Delete( p->m_content );
        free( p );
      }
    }

  public:
    void p_Empty( void )
    {
      p_Delete( m_first );
      m_first = NULL;
      m_current = NULL;
    }

    void p_MoveCurrentToBeginning( void )
    {
      m_current = m_first;
    }

    void p_Push( T p )
    {
      struct seal_QueueNode<T> *n = ( struct seal_QueueNode<T>* )malloc( sizeof( struct seal_QueueNode<T> ));
      n->m_n = NULL;
      n->m_content = f_Assign( p );
      if( m_first == NULL )
      {
        m_first = n;
        m_current = n;
      }
      else
      {
        m_last->m_n = n;
        if( m_current == NULL )
          m_current = n;
      }
      m_last = n;
    }

    bool f_IsEmpty( void )
    {
      return ( m_first == NULL );
    }

    bool f_CurrentIsAtEnd( void )
    {
      return ( m_current == NULL );
    }

    T f_Pop( void )
    {
      if( f_IsEmpty())
        throw "seal_Queue::f_Pop - f_IsEmpty() == true.";
      if( f_CurrentIsAtEnd())
        throw "seal_Queue::f_Pop - f_CurrentIsAtEnd() == true.";
      T content = f_Assign( m_current->m_content );
      m_current = m_current->m_n;
      return content;
    }

  protected:
    virtual T f_Assign( T p )
    {
      return p;
    }

    /* If your class overrides the following method, your class must have a destructor, and that destructor must invoke the `p_Empty()` method of this class. */
    virtual void p_Delete( T p )
    {
    }
};

#endif
