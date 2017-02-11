#ifndef _CCREATOR_H
#define _CCREATOR_H

#include "global.h"
class CFrameWork;

class FRAME_WORKSHARED_EXPORT CCreator {
  public:
    virtual ~CCreator();

    virtual bool Create(CFrameWork * fW) = 0;

    virtual void Free() = 0;

};
#endif
