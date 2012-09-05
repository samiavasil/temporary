#ifndef _CCOMMAND_H
#define _CCOMMAND_H


#include "global.h"
class CCommand {
  public:
    /**
     * Command handler
     */
    virtual int handler() = 0;

};
#endif
