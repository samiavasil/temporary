#ifndef _CFRAMEWORKELEMENTSFACTORY_H
#define _CFRAMEWORKELEMENTSFACTORY_H


#include "base/CPortIO.h"
#include "base/CProtocolPackFactory.h"
//#include "base/CPacketCollector.h"
#include "base/CDataPlot.h"

class QFrameWork;
class QCommandExecutor;
class QPacketCollector;
/**
 *  
 */// class template with a template template parameter V


template<template<typename> class ElementsList,class Element>
class FRAME_WORKSHARED_EXPORT CFrameWorkElementsFactory {
  public:
    virtual CPortIO* createPortIO(const Element& type) = 0;

    virtual CProtocolPackFactory* createProtocol(const Element& type) = 0;

    virtual QCommandExecutor* createCommandExecutor(const Element& type) = 0;

    virtual QPacketCollector* createPacketCollector(QFrameWork * cFwk, const Element& type) = 0;

    virtual CDataPlot* createDataPlot(const Element& type) = 0;

    virtual const ElementsList<Element>& returnElementsTypes() = 0;

};
#endif
