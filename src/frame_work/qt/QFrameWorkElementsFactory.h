#ifndef _QFRAMEWORKELEMENTSFACTORY_H
#define _QFRAMEWORKELEMENTSFACTORY_H


#include "base/CFrameWorkElementsFactory.h"

class QCommandExecutor;
class QProtocolPackFactory;
class QPacketCollector;
class QProtocolLoader;
class QSerialPortIO;
class CPortIO;
class CProtocolPackFactory;
class CCommandExecutor;
class CPacketCollector;
class CFrameWork;
class CControlView;
class CDataPlot;
class QPortIOSimulator;

class QFrameWorkElementsFactory : public CFrameWorkElementsFactory {
  public:
    QFrameWorkElementsFactory();

    ~QFrameWorkElementsFactory();

    virtual CPortIO* createPortIO(const CPortIO::portIo_type type);

    virtual CProtocolPackFactory* createProtocol();

    virtual CCommandExecutor* createCommandExecutor();

    virtual CPacketCollector* createPacketCollector(CFrameWork * cFwk);

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
