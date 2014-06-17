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

    virtual ~QFrameWorkElementsFactory();

    virtual CPortIO* createPortIO(const CPortIO::portIo_type type);

    virtual CProtocolPackFactory* createProtocol();

    virtual CCommandExecutor* createCommandExecutor();

    virtual CPacketCollector* createPacketCollector(CFrameWork * cFwk);

    virtual CControlView* createControlView();

    virtual CDataPlot* createDataPlot();

};
#endif
