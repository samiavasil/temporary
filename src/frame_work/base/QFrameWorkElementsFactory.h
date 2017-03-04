#ifndef _CFRAMEWORKELEMENTSFACTORY_H
#define _CFRAMEWORKELEMENTSFACTORY_H

#include "base/global.h"

class QDataPlot;
class QPortIO;
class QFrameWork;
class QCommandExecutor;
class QPacketCollector;
class QProtocolPackFactory;
/**
 *  
 */// class template with a template template parameter V


template<template<typename> class ElementsList,class Element>
class FRAME_WORKSHARED_EXPORT QFrameWorkElementsFactory {
  public:
    virtual QPortIO* createPortIO(const Element& type) = 0;

    virtual QProtocolPackFactory* createProtocol(const Element& type) = 0;

    virtual QCommandExecutor* createCommandExecutor(const Element& type) = 0;

    virtual QPacketCollector* createPacketCollector(QFrameWork * cFwk, const Element& type) = 0;

    virtual QDataPlot* createDataPlot(const Element& type) = 0;

    virtual const ElementsList<Element>& returnElementsTypes() = 0;

};
#endif
