#ifndef seal_list_h

#define seal_list_h

template <class T>
struct t_seal_ListNode
{
  struct t_seal_ListNode<T> *m_p, *m_n;
  size_t m_index;
  T m_content;
};

template <class T>
class seal_List
{
  private:
    struct t_seal_ListNode<T> *m_first, *m_last;
    size_t m_number;

  public:
    seal_List( void )
    {
      m_first = NULL;
      m_last = NULL;
      m_number = 0;
    }

    ~seal_List( void )
    {
      p_Delete( m_first );
    }

  private:
    void p_Delete( struct t_seal_ListNode<T> *p )
    {
      if( p != NULL )
      {
        p_Delete( p->m_n );
        p_Delete( p->m_content );
        free( p );
      }
    }

  protected:
    virtual void p_Delete( T p )
    {
    }

  public:
    bool f_IsEmpty( void )
    {
      return m_number == 0;
    }

    void p_Empty( void )
    {
      p_Delete( m_first );
      m_first = NULL;
      m_last = NULL;
      m_number = 0;
    }

    size_t f_Number( void )
    {
      return m_number;
    }

    void p_Set( T p )
    {
      struct t_seal_ListNode<T> *n = ( struct t_seal_ListNode<T>* )malloc( sizeof( struct t_seal_ListNode<T> ));
      n->m_p = m_last;
      n->m_n = NULL;
      n->m_index = m_number ++;
      n->m_content = f_Assign( p );
      if( m_first == NULL )
        m_first = n;
      else
        m_last->m_n = n;
      m_last = n;
    }

  protected:
    virtual T f_Assign( T p )
    {
      return p;
    }

  public:
    bool f_IsInList( T p )
    {
      struct t_seal_ListNode<T> *n = m_first;
      while( n != NULL )
      {
        if( f_Compare( n->m_content, p ))
          return true;
        n = n->m_n;
      }
      return false;
    }

  protected:
    virtual bool f_Compare( T p_a, T p_b )
    {
      return p_a == p_b;
    }

  public:
    T f_GetByIndex( const size_t p )
    {
      if( p >= m_number )
        throw "seal_List::f_GetByIndex - p >= f_Number().";
      struct t_seal_ListNode<T> *n = m_first;
      while( n->m_index != p )
        n = n->m_n;
      T content = f_Assign( n->m_content );
      return content;
    }

    void p_Remove( T p )
    {
      struct t_seal_ListNode<T> *n = m_first;
      while(( n != NULL ) && !f_Compare( n->m_content, p ))
        n = n->m_n;
      if( n == NULL )
        throw "seal_List::p_Remove - f_IsInList( p ) == false.";
      if( n->m_p == NULL )
        m_first = n->m_n;
      else
        n->m_p->m_n = n->m_n;
      if( n->m_n == NULL )
        m_last = n->m_p;
      else
        n->m_n->m_p = n->m_p;
      p_RenumberIndices( n->m_n );
      free( n );
      m_number --;
    }

  private:
    void p_RenumberIndices( struct t_seal_ListNode<T> *p )
    {
      while( p != NULL )
      {
        p->m_index --;
        p = p->m_n;
      }
    }
};

#endif
