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
class CFrameWorkElementsFactory {
  public:
    virtual CPortIO* createPortIO(const CPortIO::portIo_type type) = 0;

    virtual CProtocolPackFactory* createProtocol() = 0;

    virtual CCommandExecutor* createCommandExecutor() = 0;

    virtual CPacketCollector* createPacketCollector(CFrameWork * cFwk) = 0;

    virtual CDataPlot* createDataPlot() = 0;

    virtual void deleteExecutor(CCommandExecutor * executor) = 0;

    virtual void deleteProtocol(CProtocolPackFactory * protocol) = 0;

    virtual void deletePortIO(CPortIO * port) = 0;

    virtual void deleteColector(CPacketCollector * collector) = 0;

    virtual void deleteDataPlot(CDataPlot * dataPlot) = 0;

};
#endif
