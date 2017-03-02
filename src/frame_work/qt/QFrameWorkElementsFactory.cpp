#include "qt/QFrameWorkElementsFactory.h"
#include "qt/QCommandExecutor.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QPacketCollector.h"
#include "qt/QProtocolLoader.h"
#include "qt/QSerialPortIO.h"
#include "base/CPortIO.h"
#include "base/CProtocolPackFactory.h"
//#include "base/CPacketCollector.h"
#include "base/CDataPlot.h"



//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

template<typename Element> QFrameWorkElementsFactory<Element>::QFrameWorkElementsFactory() {
  DEBUG << "Create QFrameWorkElementsFactory";
}

template<typename Element> QFrameWorkElementsFactory<Element>::~QFrameWorkElementsFactory() {
  DEBUG << "Destroy QFrameWorkElementsFactory";
}

template<typename Element> CPortIO* QFrameWorkElementsFactory<Element>::createPortIO(const Element &type) {
  CPortIO* port = NULL;                            
  DEBUG << "Create PortIo";
  switch( type ) {                                 
  case CPortIO::SIMULATOR_IO :{      

      break;                                       
  }                                                
  case CPortIO::SERIALPORT_IO :{                   
      port = new QSerialPortIO();                  
      break;                                       
  }                                                
  case CPortIO::USBPORT_IO :{                      
      break;                                       
  }                                                
  default:{                                        
      break;                                       
  }                                                
  }                                                
  if( 0 == port ){                                 
      CRITICAL <<  "Can't create QPortIO";
  }                                                
  return port;                                     
}

#include"qt/QProtocolDb.h"//TODO
#include"qt/QProtocolLoader.h"//TODO
template<typename Element> CProtocolPackFactory* QFrameWorkElementsFactory<Element>::createProtocol(const Element &type) {
  DEBUG << "Create Protocol";
  CProtocolPackFactory* protocol = new QProtocolPackFactory(new QProtocolDb());//TODO FIX ME
  if( 0 == protocol ){
      CRITICAL <<  "Can't create QProtocolPackFactory";
  }
  return protocol;
}

template<typename Element> QCommandExecutor* QFrameWorkElementsFactory<Element>::createCommandExecutor(const Element &type) {
  DEBUG << "Create Command Executor";
  QCommandExecutor* exec = new QCommandExecutor(NULL);     
  if( 0 != exec ){                                         
      if( NO_ERR != exec->startExecution() ){
          CRITICAL <<  "Can't start Executor thread";
      }                                                    
  }                                                        
  return ( exec );                                         
}

template<typename Element> QPacketCollector* QFrameWorkElementsFactory<Element>::createPacketCollector( QFrameWork * cFwk,const Element& type ) {
    DEBUG << "Create Packet Collector";
    QPacketCollector* coll = NULL;//TODO= new QPacketCollector(cFwk)
    if( 0 == coll ){                                 
        CRITICAL <<  "Can't create QPacketCollector";
    }                                                
    return ( coll ); 
}

template<typename Element> CControlView* QFrameWorkElementsFactory<Element>::createControlView(const Element& type) {
  DEBUG << "Create Control View";
  return NULL;                 
}

template<typename Element> CDataPlot* QFrameWorkElementsFactory<Element>::createDataPlot(const Element& type) {
  DEBUG << "Create Data Plot";
   return NULL;
}


