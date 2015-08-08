#ifndef seal_stringQueue_h

#define seal_stringQueue_h

#include "seal_queue.h"
#include <string.h>

class seal_StringQueue : public seal_Queue<char*>
{
  private:
    char *f_Assign( char *p )
    {
      if( p == NULL )
        throw "seal_StringQueue::p_Push - p == NULL.";
      char *s = ( char* )malloc( sizeof( char ) * ( strlen( p ) + 1 ));
      strcpy( s, p );
      return s;
    }

    void p_Delete( char *p )
    {
      free( p );
    }

  public:
    char *f_String( void )
    {
      struct seal_QueueNode<char*> *n = m_first;
      size_t s_length = 0;
      while( n != NULL )
      {
        s_length += strlen( n->m_content );
        n = n->m_n;
      }
      char *s = ( char* )malloc( sizeof( char ) * ( s_length + 1 ));
      s[ 0 ] = '\0';
      n = m_first;
      while( n != NULL )
      {
        strcat( s, n->m_content );
        n = n->m_n;
      }
      return s;
    }
};

#endif
