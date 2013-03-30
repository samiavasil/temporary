
#include "base/CFrameWork.h"
#include "base/CCreator.h"

CFrameWork::CFrameWork(CCreator * creator) {
  m_creator = creator;                                                    
}

CFrameWork::~CFrameWork() {
}

bool CFrameWork::Create() {
  bool bRet  = false;
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
  }
  m_creator = creator;
  Create();
}

