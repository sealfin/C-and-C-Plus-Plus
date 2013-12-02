#ifndef seal_stringQueue_noCopy_h

#define seal_stringQueue_noCopy_h

#include "seal_queue.h"

class seal_StringQueue_NoCopy : public seal_Queue<char*>
{
  private:
    void p_Delete( char *p )
    {
      free( p );
    }
};

#endif
