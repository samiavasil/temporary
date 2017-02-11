#ifndef _CFRAMEWORKELEMENTSFACTORY_H
#define _CFRAMEWORKELEMENTSFACTORY_H


#include "base/CPortIO.h"
#include "base/CProtocolPackFactory.h"
#include "base/CCommandExecutor.h"
#include "base/CPacketCollector.h"
#include "base/CDataPlot.h"

class CFrameWork;

/**
 *  
 */
class FRAME_WORKSHARED_EXPORT CFrameWorkElementsFactory {
  public:
    virtual CPortIO* createPortIO(const CPortIO::portIo_type type) = 0;

    virtual CProtocolPackFactory* createProtocol() = 0;

    virtual CCommandExecutor* createCommandExecutor() = 0;

    virtual CPacketCollector* createPacketCollector(CFrameWork * cFwk) = 0;

    virtual CDataPlot* createDataPlot() = 0;

};
#endif
