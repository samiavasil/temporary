#ifndef _CFRAMEWORK_H
#define _CFRAMEWORK_H


#include "global.h"
class CCreator;

/**
 * Frame Work class. Contain referenses to all framework object primitives.
 */
class CFrameWork {
  public:
    CFrameWork(CCreator * creator = 0);

    virtual ~CFrameWork();

    bool Create();

    /**
     * TODO: TBD
     */
    void setCreator(CCreator * creator);


  protected:
    CCreator* m_creator;

};
#endif
