#ifndef _CFRAMEWORKELEMENTSFACTORY_H
#define _CFRAMEWORKELEMENTSFACTORY_H


class CPortIO;
class CProtocolPackFactory;
class CCommandExecutor;
class CPacketCollector;
class CControlView;
class CDataPlot;

class CFrameWorkElementsFactory {
  public:
    virtual CPortIO* createPortIO() = 0;

    virtual CProtocolPackFactory* createPrtocol() = 0;

    virtual CCommandExecutor* createCommandExecutor() = 0;

    virtual CPacketCollector* createPacketCollector() = 0;

    virtual CControlView* createControlView() = 0;

    virtual CDataPlot* createDataPlot() = 0;

    virtual void deleteExecutor(CCommandExecutor * executor) = 0;

    virtual void deleteProtocol(CProtocolPackFactory * protocol) = 0;

    virtual void deletePortIO(CPortIO * port) = 0;

    virtual void deleteColector(CPacketCollector * collector) = 0;

    virtual void deleteControlView(CControlView * ctrlView) = 0;

    virtual void deleteDataPlot(CDataPlot * dataPlot) = 0;

};
#endif
