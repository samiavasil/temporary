#ifndef _QFRAMEWORKELEMENTSFACTORY_H
#define _QFRAMEWORKELEMENTSFACTORY_H


#include "base/CFrameWorkElementsFactory.h"
#include<QList>

class QCommandExecutor;
class QProtocolPackFactory;
class QPacketCollector;
class CPortIO;
class CProtocolPackFactory;
class QCommandExecutor;
class QPacketCollector;
class QFrameWork;
class CControlView;
class CDataPlot;


template<typename Element> class FRAME_WORKSHARED_EXPORT QFrameWorkElementsFactory : public CFrameWorkElementsFactory<QList, Element > {
  public:
    QFrameWorkElementsFactory();

    virtual ~QFrameWorkElementsFactory();

    virtual CPortIO* createPortIO(const Element& type);

    virtual CProtocolPackFactory* createProtocol(const Element& type);

    virtual QCommandExecutor* createCommandExecutor(const Element& type);

    virtual QPacketCollector* createPacketCollector(QFrameWork * cFwk, const Element &type);

    virtual CControlView* createControlView(const Element& type);

    virtual CDataPlot* createDataPlot(const Element& type);

    const QList<Element>& returnElementsTypes(){ return m_list;}
  protected:
    QList<Element> m_list;
};
#endif
