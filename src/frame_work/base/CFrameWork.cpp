
#include "base/CFrameWork.h"
#include "base/CCreator.h"

CFrameWork::CFrameWork(CCreator * creator) {
  m_creator = creator;                                                    
}

CFrameWork::~CFrameWork() {
    if( m_creator )
    {
       delete m_creator;
       m_creator = 0;
    }
}

bool CFrameWork::Create() {
  bool bRet  = true;
  if( m_creator )
      bRet = m_creator->Create( this );
  return bRet;
}

/**
 * TODO: TBD
 */
void CFrameWork::setCreator(CCreator * creator) {
  if( m_creator )
  {
    m_creator->Free();
    delete m_creator;
  }
  m_creator = creator;
  Create();
}

