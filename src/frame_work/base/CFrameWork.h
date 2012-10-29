#ifndef _CFRAMEWORK_H
#define _CFRAMEWORK_H


#include "global.h"
#include "base/CControlView.h"
#include "base/CDataPlot.h"
#include "base/CCommandExecutor.h"
#include "base/CProtocolPackFactory.h"
#include "base/CPortIO.h"
#include "base/CPacketCollector.h"

class CFrameWorkElementsFactory;

/**
 * Frame Work class. Contain referenses to all framework object primitives.
 */
class CFrameWork {
  public:
    CFrameWork(CFrameWorkElementsFactory * elementsFactory);

    ~CFrameWork();


  protected:
    /**
     * pointer to Control view widget
     */
    CControlView * m_ControlView;

    /**
     * Pointer to Data Plot widget
     */
    CDataPlot * m_DataPlot;

    /**
     * Frame Work command executor. Thread based class which have a command queue. This class have a thread and  timer.
     *  If there have some command in queue, it start timer and execute coresponding command handler. If handler return not 0,
     * handler is called again after timer period. If handler return different from 0 value, command is unloaded from queue. 
     * If queue is empty timer is stoped and task go to sleep.
     */
    CCommandExecutor * m_Executor;

    CProtocolPackFactory * m_Protocol;

    CPortIO * m_PortIO;

    CPacketCollector * m_Colector;

    /**
     * Factory witch constructs ControlView, DataPlot, Executor, Protocol, PortIO,Colector (elements of CFrameWork).
     */
    CFrameWorkElementsFactory* m_ElementsFactory;


  public:
    virtual CPortIO * getPortIO();

    CPacketCollector  * getColector() volatile;

    CProtocolPackFactory * getProtocol();

    CCommandExecutor* geExecutor();

    CDataPlot * getDataPlot();

    CControlView* getControlView();

    /**
     * This function attach elements factory for FrameWork. If there allready have a factory,
     * this function make deallocation of all ellements, created with current factory, 
     * deallocate current factory and allocate new elements with new factory.
     */
    int attachElementsFactory(CFrameWorkElementsFactory * elementsFactory);


  protected:
    int deattachCurrentElementsFactory();

};
#endif
