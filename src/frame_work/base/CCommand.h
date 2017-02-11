#ifndef _CCOMMAND_H
#define _CCOMMAND_H


#include "global.h"
class FRAME_WORKSHARED_EXPORT CCommand {
  public:
    virtual ~CCommand();

    /**
     * Command handler
     */
    virtual int handler() = 0;

};
#endif
