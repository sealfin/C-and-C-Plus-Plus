#ifndef seal_bool_h

#define seal_bool_h

#ifndef __cplusplus
#define false 0
#define true 1
#endif

#ifdef LEONARDO
typedef unsigned short bool;
#endif

#if !defined( __cplusplus ) && defined( __MWERKS__ )
typedef unsigned char bool;
#endif

#if !defined( __cplusplus ) && !( defined( LEONARDO ) || defined( __MWERKS__ ))
typedef unsigned int bool;
#endif

#endif
