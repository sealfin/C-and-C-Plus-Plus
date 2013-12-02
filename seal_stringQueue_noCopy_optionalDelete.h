#ifndef seal_stringQueue_noCopy_optionalDelete_h

#define seal_stringQueue_noCopy_optionalDelete_h

#include "seal_queue.h"

typedef struct t_seal_StringQueue_NoCopy_OptionalDeleteContent_struct
{
  char *m_string;
  bool m_delete;
}
t_seal_StringQueue_NoCopy_OptionalDeleteContent;

class seal_StringQueue_NoCopy_OptionalDelete : public seal_Queue<t_seal_StringQueue_NoCopy_OptionalDeleteContent>
{
  public:
    void p_Push( char *p_string, bool p_delete )
    {
      t_seal_StringQueue_NoCopy_OptionalDeleteContent c;
      c.m_string = p_string;
      c.m_delete = p_delete;
      seal_Queue<t_seal_StringQueue_NoCopy_OptionalDeleteContent>::p_Push( c );
    }

  private:
    void p_Delete( t_seal_StringQueue_NoCopy_OptionalDeleteContent p )
    {
      if( p.m_delete )
        free( p.m_string );
    }
};

#endif
