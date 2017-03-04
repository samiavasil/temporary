#ifndef _QTEST_FRAMEWORKELEMENTSFACTORY_H
#define _QTEST_FRAMEWORKELEMENTSFACTORY_H


#include "base/QFrameWorkElementsFactory.h"
#include<QList>

class QCommandExecutor;
class QProtocolPackFactory;
class QPacketCollector;
class QPortIO;
class QProtocolPackFactory;
class QCommandExecutor;
class QPacketCollector;
class QFrameWork;
class CControlView;
class QDataPlot;


template<typename Element> class FRAME_WORKSHARED_EXPORT QTestFrameWorkElementsFactory : public QFrameWorkElementsFactory<QList, Element > {
  public:
    /*
     * TODO: Implement this as abstract class wich shoul be inherited
     *
    virtual QPortIO* createPortIO(const Element& type) = 0;

    virtual QProtocolPackFactory* createProtocol(const Element& type) = 0;

    virtual QCommandExecutor* createCommandExecutor(const Element& type) = 0;

    virtual QPacketCollector* createPacketCollector(QFrameWork * cFwk, const Element& type) = 0;

    virtual CDataPlot* createDataPlot(const Element& type) = 0;

    virtual const ElementsList<Element>& returnElementsTypes() = 0;
    */

    QTestFrameWorkElementsFactory();

    virtual ~QTestFrameWorkElementsFactory();

    virtual QPortIO* createPortIO(const Element& type);

    virtual QProtocolPackFactory* createProtocol(const Element& type);

    virtual QCommandExecutor* createCommandExecutor(const Element& type);

    virtual QPacketCollector* createPacketCollector(QFrameWork * cFwk, const Element &type);

    virtual CControlView* createControlView(const Element& type);

    virtual QDataPlot* createDataPlot(const Element& type);

    const QList<Element>& returnElementsTypes(){ return m_list;}
  protected:
    QList<Element> m_list;
};
#endif
