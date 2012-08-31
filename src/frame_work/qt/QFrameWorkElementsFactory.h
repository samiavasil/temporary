#ifndef _QFRAMEWORKELEMENTSFACTORY_H
#define _QFRAMEWORKELEMENTSFACTORY_H


#include "base/CFrameWorkElementsFactory.h"

class CPortIO;
class CProtocolPackFactory;
class CCommandExecutor;
class CPacketCollector;
class CControlView;
class CDataPlot;
class QCommandExecutor;
class QProtocolPackFactory;
class QPacketCollector;
class QProtocolLoader;

class QFrameWorkElementsFactory : public CFrameWorkElementsFactory {
  public:
    virtual CPortIO* createPortIO();

    virtual CProtocolPackFactory* createPrtocol();

    virtual CCommandExecutor* createCommandExecutor();

    virtual CPacketCollector* createPacketCollector();

    virtual CControlView* createControlView();

    virtual CDataPlot* createDataPlot();

    virtual void deleteExecutor(CCommandExecutor * executor);

    virtual void deleteProtocol(CProtocolPackFactory * protocol);

    virtual void deletePortIO(CPortIO * port);

    virtual void deleteColector(CPacketCollector * collector);

    virtual void deleteControlView(CControlView * ctrlView);

    virtual void deleteDataPlot(CDataPlot * dataPlot);

};
#endif
