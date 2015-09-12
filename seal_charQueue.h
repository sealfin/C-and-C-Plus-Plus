#ifndef seal_charQueue_h

#define seal_charQueue_h

#include "seal_queue.h"
#include <string.h>
#include <stdio.h>

class seal_CharQueue : public seal_Queue<char>
{
  private:
    size_t m_number;

  public:
    seal_CharQueue( void )
    {
      m_number = 0;
    }

    void p_Empty( void )
    {
      seal_Queue<char>::p_Empty();
      m_number = 0;
    }

    void p_Push( char p )
    {
      seal_Queue<char>::p_Push( p );
      m_number ++;
    }

  private:
    bool f_CharacterIsInString( const char c, const char * const s )
    {
      size_t i = 0;
      for( ; i < strlen( s ); i ++ )
        if( c == s[ i ] )
          return true;
      return false;
    }

  public:
    void p_Read( FILE *p_file, const char * const p_startCharacters, const char * const p_stopCharacters, char *p_stopCharacter, const bool p_throwExceptionIfFileEndsBeforeStartCharacterRead, const bool p_throwExceptionIfFileEndsBeforeStopCharacterRead, bool *p_endOfFile )
    /*
    If p_startCharacters is NULL, characters will begin to be read/added to the queue from the current position in the file.
    If p_stopCharacters is NULL, characters will be read/added to the queue 'til the end of the file.
    */
    {
      if( p_file == NULL )
        throw "seal_CharQueue::p_Read - p_file == NULL.";
      if( p_endOfFile != NULL )
        *p_endOfFile = false;
      char c;
      bool startCharacterRead = p_startCharacters == NULL;
      while( fscanf( p_file, "%c", &c ) != EOF )
        if( !startCharacterRead )
          startCharacterRead = f_CharacterIsInString( c, p_startCharacters );
        else
          if(( p_stopCharacters == NULL ) || !f_CharacterIsInString( c, p_stopCharacters ))
            p_Push( c );
          else
          {
            if( p_stopCharacter != NULL )
              *p_stopCharacter = c;
            return;
          }
      if( p_endOfFile != NULL )
        *p_endOfFile = true;
      if( !startCharacterRead )
      {
        if( p_throwExceptionIfFileEndsBeforeStartCharacterRead )
          throw "seal_CharQueue::p_Read - unexpected end of file before start character read.";
      }
      else
        if(( p_stopCharacters != NULL ) && ( p_throwExceptionIfFileEndsBeforeStopCharacterRead ))
          throw "seal_CharQueue::p_Read - unexpected end of file before stop character read.";
    }

    void p_Read( FILE *p_file, const char * const p_stopString, const bool p_throwExceptionIfFileEndsBeforeStopStringRead, bool *p_endOfFile )
    {
      if( p_file == NULL )
        throw "seal_CharQueue::p_Read - p_file == NULL.";
      if( p_stopString == NULL )
        throw "seal_CharQueue::p_Read - p_stopString == NULL.";
      if( strlen( p_stopString ) == 0 )
        throw "seal_CharQueue::p_Read - strlen( p_stopString ) == 0.";
      char c;
      size_t i = 0;
      while( fscanf( p_file, "%c", &c ) != EOF )
      {
        p_Push( c );
        if( c == p_stopString[ i ] )
        {
          i ++;
          if( i == strlen( p_stopString ))
          {
            if( p_endOfFile != NULL )
              *p_endOfFile = false;
            return;
          }
        }
        else
          i = 0;
      }
      if( p_endOfFile != NULL )
        *p_endOfFile = true;
      if( p_throwExceptionIfFileEndsBeforeStopStringRead )
        throw "seal_CharQueue::p_Read - unexpected end of file before stop string read.";
    }

    char *f_String( void )
    {
      if( f_IsEmpty())
        throw "seal_CharQueue::f_String - f_IsEmpty() == true.";
      char *s = ( char* )malloc( sizeof( char ) * ( m_number + 1 ));
      size_t i = 0;
      struct seal_QueueNode<char> *n = m_first;
      do
      {
        s[ i ++ ] = n->m_content;
        n = n->m_n;
      }
      while( n != NULL );
      s[ i ] = '\0';
      return s;
    }
};

#endif
