#ifndef DEBUG_H
#define DEBUG_H
#include "qdbg.h"
extern QDbg* m_Debug;
#define DEB1(x)  if( m_Debug ) \
                    m_Debug->log(x);

#define DEBUG_ENABLE( x ) if( x ){ \
                            if( !m_Debug ){\
                               m_Debug = new QDbg( QString(__FILE__) , NULL );\
                            }\
                            m_Debug->logEnable(x);\
                          }else{\
                            if( m_Debug ){\
                                m_Debug->logEnable(x);\
                                delete m_Debug;\
                                m_Debug = NULL;\
                            }\
                          }


#endif // DEBUG_H
