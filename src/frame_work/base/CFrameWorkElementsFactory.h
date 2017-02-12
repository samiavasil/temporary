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
 */// class template with a template template parameter V


template<template<typename> class ElementsList,class Element>
class FRAME_WORKSHARED_EXPORT CFrameWorkElementsFactory {
  public:
    virtual CPortIO* createPortIO(const Element& type) = 0;

    virtual CProtocolPackFactory* createProtocol(const Element& type) = 0;

    virtual CCommandExecutor* createCommandExecutor(const Element& type) = 0;

    virtual CPacketCollector* createPacketCollector(CFrameWork * cFwk, const Element& type) = 0;

    virtual CDataPlot* createDataPlot(const Element& type) = 0;

    virtual const ElementsList<Element>& returnElementsTypes() = 0;

};
#endif
