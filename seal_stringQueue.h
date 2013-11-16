#ifndef seal_stringQueue_h

#define seal_stringQueue_h

#include "seal_queue.h"
#include <string.h>

class seal_StringQueue : public seal_Queue<char*>
{
  public:
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
};

#endif
